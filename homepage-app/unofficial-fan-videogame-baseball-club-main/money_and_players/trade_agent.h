/**
 * @file trade_agent.h
 * @brief Defines the Trade Agent for handling player transactions (v3.9.2).
 * @author  Eeshvar Das (Erik Douglas Ward)
 * @date 2025-Jul-27
 *
 * @copyright Copyright (C) 2025 Eeshvar Das (Erik Douglas Ward)
 *
 * @license SPDX-License-Identifier: AGPL-3.0-or-later
 */

#ifndef TRADE_AGENT_H
#define TRADE_AGENT_H

#include <vector>
#include "team_data.h"
#include "player_data.h"

namespace LeagueSchedulerNS {

/**
 * @class TradeAgent
 * @brief Manages the logic for player trades between teams.
 *
 * v3.9.2: This agent now checks player trade preferences before executing a trade.
 */
class TradeAgent {
public:
    /**
     * @brief Proposes a trade between two teams for a set of players.
     * @param offering_team The team offering the players.
     * @param receiving_team The team receiving the players.
     * @param players_to_trade A vector of pointers to the players being offered.
     * @return True if the trade is successful, false otherwise.
     */
    bool proposeTrade(Team& offering_team, Team& receiving_team, const std::vector<Player*>& players_to_trade);
};

} // namespace LeagueSchedulerNS

#endif // TRADE_AGENT_H
