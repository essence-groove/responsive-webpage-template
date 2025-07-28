/**
 * @file financial_agent.cpp
 * @brief Implements the Financial Agent for managing team economies (v3.9.2).
 * @author  Eeshvar Das (Erik Douglas Ward)
 * @date 2025-Jul-27
 *
 * @copyright Copyright (C) 2025 Eeshvar Das (Erik Douglas Ward)
 *
 * @license SPDX-License-Identifier: AGPL-3.0-or-later
 */

#include "financial_agent.h"
#include <iostream>
#include <numeric> // Required for std::accumulate

namespace LeagueSchedulerNS {

/**
 * @brief Calculates and updates the player payroll for a given team.
 *
 * This function iterates through all players on a team's roster, sums
 * their salaries, and updates the team's player_payroll member.
 */
void FinancialAgent::calculateTeamPayroll(Team& team) {
    long long total_payroll = 0;
    for (const auto& player : team.players) {
        total_payroll += player.salary;
    }
    team.player_payroll = total_payroll;

    std::cout << "Financial Agent: Calculated payroll for " << team.city << ": $" << total_payroll << std::endl;
}

} // namespace LeagueSchedulerNS
