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
#include "money_and_players/game_sorter.h" // v3.9.2: Include for sorting blocks

// Using the new namespace explicitly
using namespace LeagueSchedulerNS;

int main() {
    std::cout << "Starting APMW League Schedule Generation (C++ 3.9.2 with Money & Players)" << std::endl;

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

    // Populate teams with players and set trade preferences
    int current_player_id = 1;
    for (auto& team : all_teams) {
        team.players.emplace_back(current_player_id++, "PlayerA_" + team.city, 85.0, 5000000, 10000000, false);
        team.players.emplace_back(current_player_id++, "PlayerB_" + team.city, 80.0, 3000000, 5000000, false);
        if (team.city == "Los Angeles" || team.city == "New York" || team.city == "Austin" || team.city == "Seattle") {
            team.players.emplace_back(current_player_id++, "StarPlayer_" + team.city, 95.0, 15000000, 25000000, true);
        }
    }
    
    // v3.9.2: Set a specific player to veto trades to a new region
    all_teams[0].players[0].will_accept_trade_to_new_region = false;
    std::cout << "\nNOTE: Player " << all_teams[0].players[0].name << " will veto any trade to a new region." << std::endl;


    // --- Simulate Regular Season Performance ---
    std::mt19937 perf_rng(std::chrono::steady_clock::now().time_since_epoch().count());
    std::normal_distribution<> distribution(0.0, 5.0);
    for (auto& team : all_teams) {
        for (auto& player : team.players) {
            player.performance_score = player.skill_rating + distribution(perf_rng);
        }
    }

    // --- Generate Season Schedule ---
    LeagueScheduler2 scheduler;
    std::vector<ResidencyBlock> season_schedule = scheduler.generateSeasonSchedule(all_teams, 98);

    // --- Sort and Print Schedule Report ---
    // Note: Sorting ResidencyBlocks still requires a date parser.
    // The new GameSorter is for sorting games within a block.
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
    if (all_teams.size() >= 5) {
        // Propose a trade that will be vetoed (Maine is Keystone, Atlanta is Tidewater)
        std::vector<Player*> players_from_maine = {&all_teams[0].players[0]};
        trade_agent.proposeTrade(all_teams[0], all_teams[4], players_from_maine);

        // Propose a trade that will succeed (Maine to New York is within the same region)
        std::vector<Player*> another_player_from_maine = {&all_teams[0].players[1]};
        trade_agent.proposeTrade(all_teams[0], all_teams[1], another_player_from_maine);
    }

    return 0;
}
