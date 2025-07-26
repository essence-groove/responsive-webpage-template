/**
 * @file league_scheduler_2.h
 * @brief Header for the v3.8.0 league scheduling logic.
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
#include <map>
#include "../money_and_players/game_data.h" 
#include "../money_and_players/team_data.h" 
#include "../money_and_players/geography_data.h"

namespace LeagueSchedulerNS { 

/**
 * @class LeagueScheduler2
 * @brief Manages the generation of the APMW season schedule for v3.8.0.
 *
 * This version introduces a sophisticated, concurrent scheduling algorithm to
 * manage multiple residency blocks in parallel, ensuring a balanced and
 * realistically timed season.
 */
class LeagueScheduler2 {
public:
    // Constructor
    LeagueScheduler2();

    // Main function to generate the season schedule
    std.vector<ResidencyBlock> generateSeasonSchedule(std::vector<Team>& all_teams, int games_per_team);

private:
    // v3.8.0: New private helper struct to track team status
    struct TeamScheduleStatus {
        int available_day = 1;
        int games_scheduled = 0;
        int host_blocks_assigned = 0;
    };

    /**
     * @brief Helper to create an extended residency block.
     * @param host The host team for the residency.
     * @param visitors A vector of visiting teams.
     * @param start_day The day the block begins.
     * @param out_duration_days An output parameter that will be set to the block's total duration.
     * @return A fully populated ResidencyBlock.
     */
    ResidencyBlock createResidencyBlock(const Team& host, const std::vector<Team>& visitors, int start_day, int& out_duration_days);

    /**
     * @brief Generates a series of neutral-site games (Crossroads or Regional).
     * @param visitor1 The first visiting team.
     * @param visitor2 The second visiting team.
     * @param host_stadium The team whose stadium hosts the neutral game.
     * @param num_games The number of games in the series.
     * @param game_type The type of game (CROSSROADS_GAME or REGIONAL_GAME).
     * @param start_day The day the series begins.
     * @param day_offset An initial offset for game days within the series.
     * @return A vector of Game objects for the series.
     */
    std::vector<Game> generateNeutralSiteSeries(const Team& visitor1, const Team& visitor2, const Team& host_stadium, int num_games, GameType game_type, int start_day, int& day_offset);

    // Random number generator for shuffling teams and determining batting order.
    std::mt19937 rng;
};

} // namespace LeagueSchedulerNS

#endif // LEAGUE_SCHEDULER_2_H
