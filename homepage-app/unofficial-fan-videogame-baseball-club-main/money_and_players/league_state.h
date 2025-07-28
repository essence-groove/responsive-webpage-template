/**
 * @file league_state.h
 * @brief Defines the main data structure for the league's persistent state (v3.9.2).
 * @author  Eeshvar Das (Erik Douglas Ward)
 * @date 2025-Jul-27
 *
 * @copyright Copyright (C) 2025 Eeshvar Das (Erik Douglas Ward)
 *
 * @license SPDX-License-Identifier: AGPL-3.0-or-later
 */

#ifndef LEAGUE_STATE_H
#define LEAGUE_STATE_H

#include <vector>
#include <string>
#include "team_data.h"

namespace LeagueSchedulerNS {

/**
 * @struct LeagueState
 * @brief Encapsulates the entire state of the baseball league.
 *
 * This structure is designed to be saved at the end of a season and loaded
 * at the beginning of the next, enabling a true, persistent offseason and
 * multi-season play.
 */
struct LeagueState {
    int current_season_year = 2025;
    std::vector<Team> teams;
    // Future fields for offseason simulation can be added here, e.g.:
    // std::vector<Player> free_agents;
    // DraftOrder draft_order;
};

} // namespace LeagueSchedulerNS

#endif // LEAGUE_STATE_H
