/**
 * @file persistence_agent.h
 * @brief Defines the Persistence Agent for saving and loading league state (v3.9.2).
 * @author  Eeshvar Das (Erik Douglas Ward)
 * @date 2025-Jul-27
 *
 * @copyright Copyright (C) 2025 Eeshvar Das (Erik Douglas Ward)
 *
 * @license SPDX-License-Identifier: AGPL-3.0-or-later
 */

#ifndef PERSISTENCE_AGENT_H
#define PERSISTENCE_AGENT_H

#include <string>
#include "league_state.h"

namespace LeagueSchedulerNS {

/**
 * @class PersistenceAgent
 * @brief Manages saving and loading the entire league state to/from a file.
 *
 * This enables multi-season play by persisting the league's progress.
 */
class PersistenceAgent {
public:
    /**
     * @brief Saves the current league state to a file.
     * @param state The LeagueState object to save.
     * @param filename The name of the file to save to.
     * @return True if saving was successful, false otherwise.
     */
    bool saveState(const LeagueState& state, const std::string& filename);

    /**
     * @brief Loads the league state from a file.
     * @param filename The name of the file to load from.
     * @return A LeagueState object. If loading fails, it returns a default-initialized state.
     */
    LeagueState loadState(const std::string& filename);
};

} // namespace LeagueSchedulerNS

#endif // PERSISTENCE_AGENT_H
