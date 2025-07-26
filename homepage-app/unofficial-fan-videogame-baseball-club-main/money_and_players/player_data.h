/**
 * @file player_data.h
 * @brief Defines the data structure for a single player (v3.7.0).
 * @author  Eeshvar Das (Erik Douglas Ward)
 * @date 2025-Jul-25
 *
 * @copyright Copyright (C) 2025 Eeshvar Das (Erik Douglas Ward)
 *
 * @license SPDX-License-Identifier: AGPL-3.0-or-later
 *
 * Note: The structure of a player is unchanged in v3.7.0, as the updates
 * focus on high-level league scheduling logic rather than player attributes.
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
 *
 * This structure holds attributes that can be used by game simulation agents
 * to consider individual player performance and financial impact.
 */
struct Player {
    int id;
    std::string name;
    // Example attributes relevant to agentic control and simulation
    double skill_rating;        // Overall skill rating (e.g., 0.0 to 100.0)
    int games_played_season;    // Games played this season, for fatigue
    double fatigue_level;       // Current fatigue level (e.g., 0.0 to 1.0)

    // Financial attributes for "Money and Players" concept
    long long salary;           // Player's annual salary
    long long market_value;     // Player's market value

    bool is_star_player;        // Flag for star players, who might be subject to special agentic control

    // Performance metrics (simplified for this example)
    std::map<std::string, double> performance_metrics; // e.g., "batting_average", "era", "wins_above_replacement"

    // Default constructor
    Player() : id(0), name(""), skill_rating(0.0), games_played_season(0), fatigue_level(0.0),
               salary(0), market_value(0), is_star_player(false) {}

    // Parameterized constructor for easy initialization
    Player(int _id, const std::string& _name, double _skill_rating, long long _salary, long long _market_value, bool _is_star_player)
        : id(_id), name(_name), skill_rating(_skill_rating), games_played_season(0), fatigue_level(0.0),
          salary(_salary), market_value(_market_value), is_star_player(_is_star_player) {}
};

} // namespace LeagueSchedulerNS

#endif // PLAYER_DATA_H
