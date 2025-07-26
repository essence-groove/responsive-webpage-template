/**
 * @file league_scheduler.cpp
 * @brief Main entry point for the unofficial-fan-videogame-baseball-club game.
 * @author  Eeshvar Das (Erik Douglas Ward)
 * @date 2025-Jul-23
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

std::vector<ResidencyBlock> LeagueScheduler2::generateSeasonSchedule(const std::vector<Team>& all_teams, int games_per_team) {
    std::vector<ResidencyBlock> season_schedule;

    if (all_teams.size() < 3) {
        std::cerr << "Need at least 3 teams to create a residency block (1 host + 2 visitors)." << std::endl;
        return season_schedule;
    }

    int residency_block_counter = 0;
    for (const auto& host_team : all_teams) {
        std::vector<Team> potential_visitors;
        for (const auto& team : all_teams) {
            if (team.id != host_team.id) {
                potential_visitors.push_back(team);
            }
        }

        if (potential_visitors.size() < 2) {
            continue;
        }

        std::shuffle(potential_visitors.begin(), potential_visitors.end(), rng);
        // FIX: Create a new vector containing two specific teams from the shuffled list.
        std::vector<Team> visiting_teams = {potential_visitors[0], potential_visitors[1]};

        ResidencyBlock block = createResidencyBlock(host_team, visiting_teams);
        season_schedule.push_back(block);
        residency_block_counter++;

        if (residency_block_counter >= all_teams.size()) { 
            break;
        }
    }

    std::cout << "Generated " << season_schedule.size() << " residency blocks." << std::endl;
    return season_schedule;
}

ResidencyBlock LeagueScheduler2::createResidencyBlock(const Team& host, const std::vector<Team>& visitors) {
    ResidencyBlock block;
    block.host_team = host;
    block.visiting_residents = visitors;
    block.start_date = "2025-07-25"; // Placeholder
    block.end_date = "2025-07-31";   // Placeholder

    if (visitors.size() < 2) {
        std::cerr << "Error: Not enough visiting residents for a residency block and Crossroads Games." << std::endl;
        return block;
    }

    // Games between Host and each Visitor
    for (const auto& visitor : visitors) {
        Game game;
        // FIX: Assign a single Team object (the current visitor in the loop).
        game.team1 = visitor;
        game.team2 = host;
        game.designated_home_team_for_batting = host;
        game.actual_host_stadium = host;
        game.date = block.start_date;
        game.game_type = GameType::REGULAR_SEASON;
        block.games.push_back(game);
    }

    // Crossroads Games between the two visiting residents
    // FIX: Pass the two individual Team objects from the visitors vector.
    std::vector<Game> crossroads_series = generateCrossroadsGames(visitors[0], visitors[1], host, 5);
    block.games.insert(block.games.end(), crossroads_series.begin(), crossroads_series.end());

    return block;
}

std::vector<Game> LeagueScheduler2::generateCrossroadsGames(const Team& visitor1, const Team& visitor2, const Team& host_stadium, int num_games_in_series) {
    std::vector<Game> series_games;
    std::uniform_int_distribution<> distrib(0, 1);
    bool visitor1_bats_first = (distrib(rng) == 0);

    for (int i = 0; i < num_games_in_series; ++i) {
        Game game;
        game.actual_host_stadium = host_stadium;
        game.game_type = GameType::CROSSROADS_GAME;
        game.date = "Crossroads Game " + std::to_string(i + 1);

        // Alternate who bats first each game
        if ((i % 2 == 0) ? visitor1_bats_first : !visitor1_bats_first) {
            game.team1 = visitor1;
            game.team2 = visitor2;
            game.designated_home_team_for_batting = visitor2;
        } else {
            game.team1 = visitor2;
            game.team2 = visitor1;
            game.designated_home_team_for_batting = visitor1;
        }
        series_games.push_back(game);
    }
    return series_games;
}

} // namespace LeagueSchedulerNS
