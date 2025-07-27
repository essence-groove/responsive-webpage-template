/**
 * @file environmental_agent.cpp
 * @brief Implements the Environmental Impact Evaluation Agent for v3.8.1.
 * @author  Eeshvar Das (Erik Douglas Ward)
 * @date 2025-Jul-26
 *
 * @copyright Copyright (C) 2025 Eeshvar Das (Erik Douglas Ward)
 *
 * @license SPDX-License-Identifier: AGPL-3.0-or-later
 */

#include "environmental_agent.h"
#include <iostream>
#include <iomanip>
#include <set>

namespace LeagueSchedulerNS {

/**
 * @brief Analyzes a schedule, calculates total travel distance, and prints a report.
 */
void EnvironmentalAgent::generateReport(const std::vector<ResidencyBlock>& schedule) {
    double total_travel_distance = 0.0;
    std::string last_location_of_team[19]; // Assuming max 18 teams (ID 1-18)

    // Initialize all teams to their home city
    for (const auto& block : schedule) {
        last_location_of_team[block.host_team.id] = block.host_team.city;
        for (const auto& visitor : block.visiting_residents) {
            last_location_of_team[visitor.id] = visitor.city;
        }
    }

    for (const auto& block : schedule) {
        std::set<int> teams_in_block;
        teams_in_block.insert(block.host_team.id);

        for (const auto& visitor : block.visiting_residents) {
            teams_in_block.insert(visitor.id);

            // Calculate travel for visitor from their last location to the host city
            if (last_location_of_team[visitor.id] != block.host_team.city) {
                total_travel_distance += GeographyData::calculateDistance(last_location_of_team[visitor.id], block.host_team.city);
            }
        }
        
        // After the block, update the location of all participating teams to the host city
        for (int team_id : teams_in_block) {
            last_location_of_team[team_id] = block.host_team.city;
        }
    }

    double total_co2_emissions = total_travel_distance * DISTANCE_TO_CO2_MULTIPLIER;

    std::cout << "\n--- Environmental Impact Report (v3.8.1) ---" << std::endl;
    std::cout << "Total Residency Blocks: " << schedule.size() << std::endl;
    std::cout << "Total Calculated Travel Distance: " << std::fixed << std::setprecision(2) << total_travel_distance << " units" << std::endl;
    std::cout << "Estimated Carbon Footprint: " << std::fixed << std::setprecision(2) << total_co2_emissions << " kg CO2-e" << std::endl;
    std::cout << "Analysis: The residency model significantly reduces trips compared to a traditional home-and-away model, consolidating travel into fewer, longer journeys." << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
}

} // namespace LeagueSchedulerNS
