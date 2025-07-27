/**
 * @file main.cpp
 * @brief Main entry point for the unofficial-fan-videogame-baseball-club game (v3.8.1).
 * @author  Eeshvar Das (Erik Douglas Ward)
 * @date 2025-Jul-26
 *
 * @copyright Copyright (C) 2025 Eeshvar Das (Erik Douglas Ward)
 *
 * @license SPDX-License-Identifier: AGPL-3.0-or-later
 */

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include "money_and_players/league_scheduler_2.h"
#include "money_and_players/game_data.h"
#include "money_and_players/geography_data.h"
#include "money_and_players/environmental_agent.h" // v3.8.1: Include new agent

// Using the new namespace explicitly
using namespace LeagueSchedulerNS;

// Helper function to convert GameType enum to string
std::string getGameTypeString(GameType type) {
    switch (type) {
        case GameType::REGIONAL_GAME: return "REGIONAL_GAME";
        case GameType::CROSSROADS_GAME: return "CROSSROADS_GAME";
        case GameType::APEX_RESIDENCY_GAME: return "APEX_RESIDENCY_GAME";
        case GameType::REGULAR_SEASON: default: return "REGULAR_SEASON";
    }
}

// Helper to extract the day number
int getDayNumber(const std::string& day_str) {
    try {
        return std::stoi(day_str.substr(4));
    } catch (const std::exception& e) {
        return -1;
    }
}


int main() {
    std::cout << "Starting APMW League Schedule Generation (C++ 3.8.1 with Money & Players)" << std::endl;

    std::vector<Team> all_teams;
    int current_team_id = 1;

    // Atlantic Union
    all_teams.emplace_back(current_team_id++, "Maine", "Lumberjack Spirit", UnionType::ATLANTIC, RegionType::KEYSTONE);
    all_teams.emplace_back(current_team_id++, "New York", "Metropolitan Spirit", UnionType::ATLANTIC, RegionType::KEYSTONE);
    all_teams.emplace_back(current_team_id++, "Philadelphia", "Founder Spirit", UnionType::ATLANTIC, RegionType::KEYSTONE);
    all_teams.emplace_back(current_team_id++, "Pittsburgh", "Iron Spirit", UnionType::ATLANTIC, RegionType::KEYSTONE);
    all_teams.emplace_back(current_team_id++, "Atlanta", "Peach Blossom", UnionType::ATLANTIC, RegionType::TIDEWATER);
    all_teams.emplace_back(current_team_id++, "Miami", "Manatee Calm", UnionType::ATLANTIC, RegionType::TIDEWATER);
    all_teams.emplace_back(current_team_id++, "Charlotte", "Aviator Grit", UnionType::ATLANTIC, RegionType::TIDEWATER);
    all_teams.emplace_back(current_team_id++, "Cleveland", "Guardian Resolve", UnionType::ATLANTIC, RegionType::THE_CONFLUENCE);
    all_teams.emplace_back(current_team_id++, "Detroit", "Automaker Drive", UnionType::ATLANTIC, RegionType::THE_CONFLUENCE);

    // Pacific Union
    all_teams.emplace_back(current_team_id++, "Los Angeles", "Star Radiance", UnionType::PACIFIC, RegionType::GOLDEN_PENNANT);
    all_teams.emplace_back(current_team_id++, "San Diego", "Surf Vibe", UnionType::PACIFIC, RegionType::GOLDEN_PENNANT);
    all_teams.emplace_back(current_team_id++, "San Francisco", "Seal Endurance", UnionType::PACIFIC, RegionType::GOLDEN_PENNANT);
    all_teams.emplace_back(current_team_id++, "Seattle", "Rainier Force", UnionType::PACIFIC, RegionType::CASCADE_TERRITORY);
    all_teams.emplace_back(current_team_id++, "Austin", "Armadillo Resilience", UnionType::PACIFIC, RegionType::THE_SUNSTONE_DIVISION);
    all_teams.emplace_back(current_team_id++, "Dallas", "Lonestar Pride", UnionType::PACIFIC, RegionType::THE_SUNSTONE_DIVISION);
    all_teams.emplace_back(current_team_id++, "Denver", "Summit Peak", UnionType::PACIFIC, RegionType::THE_SUNSTONE_DIVISION);
    all_teams.emplace_back(current_team_id++, "St. Louis", "Archer Aim", UnionType::PACIFIC, RegionType::THE_HEARTLAND_CORE);
    all_teams.emplace_back(current_team_id++, "Kansas City", "Monarch Reign", UnionType::PACIFIC, RegionType::THE_HEARTLAND_CORE);

    LeagueScheduler2 scheduler;
    int games_per_team = 98;
    std::vector<ResidencyBlock> season_schedule = scheduler.generateSeasonSchedule(all_teams, games_per_team);

    std::sort(season_schedule.begin(), season_schedule.end(), [](const ResidencyBlock& a, const ResidencyBlock& b){
        return getDayNumber(a.start_date) < getDayNumber(b.start_date);
    });

    std::ofstream reportFile("schedule_report_v3.8.md");
    reportFile << "# APMW Season Schedule Report (v3.8)\n\n";

    std::cout << "\n--- Sample Season Schedule (v3.8.1) ---" << std::endl;
    for (const auto& block : season_schedule) {
        reportFile << "## Residency Block: " << block.host_team.city << " Host (" << block.start_date << " to " << block.end_date << ")\n\n";
        int last_printed_day = getDayNumber(block.start_date) - 1;

        for (const auto& game : block.games) {
            int current_game_day = getDayNumber(game.date);
            if (current_game_day > last_printed_day + 1) {
                for (int day = last_printed_day + 1; day < current_game_day; ++day) {
                    std::string day_str = "Day " + std::to_string(day);
                    std::string note = "Travel / Rest Day. Environmental Adjustment: Reduces frequent travel and carbon emissions within the extended residency model.";
                    reportFile << "- **" << day_str << ":** TRAVEL / REST DAY. **Environmental Adjustment Note:** " << note << "\n";
                }
            }
            const Team& home_batting_team = game.designated_home_team_for_batting;
            const Team& away_batting_team = (game.team1 == home_batting_team) ? game.team2 : game.team1;
            std::string game_type_str = getGameTypeString(game.game_type);
            reportFile << "- **" << game.date << ":** " << away_batting_team.city << " (First Bat) vs. " << home_batting_team.city << " (Second Bat) at " << game.actual_host_stadium.city << " Stadium. **Type:** " << game_type_str << "\n";
            if (game.game_type == GameType::REGIONAL_GAME) {
                double distance = GeographyData::calculateDistance(away_batting_team.city, home_batting_team.city);
                std::string travel_note = (distance < 5.0) ? "This is a local derby, facilitating low-emission fan travel by train for a short-distance journey." : "This matchup allows for efficient regional fan travel by train, minimizing the carbon footprint compared to air travel.";
                reportFile << "  - *Note: This is a **Regional Game**. **Environmental Enhancement:** " << travel_note << "*\n";
            }
            last_printed_day = current_game_day;
        }
        int block_end_day = getDayNumber(block.end_date);
        if (block_end_day > last_printed_day) {
             for (int day = last_printed_day + 1; day <= block_end_day; ++day) {
                std::string day_str = "Day " + std::to_string(day);
                std::string note = "Departure / Rest Day. Environmental Adjustment: Optimizes team travel logistics, reducing overall carbon footprint.";
                reportFile << "- **" << day_str << ":** TRAVEL / REST DAY. **Environmental Adjustment Note:** " << note << "\n";
            }
        }
        reportFile << "\n";
    }
    
    std::cout << "Schedule generation complete. Report written to schedule_report_v3.8.md" << std::endl;
    reportFile.close();

    // v3.8.1: Run the new Environmental Impact Evaluation Agent
    EnvironmentalAgent env_agent;
    env_agent.generateReport(season_schedule);

    return 0;
}
