/**
 * @file environmental_agent.h
 * @brief Defines the Environmental Impact Evaluation Agent for v3.8.1.
 * @author  Eeshvar Das (Erik Douglas Ward)
 * @date 2025-Jul-26
 *
 * @copyright Copyright (C) 2025 Eeshvar Das (Erik Douglas Ward)
 *
 * @license SPDX-License-Identifier: AGPL-3.0-or-later
 */

#ifndef ENVIRONMENTAL_AGENT_H
#define ENVIRONMENTAL_AGENT_H

#include <vector>
#include <string>
#include "game_data.h"
#include "geography_data.h"

namespace LeagueSchedulerNS {

/**
 * @class EnvironmentalAgent
 * @brief An analytical module that evaluates the environmental impact of a generated schedule.
 */
class EnvironmentalAgent {
public:
    /**
     * @brief Analyzes a completed schedule and generates an environmental report.
     * @param schedule The vector of ResidencyBlock objects representing the season schedule.
     */
    void generateReport(const std::vector<ResidencyBlock>& schedule);

private:
    // A simple multiplier to convert abstract distance units to a CO2 equivalent (e.g., kg of CO2).
    // This is a placeholder for a more complex calculation.
    const double DISTANCE_TO_CO2_MULTIPLIER = 150.0; 
};

} // namespace LeagueSchedulerNS

#endif // ENVIRONMENTAL_AGENT_H
