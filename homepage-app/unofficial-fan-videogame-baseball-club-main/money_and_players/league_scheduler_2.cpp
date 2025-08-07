/**
 * @file league_scheduler_2.cpp
 * @brief Implements the scheduling logic for the Ayurveda Project Management World baseball league (v3.9.2).
 * @author  Eeshvar Das (Erik Douglas Ward)
 * @date 2025-Aug-07
 *
 * @copyright Copyright (C) 2025 Eeshvar Das (Erik Douglas Ward)
 *
 * @license SPDX-License-Identifier: AGPL-3.0-or-later
 */

#include "league_scheduler_2.h"
#include <iostream>
#include <chrono>
#include <algorithm>
#include <random>
#include <map>
#include <vector>
#include <set>
#include "days.h"
#include "game_sorter.h"

namespace LeagueSchedulerNS {

// Constructor
LeagueScheduler2::LeagueScheduler2() : rng(std::chrono::steady_clock::now().time_since_epoch().count()) {}

// Main scheduling function
std::vector<ResidencyBlock> LeagueScheduler2::generateSeasonSchedule(std::vector<Team>& all_teams, int games_per_team) {
    std::vector<ResidencyBlock> season_schedule;
    std::map<int, TeamScheduleStatus> team_statuses;
    for(const auto& team : all_teams) {
        team_statuses[team.id] = TeamScheduleStatus();
    }

    int current_day = 1;
    const int MAX_SEASON_DAYS = 204; 
    const int APEX_EVENT_START_DAY = MAX_SEASON_DAYS - 45;
    const int MAX_REGULAR_SEASON_DAYS = APEX_EVENT_START_DAY - 1;
    const int MAX_HOST_BLOCKS = 5;

    // --- Phase 1: Schedule the Regular Season ---
    while (current_day < MAX_REGULAR_SEASON_DAYS) {
        std::vector<Team*> available_teams;
        for (auto& team : all_teams) {
            if (team_statuses[team.id].available_day <= current_day) {
                available_teams.push_back(&team);
            }
        }
        
        while (available_teams.size() >= 4) {
            Team* host = nullptr;
            std::vector<Team*> eligible_hosts;
            for(auto* team : available_teams) {
                if (team_statuses[team->id].host_blocks_assigned < MAX_HOST_BLOCKS) eligible_hosts.push_back(team);
            }
            if (eligible_hosts.empty()) break;

            int total_weight = 0;
            for(auto* team : eligible_hosts) total_weight += (1 + team->apex_points);
            std::uniform_int_distribution<> distrib(1, total_weight > 0 ? total_weight : 1);
            int winning_ticket = distrib(rng);
            int current_weight = 0;
            for(auto* team : eligible_hosts) {
                current_weight += (1 + team->apex_points);
                if (winning_ticket <= current_weight) {
                    host = team;
                    break;
                }
            }
            if (!host) host = eligible_hosts.back();

            available_teams.erase(std::remove_if(available_teams.begin(), available_teams.end(), 
                [&](Team* t){ return t->id == host->id; }), available_teams.end());

            std::vector<Team> visitors;
            std::vector<Team*> regional_visitors, other_visitors;
            for(auto* team : available_teams) {
                if (team->region_type == host->region_type) regional_visitors.push_back(team);
                else other_visitors.push_back(team);
            }
            std::shuffle(regional_visitors.begin(), regional_visitors.end(), rng);
            std::sort(other_visitors.begin(), other_visitors.end(), [&](Team* a, Team* b){
                return GeographyData::calculateDistance(host->city, a->city) > GeographyData::calculateDistance(host->city, b->city);
            });
            for(auto* team : regional_visitors) { if(visitors.size() < 3) visitors.push_back(*team); }
            for(auto* team : other_visitors) { if(visitors.size() < 3) visitors.push_back(*team); }
            
            for(const auto& v : visitors) {
                available_teams.erase(std::remove_if(available_teams.begin(), available_teams.end(), 
                    [&](Team* t){ return t->id == v.id; }), available_teams.end());
            }

            if (visitors.size() < 3) {
                available_teams.push_back(host);
                break; 
            }

            int block_duration = 0;
            ResidencyBlock block = createResidencyBlock(*host, visitors, current_day, block_duration);
            season_schedule.push_back(block);
            
            int end_day = current_day + block_duration;
            team_statuses[host->id].available_day = end_day;
            team_statuses[host->id].host_blocks_assigned++;
            for (const auto& visitor : visitors) team_statuses[visitor.id].available_day = end_day;
        }

        int next_free_day = MAX_REGULAR_SEASON_DAYS + 1;
        for(const auto& pair : team_statuses) {
            if (pair.second.available_day > current_day) next_free_day = std::min(next_free_day, pair.second.available_day);
        }
        current_day = (next_free_day > MAX_REGULAR_SEASON_DAYS) ? current_day + 1 : next_free_day;
    }

    // --- Phase 2: Schedule and Simulate the Apex Residency Event ---
    if (!apex_event_scheduled) {
        std::vector<Team*> participants = selectApexParticipants(all_teams);
        if (participants.size() >= 4) { // Need at least 4 for a tournament
            ResidencyBlock apex_block = createApexResidency(participants, APEX_EVENT_START_DAY);
            season_schedule.push_back(apex_block);
            simulateApexEventAndAwardPoints(apex_block, all_teams);
            apex_event_scheduled = true;
        }
    }

    std::cout << "Generated " << season_schedule.size() << " total blocks, including Apex event." << std::endl;
    return season_schedule;
}

/**
 * @brief v3.9.1: Creates a standard residency block with improved game density for visitors.
 */
ResidencyBlock LeagueScheduler2::createResidencyBlock(const Team& host, const std::vector<Team>& visitors, int start_day, int& out_duration_days) {
    ResidencyBlock block;
    block.host_team = host;
    block.visiting_residents = visitors;
    block.start_date = "Day " + std::to_string(start_day);
    int day_offset = 1;

    // --- v3.9.1 Dormancy Fix: Cluster games for visitors ---
    for (const auto& visitor : visitors) {
        Game g1 = {.team1 = visitor, .team2 = host, .designated_home_team_for_batting = host, .actual_host_stadium = host, .date = "Day " + std::to_string(start_day + day_offset++), .game_type = GameType::REGULAR_SEASON};
        block.games.push_back(g1);
    }
    day_offset++; // Rest day

    for (size_t i = 0; i < visitors.size(); ++i) {
        for (size_t j = i + 1; j < visitors.size(); ++j) {
            const auto& visitor1 = visitors[i];
            const auto& visitor2 = visitors[j];
            std::vector<Game> series;
            if (visitor1.region_type == visitor2.region_type) {
                series = generateNeutralSiteSeries(visitor1, visitor2, host, 1, GameType::REGIONAL_GAME, start_day, day_offset);
            } else {
                series = generateNeutralSiteSeries(visitor1, visitor2, host, 1, GameType::CROSSROADS_GAME, start_day, day_offset);
            }
            block.games.insert(block.games.end(), series.begin(), series.end());
        }
    }
    day_offset++; // Rest day

    for (const auto& visitor : visitors) {
        Game g2 = {.team1 = host, .team2 = visitor, .designated_home_team_for_batting = visitor, .actual_host_stadium = host, .date = "Day " + std::to_string(start_day + day_offset++), .game_type = GameType::REGULAR_SEASON};
        block.games.push_back(g2);
    }
    
    GameSorter sorter;
    sorter.sortSchedule(block.games);

    out_duration_days = day_offset + 1; 
    block.end_date = "Day " + std::to_string(start_day + out_duration_days - 1);
    return block;
}

/**
 * @brief v3.9.1: Creates the Apex Residency with a tournament structure.
 */
ResidencyBlock LeagueScheduler2::createApexResidency(std::vector<Team*>& participants, int start_day) {
    ResidencyBlock block;
    block.is_apex_residency = true;
    if (participants.empty()) return block;
    block.host_team = *participants[0]; 
    for(size_t i = 0; i < participants.size(); ++i) {
        block.visiting_residents.push_back(*participants[i]);
    }
    block.start_date = "Day " + std::to_string(start_day);
    int day_offset = 1;

    block.games = createApexTournamentGames(participants, block.host_team, start_day, day_offset);
    
    const int APEX_DURATION_DAYS = day_offset + 3; // Add a few final rest days
    block.end_date = "Day " + std::to_string(start_day + APEX_DURATION_DAYS);
    return block;
}

/**
 * @brief v3.9.1: New helper to create the Apex tournament games (seeding + playoffs).
 */
std::vector<Game> LeagueScheduler2::createApexTournamentGames(std::vector<Team*>& participants, const Team& host_team, int start_day, int& day_offset) {
    std::vector<Game> games;
    std::map<int, int> seeding_wins;

    // --- Seeding Phase: Single Round-Robin ---
    for (size_t i = 0; i < participants.size(); ++i) {
        for (size_t j = i + 1; j < participants.size(); ++j) {
            Game game;
            game.team1 = *participants[i]; game.team2 = *participants[j];
            game.designated_home_team_for_batting = *participants[j];
            game.actual_host_stadium = host_team;
            game.date = "Day " + std::to_string(start_day + day_offset);
            game.game_type = GameType::APEX_RESIDENCY_GAME;
            games.push_back(game);
            day_offset += 2; // Game + Rest Day

            int winner_id = (rng() % 2 == 0) ? game.team1.id : game.team2.id;
            seeding_wins[winner_id]++;
        }
    }

    // --- Playoff Phase: Top 4 Teams ---
    std::vector<std::pair<int, int>> sorted_seeds;
    for(auto const& [team_id, wins] : seeding_wins) sorted_seeds.push_back({team_id, wins});
    std::sort(sorted_seeds.begin(), sorted_seeds.end(), [](const auto& a, const auto& b){ return a.second > b.second; });

    if (sorted_seeds.size() >= 4) {
        Team* seed1 = *std::find_if(participants.begin(), participants.end(), [&](Team* t){ return t->id == sorted_seeds[0].first; });
        Team* seed2 = *std::find_if(participants.begin(), participants.end(), [&](Team* t){ return t->id == sorted_seeds[1].first; });
        Team* seed3 = *std::find_if(participants.begin(), participants.end(), [&](Team* t){ return t->id == sorted_seeds[2].first; });
        Team* seed4 = *std::find_if(participants.begin(), participants.end(), [&](Team* t){ return t->id == sorted_seeds[3].first; });

        day_offset += 2; // Rest days before playoffs

        Game semi1 = {.team1 = *seed1, .team2 = *seed4, .designated_home_team_for_batting = *seed1, .actual_host_stadium = host_team, .date = "Day " + std::to_string(start_day + day_offset), .game_type = GameType::APEX_RESIDENCY_GAME};
        Game semi2 = {.team1 = *seed2, .team2 = *seed3, .designated_home_team_for_batting = *seed2, .actual_host_stadium = host_team, .date = "Day " + std::to_string(start_day + day_offset), .game_type = GameType::APEX_RESIDENCY_GAME};
        games.push_back(semi1);
        games.push_back(semi2);
        day_offset += 3; // Game day + rest days

        Game final_game = {.team1 = *seed1, .team2 = *seed2, .designated_home_team_for_batting = *seed1, .actual_host_stadium = host_team, .date = "Day " + std::to_string(start_day + day_offset), .game_type = GameType::APEX_RESIDENCY_GAME};
        games.push_back(final_game);
        day_offset += 2;
    }
    
    return games;
}


/**
 * @brief Selects teams for the Apex event and sets player ApexStatus.
 */
std::vector<Team*> LeagueScheduler2::selectApexParticipants(std::vector<Team>& all_teams) {
    std::vector<std::pair<Player*, Team*>> all_players;
    for (auto& team : all_teams) {
        for (auto& player : team.players) {
            all_players.push_back({&player, &team});
        }
    }

    std::sort(all_players.begin(), all_players.end(), [](const auto& a, const auto& b) {
        return a.first->performance_score > b.first->performance_score;
    });

    const int NUM_APEX_PLAYERS = 16;
    std::set<Team*> qualifying_teams_set;
    std::vector<std::pair<Player*, Team*>> top_players_with_teams;
    for (int i = 0; i < NUM_APEX_PLAYERS && i < all_players.size(); ++i) {
        qualifying_teams_set.insert(all_players[i].second);
        top_players_with_teams.push_back(all_players[i]);
    }

    std::cout << "\n--- Apex Player Selection (v3.9.1) ---" << std::endl;
    for (auto& player_team_pair : top_players_with_teams) {
        Player* player = player_team_pair.first;
        Team* team = player_team_pair.second;
        
        if (qualifying_teams_set.count(team) > 0) {
            player->apex_status = ApexStatus::TeamParticipant;
        } else {
            player->apex_status = ApexStatus::GreyUniform;
            std::cout << "Player " << player->name << " (" << team->city 
                      << ") selected as a Grey Uniform participant." << std::endl;
        }
    }
    for (auto* team : qualifying_teams_set) {
        for (auto& player : team->players) {
            if (player.apex_status == ApexStatus::None) {
                 player.apex_status = ApexStatus::TeamParticipant;
            }
        }
    }

    std::vector<Team*> participants(qualifying_teams_set.begin(), qualifying_teams_set.end());
    
    std::cout << "Selected " << participants.size() << " teams for the Apex Residency based on the top " << NUM_APEX_PLAYERS << " players." << std::endl;
    std::cout << "------------------------------------" << std::endl;
    
    return participants;
}


/**
 * @brief Simulates the outcome of the Apex event and awards points to teams.
 */
void LeagueScheduler2::simulateApexEventAndAwardPoints(const ResidencyBlock& apex_block, std::vector<Team>& all_teams) {
    std::map<int, int> apex_wins;
    std::uniform_int_distribution<> distrib(0, 1);
    for (const auto& game : apex_block.games) {
        int winner_id = (distrib(rng) == 0) ? game.team1.id : game.team2.id;
        apex_wins[winner_id]++;
    }

    std::vector<std::pair<int, int>> sorted_teams;
    for (auto const& [team_id, wins] : apex_wins) {
        sorted_teams.push_back({team_id, wins});
    }
    std::sort(sorted_teams.begin(), sorted_teams.end(), [](const auto& a, const auto& b){
        return a.second > b.second;
    });

    const int WINNER_POINTS = 10;
    const int RUNNER_UP_POINTS = 5;
    const int PARTICIPATION_POINTS = 1;

    std::cout << "\n--- Apex Event Results ---" << std::endl;
    for (size_t i = 0; i < sorted_teams.size(); ++i) {
        int team_id = sorted_teams[i].first;
        int points_to_award = 0;
        if (i == 0) points_to_award = WINNER_POINTS;
        else if (i == 1) points_to_award = RUNNER_UP_POINTS;
        else points_to_award = PARTICIPATION_POINTS;

        auto it = std::find_if(all_teams.begin(), all_teams.end(), [team_id](const Team& t){
            return t.id == team_id;
        });
        if (it != all_teams.end()) {
            it->apex_points += points_to_award;
            std::cout << "Team " << it->city << " finished rank " << i+1 << " and earned " << points_to_award << " Apex Points." << std::endl;
        }
    }
    std::cout << "--------------------------" << std::endl;
}


/**
 * @brief Generates a series of neutral-site games.
 */
std::vector<Game> LeagueScheduler2::generateNeutralSiteSeries(const Team& visitor1, const Team& visitor2, const Team& host_stadium, int num_games, GameType game_type, int start_day, int& day_offset) {
    std::vector<Game> series_games;
    std::uniform_int_distribution<> distrib(0, 1);
    bool visitor1_is_initial_home_batter = (distrib(rng) == 0);

    for (int i = 0; i < num_games; ++i) {
        Game game;
        game.actual_host_stadium = host_stadium;
        game.game_type = game_type;
        game.date = "Day " + std::to_string(start_day + day_offset);

        bool v1_bats_home_this_game = (i % 2 == 0) ? visitor1_is_initial_home_batter : !visitor1_is_initial_home_batter;

        if (v1_bats_home_this_game) {
            game.team1 = visitor2;
            game.team2 = visitor1;
            game.designated_home_team_for_batting = visitor1;
        } else {
            game.team1 = visitor1;
            game.team2 = visitor2;
            game.designated_home_team_for_batting = visitor2;
        }
        series_games.push_back(game);
        
        day_offset += (i < num_games - 1) ? 2 : 1;
    }
    day_offset++;
    return series_games;
}

} // namespace LeagueSchedulerNS
