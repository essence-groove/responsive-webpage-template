/**
 * @file main.cpp
 * @brief Main entry point for the unofficial-fan-videogame-baseball-club game (v3.9.2).
 * @author  Eeshvar Das (Erik Douglas Ward)
 * @date 2025-Jul-27
 *
 * @copyright Copyright (C) 2025 Eeshvar Das (Erik Douglas Ward)
 *
 * @license SPDX-License-Identifier: AGPL-3.0-or-later
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <random>
#include <chrono>
#include "money_and_players/league_scheduler_2.h"
#include "money_and_players/environmental_agent.h"
#include "money_and_players/trade_agent.h"
#include "money_and_players/report_logic.h"
#include "money_and_players/game_sorter.h"
#include "money_and_players/financial_agent.h"
#include "money_and_players/persistence_agent.h"
#include "money_and_players/league_state.h"
#include "money_and_players/days.h" // FIX: Include the header for DateConverter

// Using the new namespace explicitly
using namespace LeagueSchedulerNS;

// Function to initialize a new league if no save file is found
void initializeNewLeague(LeagueState& state) {
    std::cout << "Initializing a new league for the 2025 season." << std::endl;
    state.current_season_year = 2025;
    int current_team_id = 1;

    // Atlantic Union
    state.teams.emplace_back(current_team_id++, "Maine", "Lumberjack Spirit", UnionType::ATLANTIC, RegionType::KEYSTONE);
    state.teams.emplace_back(current_team_id++, "New York", "Metropolitan Spirit", UnionType::ATLANTIC, RegionType::KEYSTONE);
    state.teams.emplace_back(current_team_id++, "Philadelphia", "Founder Spirit", UnionType::ATLANTIC, RegionType::KEYSTONE);
    state.teams.emplace_back(current_team_id++, "Pittsburgh", "Iron Spirit", UnionType::ATLANTIC, RegionType::KEYSTONE);
    state.teams.emplace_back(current_team_id++, "Atlanta", "Peach Blossom", UnionType::ATLANTIC, RegionType::TIDEWATER);
    state.teams.emplace_back(current_team_id++, "Miami", "Manatee Calm", UnionType::ATLANTIC, RegionType::TIDEWATER);
    state.teams.emplace_back(current_team_id++, "Charlotte", "Aviator Grit", UnionType::ATLANTIC, RegionType::TIDEWATER);
    state.teams.emplace_back(current_team_id++, "Cleveland", "Sentinel Resolve", UnionType::ATLANTIC, RegionType::THE_CONFLUENCE);
    state.teams.emplace_back(current_team_id++, "Detroit", "Automaker Drive", UnionType::ATLANTIC, RegionType::THE_CONFLUENCE);

    // Pacific Union
    state.teams.emplace_back(current_team_id++, "Los Angeles", "Star Radiance", UnionType::PACIFIC, RegionType::GOLDEN_PENNANT);
    state.teams.emplace_back(current_team_id++, "San Diego", "Surf Vibe", UnionType::PACIFIC, RegionType::GOLDEN_PENNANT);
    state.teams.emplace_back(current_team_id++, "San Francisco", "Seal Endurance", UnionType::PACIFIC, RegionType::GOLDEN_PENNANT);
    state.teams.emplace_back(current_team_id++, "Seattle", "Rainier Force", UnionType::PACIFIC, RegionType::CASCADE_TERRITORY);
    state.teams.emplace_back(current_team_id++, "Austin", "Armadillo Resilience", UnionType::PACIFIC, RegionType::THE_SUNSTONE_DIVISION);
    state.teams.emplace_back(current_team_id++, "Dallas", "Lonestar Pride", UnionType::PACIFIC, RegionType::THE_SUNSTONE_DIVISION);
    state.teams.emplace_back(current_team_id++, "Denver", "Summit Peak", UnionType::PACIFIC, RegionType::THE_SUNSTONE_DIVISION);
    state.teams.emplace_back(current_team_id++, "St. Louis", "Archer Aim", UnionType::PACIFIC, RegionType::THE_HEARTLAND_CORE);
    state.teams.emplace_back(current_team_id++, "Kansas City", "Monarch Reign", UnionType::PACIFIC, RegionType::THE_HEARTLAND_CORE);

    // Populate teams with players
    int current_player_id = 1;
    for (auto& team : state.teams) {
        team.players.emplace_back(current_player_id++, "PlayerA_" + team.city, 85.0, 5000000, 10000000, false);
        team.players.emplace_back(current_player_id++, "PlayerB_" + team.city, 80.0, 3000000, 5000000, false);
        if (team.city == "Los Angeles" || team.city == "New York" || team.city == "Austin" || team.city == "Seattle") {
            team.players.emplace_back(current_player_id++, "StarPlayer_" + team.city, 95.0, 15000000, 25000000, true);
        }
    }
}


int main() {
    std::cout << "Starting APMW League Simulation (C++ 3.9.2)" << std::endl;

    // --- v3.9.2: Manage League State ---
    PersistenceAgent persistence_agent;
    const std::string save_filename = "apmw_league_save.dat";
    LeagueState league_state = persistence_agent.loadState(save_filename);

    // If loading failed (or no save file exists), initialize a new league
    if (league_state.teams.empty()) {
        initializeNewLeague(league_state);
    }
    
    // Set a specific player to veto trades to a new region for demonstration
    league_state.teams[0].players[0].will_accept_trade_to_new_region = false;
    std::cout << "\nNOTE: Player " << league_state.teams[0].players[0].name << " will veto any trade to a new region." << std::endl;

    // --- v3.9.2: Calculate Initial Payrolls ---
    FinancialAgent financial_agent;
    std::cout << "\n--- Initial Team Payrolls ---" << std::endl;
    for (auto& team : league_state.teams) {
        financial_agent.calculateTeamPayroll(team);
    }
    std::cout << "-----------------------------" << std::endl;


    // --- Simulate Regular Season Performance ---
    std::mt19937 perf_rng(std::chrono::steady_clock::now().time_since_epoch().count());
    std::normal_distribution<> distribution(0.0, 5.0);
    for (auto& team : league_state.teams) {
        for (auto& player : team.players) {
            player.performance_score = player.skill_rating + distribution(perf_rng);
        }
    }

    // --- Generate Season Schedule ---
    LeagueScheduler2 scheduler;
    std::vector<ResidencyBlock> season_schedule = scheduler.generateSeasonSchedule(league_state.teams, 98);

    // --- Sort and Print Schedule Report ---
    DateConverter date_converter;
    std::sort(season_schedule.begin(), season_schedule.end(), [&](const ResidencyBlock& a, const ResidencyBlock& b){
        return date_converter.getDayNumber(a.start_date) < date_converter.getDayNumber(b.start_date);
    });
    
    ReportGenerator report_generator;
    report_generator.generate(season_schedule, "schedule_report_v3.9.md");

    // --- Run Environmental Report ---
    EnvironmentalAgent env_agent;
    env_agent.generateReport(season_schedule);

    // --- Demonstrate Trade Agent ---
    TradeAgent trade_agent;
    if (league_state.teams.size() >= 5) {
        // Propose a trade that will be vetoed (Maine is Keystone, Atlanta is Tidewater)
        std::vector<Player*> players_from_maine = {&league_state.teams[0].players[0]};
        trade_agent.proposeTrade(league_state.teams[0], league_state.teams[4], players_from_maine);

        // Propose a trade that will succeed (Maine to New York is within the same region)
        std::vector<Player*> another_player_from_maine = {&league_state.teams[0].players[1]};
        trade_agent.proposeTrade(league_state.teams[0], league_state.teams[1], another_player_from_maine);
    }
    
    // --- v3.9.2: Save League State at End of Season ---
    persistence_agent.saveState(league_state, save_filename);

    return 0;
}
