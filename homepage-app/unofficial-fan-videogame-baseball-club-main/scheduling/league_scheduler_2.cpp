/**
 * @file league_scheduler_2.cpp
 * @brief Implements the scheduling logic for the APMW baseball league (v3.7.4).
 * @author  Eeshvar Das (Erik Douglas Ward)
 * @date 2025-Jul-25
 *
 * @copyright Copyright (C) 2025 Eeshvar Das (Erik Douglas Ward)
 *
 * @license SPDX-License-Identifier: AGPL-3.0-or-later
 *
 * Note: The core scheduling logic in this file is unchanged from v3.7.2.
 * Version 3.7.4 focuses on adding the geographical data layer (`geography_data.h`)
 * which will be used by the reporting mechanism in `main.cpp`.
 */

#include "league_scheduler_2.h"
#include <iostream>
#include <chrono>
#include <algorithm>
#include <random>
#include <map>

namespace LeagueSchedulerNS {

// Constructor to initialize the random number generator
LeagueScheduler2::LeagueScheduler2() : rng(std::chrono::steady_clock::now().time_since_epoch().count()) {}

/**
 * @brief Generates the full season schedule using parallel block scheduling.
 *
 * v3.7.1 logic for parallel scheduling is maintained. It manages a calendar and
 * team availability to schedule multiple residency blocks concurrently.
 */
std::vector<ResidencyBlock> LeagueScheduler2::generateSeasonSchedule(std::vector<Team>& all_teams, int games_per_team) {
    std::vector<ResidencyBlock> season_schedule;
    std::map<int, int> team_availability; // Maps team_id to the day they become available
    for(const auto& team : all_teams) {
        team_availability[team.id] = 1; // All teams are available on Day 1
    }

    int total_games_scheduled = 0;
    const int total_games_target = (all_teams.size() * games_per_team) / 2;
    int current_day = 1;
    const int MAX_SEASON_DAYS = 250; // Safety break for a reasonable season length

    while (total_games_scheduled < total_games_target && current_day < MAX_SEASON_DAYS) {
        std::vector<Team*> available_teams;
        for (auto& team : all_teams) {
            if (team_availability[team.id] <= current_day) {
                available_teams.push_back(&team);
            }
        }

        if (available_teams.size() >= 4) { // Need at least 1 host and 3 visitors for a rich block
            std::shuffle(available_teams.begin(), available_teams.end(), rng);

            Team* host = available_teams[0];
            std::vector<Team> visitors = {*available_teams[1], *available_teams[2], *available_teams[3]};

            int block_duration = 0;
            ResidencyBlock block = createResidencyBlock(*host, visitors, current_day, block_duration);
            season_schedule.push_back(block);
            total_games_scheduled += block.games.size();

            // Mark all participating teams as unavailable for the full duration of the block
            int end_day = current_day + block_duration;
            team_availability[host->id] = end_day;
            for (const auto& visitor : visitors) {
                team_availability[visitor.id] = end_day;
            }
        } else {
            // If not enough teams are available, advance time to the next day any team becomes free
            int next_free_day = MAX_SEASON_DAYS;
            for(const auto& pair : team_availability) {
                if (pair.second > current_day) {
                    next_free_day = std::min(next_free_day, pair.second);
                }
            }
            current_day = next_free_day;
        }
    }

    std::cout << "Generated " << season_schedule.size() << " residency blocks over approx " << current_day << " days." << std::endl;
    return season_schedule;
}

/**
 * @brief Creates a single residency block with explicit travel/rest days.
 *
 * v3.7.2: This function is meticulously adjusted to explicitly account for and
 * schedule travel/rest days between game series. This ensures the block's
 * duration is realistic and consistent.
 */
ResidencyBlock LeagueScheduler2::createResidencyBlock(const Team& host, const std::vector<Team>& visitors, int start_day, int& out_duration_days) {
    ResidencyBlock block;
    block.host_team = host;
    block.visiting_residents = visitors;
    block.start_date = "Day " + std::to_string(start_day);

    int day_offset = 0; // Tracks days elapsed *within this block*

    // Day 0: Assumed arrival day for visitors

    // Schedule games between the host and each visiting team
    for (const auto& visitor : visitors) {
        // Play a 2-game series
        Game g1, g2;
        g1 = {.team1 = visitor, .team2 = host, .designated_home_team_for_batting = host, .actual_host_stadium = host, .date = "Day " + std::to_string(start_day + day_offset++), .game_type = GameType::REGULAR_SEASON};
        g2 = {.team1 = host, .team2 = visitor, .designated_home_team_for_batting = visitor, .actual_host_stadium = host, .date = "Day " + std::to_string(start_day + day_offset++), .game_type = GameType::REGULAR_SEASON};
        block.games.push_back(g1);
        block.games.push_back(g2);
        
        // Explicitly add a rest day after each host vs. visitor series
        day_offset++; 
    }

    // Add another rest day before the neutral-site games begin
    day_offset++;

    // Schedule neutral-site games (Crossroads/Regional) between all pairs of visiting teams
    for (size_t i = 0; i < visitors.size(); ++i) {
        for (size_t j = i + 1; j < visitors.size(); ++j) {
            const auto& visitor1 = visitors[i];
            const auto& visitor2 = visitors[j];
            std::vector<Game> series;
            
            if (visitor1.region_type == visitor2.region_type) {
                series = generateNeutralSiteSeries(visitor1, visitor2, host, 2, GameType::REGIONAL_GAME, start_day, day_offset);
            } else {
                series = generateNeutralSiteSeries(visitor1, visitor2, host, 2, GameType::CROSSROADS_GAME, start_day, day_offset);
            }
            block.games.insert(block.games.end(), series.begin(), series.end());
        }
    }
    
    // Sort games by date for a clean, chronological report
    std::sort(block.games.begin(), block.games.end(), [](const Game& a, const Game& b){
        int day_a = std::stoi(a.date.substr(4));
        int day_b = std::stoi(b.date.substr(4));
        return day_a < day_b;
    });

    out_duration_days = day_offset + 1; // Total days for the block plus a final departure/rest day
    block.end_date = "Day " + std::to_string(start_day + out_duration_days - 1);
    return block;
}

/**
 * @brief Generates a series of neutral-site games with rest days.
 *
 * v3.7.2: Logic adjusted to ensure there's a rest day between neutral-site games.
 */
std::vector<Game> LeagueScheduler2::generateNeutralSiteSeries(const Team& visitor1, const Team& visitor2, const Team& host_stadium, int num_games, GameType game_type, int start_day, int& day_offset) {
    std::vector<Game> series_games;
    std::uniform_int_distribution<> distrib(0, 1);
    bool visitor1_is_initial_home_batter = (distrib(rng) == 0);

    for (int i = 0; i < num_games; ++i) {
        Game game;
        game.actual_host_stadium = host_stadium;
        game.game_type = game_type;
        game.date = "Day " + std::to_string(start_day + day_offset);

        bool v1_bats_home_this_game = (i % 2 == 0) ? visitor1_is_initial_home_batter : !visitor1_is_initial_home_batter;

        if (v1_bats_home_this_game) {
            game.team1 = visitor2;
            game.team2 = visitor1;
            game.designated_home_team_for_batting = visitor1;
        } else {
            game.team1 = visitor1;
            game.team2 = visitor2;
            game.designated_home_team_for_batting = visitor2;
        }
        series_games.push_back(game);
        
        // Advance the day offset. Add an extra day for rest between games in the series.
        day_offset += 2; 
    }
    return series_games;
}

} // namespace LeagueSchedulerNS
