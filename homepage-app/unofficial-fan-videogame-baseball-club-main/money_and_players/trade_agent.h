/**
 * @file trade_agent.h
 * @brief Defines the Trade Agent for handling player transactions (v3.9.1).
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
 * This agent will be responsible for proposing, evaluating, and executing
 * trades, taking into account player preferences, team budgets, and other
 * strategic factors.
 */
class TradeAgent {
public:
    /**
     * @brief Proposes a trade between two teams for a set of players.
     * @param team1 The first team in the trade.
     * @param team2 The second team in the trade.
     * @param players_from_team1 A vector of players to be traded from team 1.
     * @param players_from_team2 A vector of players to be traded from team 2.
     * @return True if the trade is successful, false otherwise.
     */
    bool proposeTrade(Team& team1, Team& team2, const std::vector<Player*>& players_from_team1, const std::vector<Player*>& players_from_team2);
};

} // namespace LeagueSchedulerNS

#endif // TRADE_AGENT_H
