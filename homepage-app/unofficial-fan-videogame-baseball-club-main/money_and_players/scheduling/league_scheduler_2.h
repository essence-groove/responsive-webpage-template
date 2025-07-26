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
// v3.8.0 FIX: Use direct includes. The new CMake configuration correctly
// provides the search path via the 'money_and_players_data' library.
#include "game_data.h" 
#include "team_data.h" 
#include "geography_data.h"

namespace LeagueSchedulerNS { 

/**
 * @class LeagueScheduler2
 * @brief Manages the generation of the APMW season schedule for v3.8.0.
 */
class LeagueScheduler2 {
public:
    // Constructor
    LeagueScheduler2();

    // Main function to generate the season schedule
    std::vector<ResidencyBlock> generateSeasonSchedule(std::vector<Team>& all_teams, int games_per_team);

private:
    // Private helper struct to track team status during scheduling.
    struct TeamScheduleStatus {
        int available_day = 1;
        int games_scheduled = 0;
        int host_blocks_assigned = 0;
    };

    /**
     * @brief Helper to create an extended residency block.
     */
    ResidencyBlock createResidencyBlock(const Team& host, const std::vector<Team>& visitors, int start_day, int& out_duration_days);

    /**
     * @brief Generates a series of neutral-site games (Crossroads or Regional).
     */
    std::vector<Game> generateNeutralSiteSeries(const Team& visitor1, const Team& visitor2, const Team& host_stadium, int num_games, GameType game_type, int start_day, int& day_offset);

    // Random number generator for shuffling teams and determining batting order.
    std::mt19937 rng;
};

} // namespace LeagueSchedulerNS

#endif // LEAGUE_SCHEDULER_2_H
