/**
 * @file financial_agent.h
 * @brief Defines the Financial Agent for managing team economies (v3.9.2).
 * @author  Eeshvar Das (Erik Douglas Ward)
 * @date 2025-Jul-27
 *
 * @copyright Copyright (C) 2025 Eeshvar Das (Erik Douglas Ward)
 *
 * @license SPDX-License-Identifier: AGPL-3.0-or-later
 */

#ifndef FINANCIAL_AGENT_H
#define FINANCIAL_AGENT_H

#include "team_data.h"

namespace LeagueSchedulerNS {

/**
 * @class FinancialAgent
 * @brief Manages the financial calculations and state for teams in the league.
 *
 * This agent will handle tasks like calculating payroll, updating budgets,
 * and processing revenue and expenses.
 */
class FinancialAgent {
public:
    /**
     * @brief Calculates and updates the player payroll for a given team.
     * @param team A reference to the team whose payroll should be calculated.
     */
    void calculateTeamPayroll(Team& team);
};

} // namespace LeagueSchedulerNS

#endif // FINANCIAL_AGENT_H
