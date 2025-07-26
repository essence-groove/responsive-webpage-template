/**
 * @file league_scheduler_2.h
 * @brief Header for the v3.7.0 league scheduling logic.
 * @author  Eeshvar Das (Erik Douglas Ward)
 * @date 2025-Jul-25
 *
 * @copyright Copyright (C) 2025 Eeshvar Das (Erik Douglas Ward)
 *
 * @license SPDX-License-Identifier: AGPL-3.0-or-later
 */

#ifndef LEAGUE_SCHEDULER_2_H
#define LEAGUE_SCHEDULER_2_H

#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include "../money_and_players/game_data.h" 
#include "../money_and_players/team_data.h" 

namespace LeagueSchedulerNS { 

/**
 * @class LeagueScheduler2
 * @brief Manages the generation of the APMW season schedule for v3.7.0.
 *
 * This version is enhanced to create extended residency blocks (3+ weeks)
 * and formally incorporates "Regional Games" into the scheduling logic.
 */
class LeagueScheduler2 {
public:
    // Constructor
    LeagueScheduler2();

    // Main function to generate the season schedule
    std::vector<ResidencyBlock> generateSeasonSchedule(const std::vector<Team>& all_teams, int games_per_team);

private:
    /**
     * @brief Helper to create an extended residency block.
     * @param host The host team for the residency.
     * @param visitors A vector of visiting teams.
     * @param day_counter A reference to a counter to track game dates across the season.
     * @return A fully populated ResidencyBlock.
     *
     * v3.7.0: Signature updated to manage date progression for longer, staggered blocks.
     */
    ResidencyBlock createResidencyBlock(const Team& host, const std::vector<Team>& visitors, int& day_counter);

    /**
     * @brief Generates a series of neutral-site games (Crossroads or Regional).
     * @param visitor1 The first visiting team.
     * @param visitor2 The second visiting team.
     * @param host_stadium The team whose stadium hosts the neutral game.
     * @param num_games The number of games in the series.
     * @param game_type The type of game (CROSSROADS_GAME or REGIONAL_GAME).
     * @param day_counter A reference to the season's day counter.
     * @return A vector of Game objects for the series.
     *
     * v3.7.0: New generalized helper function to create different types of neutral-site games.
     */
    std::vector<Game> generateNeutralSiteSeries(const Team& visitor1, const Team& visitor2, const Team& host_stadium, int num_games, GameType game_type, int& day_counter);

    // Random number generator for shuffling teams and determining batting order.
    std::mt19937 rng;
};

} // namespace LeagueSchedulerNS

#endif // LEAGUE_SCHEDULER_2_H
