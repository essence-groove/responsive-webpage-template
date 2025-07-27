/**
 * @file player_data.h
 * @brief Defines the data structure for a single player (v3.9.0).
 * @author  Eeshvar Das (Erik Douglas Ward)
 * @date 2025-Jul-27
 *
 * @copyright Copyright (C) 2025 Eeshvar Das (Erik Douglas Ward)
 *
 * @license SPDX-License-Identifier: AGPL-3.0-or-later
 */

#ifndef PLAYER_DATA_H
#define PLAYER_DATA_H

#include <string>
#include <vector>
#include <map>

namespace LeagueSchedulerNS {

/**
 * @struct Player
 * @brief Represents a single player in the league.
 */
struct Player {
    int id;
    std::string name;
    double skill_rating;
    int games_played_season;
    double fatigue_level;
    long long salary;
    long long market_value;
    bool is_star_player;
    
    // v3.9.0: Add performance score for Apex selection
    double performance_score = 0.0; 

    std::map<std::string, double> performance_metrics;

    // Default constructor
    Player() : id(0), name(""), skill_rating(0.0), games_played_season(0), fatigue_level(0.0),
               salary(0), market_value(0), is_star_player(false), performance_score(0.0) {}

    // Parameterized constructor for easy initialization
    Player(int _id, const std::string& _name, double _skill_rating, long long _salary, long long _market_value, bool _is_star_player)
        : id(_id), name(_name), skill_rating(_skill_rating), games_played_season(0), fatigue_level(0.0),
          salary(_salary), market_value(_market_value), is_star_player(_is_star_player) {
        // For now, base performance score on skill rating for demonstration
        performance_score = _skill_rating;
    }
};

} // namespace LeagueSchedulerNS

#endif // PLAYER_DATA_H
