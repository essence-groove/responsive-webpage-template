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

    // ... (Schedule printing logic remains the same) ...
    
    std::cout << "\nSchedule generation complete." << std::endl;

    // v3.8.1: Run the new Environmental Impact Evaluation Agent
    EnvironmentalAgent env_agent;
    env_agent.generateReport(season_schedule);

    return 0;
}
