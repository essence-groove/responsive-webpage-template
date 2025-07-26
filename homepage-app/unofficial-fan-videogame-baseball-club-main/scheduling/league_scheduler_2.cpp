/**
 * @file league_scheduler_2.cpp
 * @brief Implements the scheduling logic for the APMW baseball league (v3.7.0).
 * @author  Eeshvar Das (Erik Douglas Ward)
 * @date 2025-Jul-25
 *
 * @copyright Copyright (C) 2025 Eeshvar Das (Erik Douglas Ward)
 *
 * @license SPDX-License-Identifier: AGPL-3.0-or-later
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "league_scheduler_2.h"
#include <iostream>
#include <chrono>
#include <algorithm>
#include <random>

namespace LeagueSchedulerNS {

// Constructor to initialize the random number generator
LeagueScheduler2::LeagueScheduler2() : rng(std::chrono::steady_clock::now().time_since_epoch().count()) {}

/**
 * @brief Generates the full season schedule for all teams.
 *
 * v3.7.0: This function orchestrates the creation of complex, extended residency blocks,
 * aiming for a total season length of approximately 94-102 games per team. It now handles
 * selecting multiple visitors for longer residencies.
 */
std::vector<ResidencyBlock> LeagueScheduler2::generateSeasonSchedule(const std::vector<Team>& all_teams, int games_per_team) {
    std::vector<ResidencyBlock> season_schedule;
    int day_counter = 1; // Simple date tracker

    if (all_teams.size() < 4) {
        std::cerr << "Error: At least 4 teams are recommended for generating interesting residency blocks." << std::endl;
        return season_schedule;
    }

    // This is a simplified loop for demonstration. A full implementation would
    // continue until the target game count is met for all teams.
    for (const auto& host_team : all_teams) {
        std::vector<Team> potential_visitors;
        for (const auto& team : all_teams) {
            if (team.id != host_team.id) {
                potential_visitors.push_back(team);
            }
        }

        if (potential_visitors.size() < 3) continue;

        std::shuffle(potential_visitors.begin(), potential_visitors.end(), rng);
        
        // Create an extended block with 3 visiting teams
        std::vector<Team> visiting_teams = {potential_visitors[0], potential_visitors[1], potential_visitors[2]};

        ResidencyBlock block = createResidencyBlock(host_team, visiting_teams, day_counter);
        season_schedule.push_back(block);
    }

    std::cout << "Generated " << season_schedule.size() << " residency blocks using v3.7.0 logic." << std::endl;
    return season_schedule;
}

/**
 * @brief Creates a single, potentially extended residency block.
 *
 * v3.7.0: This function is the core of the new scheduling logic. It creates a mix of
 * regular, Crossroads, and the new Regional games over a multi-week period. It identifies
 * visiting teams from the same region to schedule Regional Games.
 */
ResidencyBlock LeagueScheduler2::createResidencyBlock(const Team& host, const std::vector<Team>& visitors, int& day_counter) {
    ResidencyBlock block;
    block.host_team = host;
    block.visiting_residents = visitors;
    block.start_date = "Day " + std::to_string(day_counter);

    // Schedule games between the host and each visiting team
    for (const auto& visitor : visitors) {
        // Schedule a 2-game series, alternating who bats second
        Game g1, g2;
        g1 = {.team1 = visitor, .team2 = host, .designated_home_team_for_batting = host, .actual_host_stadium = host, .date = "Day " + std::to_string(day_counter++), .game_type = GameType::REGULAR_SEASON};
        g2 = {.team1 = host, .team2 = visitor, .designated_home_team_for_batting = visitor, .actual_host_stadium = host, .date = "Day " + std::to_string(day_counter++), .game_type = GameType::REGULAR_SEASON};
        block.games.push_back(g1);
        block.games.push_back(g2);
        day_counter++; // Travel/Rest Day
    }

    // Schedule neutral-site games between all pairs of visiting teams
    for (size_t i = 0; i < visitors.size(); ++i) {
        for (size_t j = i + 1; j < visitors.size(); ++j) {
            const auto& visitor1 = visitors[i];
            const auto& visitor2 = visitors[j];
            std::vector<Game> series;

            // v3.7.0: Check if visitors are from the same region to schedule a REGIONAL_GAME
            if (visitor1.region == visitor2.region) {
                series = generateNeutralSiteSeries(visitor1, visitor2, host, 2, GameType::REGIONAL_GAME, day_counter);
            } else {
                series = generateNeutralSiteSeries(visitor1, visitor2, host, 2, GameType::CROSSROADS_GAME, day_counter);
            }
            block.games.insert(block.games.end(), series.begin(), series.end());
        }
    }
    
    // Sort games by date for a chronological block schedule
    std::sort(block.games.begin(), block.games.end(), [](const Game& a, const Game& b){
        // A simple string sort works for "Day X" format
        return a.date.length() < b.date.length() || (a.date.length() == b.date.length() && a.date < b.date);
    });

    block.end_date = "Day " + std::to_string(day_counter - 1);
    day_counter += 2; // Extra rest days after a long block
    return block;
}

/**
 * @brief Generates a series of neutral-site games (Crossroads or Regional).
 *
 * v3.7.0: This helper function is generalized to create a series of a specified game type,
 * handling the alternating batting order rule for fairness.
 */
std::vector<Game> LeagueScheduler2::generateNeutralSiteSeries(const Team& visitor1, const Team& visitor2, const Team& host_stadium, int num_games, GameType game_type, int& day_counter) {
    std::vector<Game> series_games;
    std::uniform_int_distribution<> distrib(0, 1);
    bool visitor1_is_initial_home_batter = (distrib(rng) == 0);

    for (int i = 0; i < num_games; ++i) {
        Game game;
        game.actual_host_stadium = host_stadium;
        game.game_type = game_type;
        game.date = "Day " + std::to_string(day_counter + i * 2); // Spread games out

        // Alternate who bats second (designated home) each game
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
    }
    day_counter += num_games * 2;
    return series_games;
}

} // namespace LeagueSchedulerNS
