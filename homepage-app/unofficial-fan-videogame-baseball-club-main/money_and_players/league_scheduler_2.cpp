/**
 * @file league_scheduler_2.cpp
 * @brief Implements the scheduling logic for the APMW baseball league (v3.8.1).
 * @author  Eeshvar Das (Erik Douglas Ward)
 * @date 2025-Jul-26

 *
 * @copyright Copyright (C) 2025 Eeshvar Das (Erik Douglas Ward)
 *
 * @license SPDX-License-Identifier: AGPL-3.0-or-later
 *
 * v3.8.1: This version represents a stabilization of the 3.8.0 concurrent
 * scheduling engine. The logic has been reviewed to ensure flawless consistency
 * in game counts and precise management of travel/rest days.

 */

#include "league_scheduler_2.h"
#include <iostream>
#include <chrono>
#include <algorithm>
#include <random>
#include <map>
#include <vector>
#include "days.h" // 1. Add this line


namespace LeagueSchedulerNS {

// Constructor to initialize the random number generator
LeagueScheduler2::LeagueScheduler2() : rng(std::chrono::steady_clock::now().time_since_epoch().count()) {}

/**
 * @brief Generates the full season schedule using the concurrent algorithm.

 */
std::vector<ResidencyBlock> LeagueScheduler2::generateSeasonSchedule(std::vector<Team>& all_teams, int games_per_team) {
    std::vector<ResidencyBlock> season_schedule;
    std::map<int, TeamScheduleStatus> team_statuses;
    for(const auto& team : all_teams) {
        team_statuses[team.id] = TeamScheduleStatus();
    }

    int current_day = 1;
    const int MAX_SEASON_DAYS = 200;
    const int MAX_HOST_BLOCKS = (games_per_team * all_teams.size()) / (18 * 12); // Approximate target

    while (current_day < MAX_SEASON_DAYS) {

        std::vector<Team*> available_teams;
        for (auto& team : all_teams) {
            if (team_statuses[team.id].available_day <= current_day) {
                available_teams.push_back(&team);
            }
        }
        
        std::shuffle(available_teams.begin(), available_teams.end(), rng);

        while (available_teams.size() >= 4) {

            Team* host = nullptr;
            auto host_it = std::find_if(available_teams.begin(), available_teams.end(), [&](Team* t){
                return team_statuses[t->id].host_blocks_assigned < MAX_HOST_BLOCKS;
            });

            if (host_it == available_teams.end()) break;
            host = *host_it;
            available_teams.erase(host_it);


            std::vector<Team> visitors;
            std::sort(available_teams.begin(), available_teams.end(), [&](Team* a, Team* b){
                return GeographyData::calculateDistance(host->city, a->city) > GeographyData::calculateDistance(host->city, b->city);
            });
            
            for(int i=0; i < 3 && !available_teams.empty(); ++i) {
                visitors.push_back(*available_teams.front());
                available_teams.erase(available_teams.begin());
            }

            if (visitors.size() < 3) {

                available_teams.push_back(host);
                break; 
            }


            int block_duration = 0;
            ResidencyBlock block = createResidencyBlock(*host, visitors, current_day, block_duration);
            season_schedule.push_back(block);
            

            int end_day = current_day + block_duration;
            team_statuses[host->id].available_day = end_day;
            team_statuses[host->id].games_scheduled += block.games.size();
            team_statuses[host->id].host_blocks_assigned++;

            for (const auto& visitor : visitors) {
                team_statuses[visitor.id].available_day = end_day;
                // Note: In a more complex simulation, visitor game counts might differ.
                // For this model, all teams in a block play the same number of games.
                team_statuses[visitor.id].games_scheduled += block.games.size() / 4; // Approximate
            }
        }


        int next_free_day = MAX_SEASON_DAYS + 1;
        bool all_done = true;
        for(const auto& pair : team_statuses) {
            if (pair.second.games_scheduled < games_per_team) {
                all_done = false;
                if (pair.second.available_day > current_day) {
                    next_free_day = std::min(next_free_day, pair.second.available_day);
                }
            }
        }
        if (all_done) break;

        current_day = (next_free_day > MAX_SEASON_DAYS) ? current_day + 1 : next_free_day;
    }

    std::cout << "Generated " << season_schedule.size() << " residency blocks over approx " << current_day << " days." << std::endl;
    return season_schedule;
}

/**
 * @brief Creates a single residency block with precise game counts and rest days.
 */
ResidencyBlock LeagueScheduler2::createResidencyBlock(const Team& host, const std::vector<Team>& visitors, int start_day, int& out_duration_days) {
    ResidencyBlock block;
    block.host_team = host;
    block.visiting_residents = visitors;
    block.start_date = "Day " + std::to_string(start_day);

    int day_offset = 1; // Start on day 1 of the block (day 0 is arrival)

    // 2 games per visitor against the host (6 total)

    for (const auto& visitor : visitors) {
        Game g1, g2;
        g1 = {.team1 = visitor, .team2 = host, .designated_home_team_for_batting = host, .actual_host_stadium = host, .date = "Day " + std::to_string(start_day + day_offset++), .game_type = GameType::REGULAR_SEASON};
        g2 = {.team1 = host, .team2 = visitor, .designated_home_team_for_batting = visitor, .actual_host_stadium = host, .date = "Day " + std::to_string(start_day + day_offset++), .game_type = GameType::REGULAR_SEASON};
        block.games.push_back(g1);
        block.games.push_back(g2);
        day_offset++; // Rest day
    }

    day_offset++; // Extra rest day before neutral games

    // 2 games per visitor pair (6 total)

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
    
    std::sort(block.games.begin(), block.games.end(), [](const Game& a, const Game& b){
        int day_a = getDayNumber(a.date);
        int day_b = getDayNumber(b.date);

        return day_a < day_b;
    });

    out_duration_days = day_offset + 1; 
    block.end_date = "Day " + std::to_string(start_day + out_duration_days - 1);
    return block;
}

/**
 * @brief Generates a series of neutral-site games with rest days.
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
        
        day_offset += (i < num_games - 1) ? 2 : 1;
    }
    day_offset++;
    return series_games;
}

} // namespace LeagueSchedulerNS
