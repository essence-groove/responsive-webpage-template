/**
 * @file trade_agent.cpp
 * @brief Implements the Trade Agent for handling player transactions (v3.9.2).
 * @author  Eeshvar Das (Erik Douglas Ward)
 * @date 2025-Jul-27
 *
 * @copyright Copyright (C) 2025 Eeshvar Das (Erik Douglas Ward)
 *
 * @license SPDX-License-Identifier: AGPL-3.0-or-later
 */

#include "trade_agent.h"
#include <iostream>
#include <vector>

namespace LeagueSchedulerNS {

/**
 * @brief Proposes and evaluates a trade based on player preferences.
 *
 * v3.9.2: This function now contains the core logic to check if players
 * are willing to be traded to a new region or union.
 */
bool TradeAgent::proposeTrade(Team& offering_team, Team& receiving_team, const std::vector<Player*>& players_to_trade) {
    std::cout << "\n--- Trade Proposal Initiated (v3.9.2) ---" << std::endl;
    std::cout << "Team " << offering_team.city << " offers players to Team " << receiving_team.city << "." << std::endl;
    
    // Check if any player in the package would veto the trade.
    for (const auto* player : players_to_trade) {
        // Check for region veto
        if (offering_team.region_type != receiving_team.region_type && !player->will_accept_trade_to_new_region) {
            std::cout << "TRADE VETOED: Player " << player->name << " is unwilling to move to a new region." << std::endl;
            std::cout << "------------------------------------------" << std::endl;
            return false;
        }
        // Check for union veto
        if (offering_team.union_type != receiving_team.union_type && !player->will_accept_trade_to_new_union) {
            std::cout << "TRADE VETOED: Player " << player->name << " is unwilling to move to a new union." << std::endl;
            std::cout << "------------------------------------------" << std::endl;
            return false;
        }
    }
    
    // Placeholder: If no vetos, the trade is considered successful for now.
    // Future logic will handle roster updates and financial checks.
    std::cout << "Trade successfully executed (all players accepted the terms)." << std::endl;
    std::cout << "------------------------------------------" << std::endl;

    return true;
}

} // namespace LeagueSchedulerNS
