/**
 * @file team_data.h
 * @brief Defines the data structure for a single team (v3.9.2).
 * @author  Eeshvar Das (Erik Douglas Ward)
 * @date 2025-Jul-27
 *
 * @copyright Copyright (C) 2025 Eeshvar Das (Erik Douglas Ward)
 *
 * @license SPDX-License-Identifier: AGPL-3.0-or-later
 */

#ifndef TEAM_DATA_H
#define TEAM_DATA_H

#include <string>
#include <vector>
#include "player_data.h"

namespace LeagueSchedulerNS {

// Enum for Union types
enum class UnionType {
    ATLANTIC,
    PACIFIC,
    UNKNOWN
};

// Enum for Region types within Unions
enum class RegionType {
    KEYSTONE,
    TIDEWATER,
    THE_CONFLUENCE,
    GOLDEN_PENNANT,
    CASCADE_TERRITORY,
    THE_SUNSTONE_DIVISION,
    THE_HEARTLAND_CORE,
    UNKNOWN
};

/**
 * @struct Team
 * @brief Represents a baseball team in the league.
 */
struct Team {
    int id;
    std::string city;
    std::string mascot_theme;
    UnionType union_type;
    RegionType region_type;
    int wins;
    int losses;
    int apex_points = 0;

    // v3.9.2: Expanded financial data model
    long long total_revenue = 50000000; // Placeholder starting revenue
    long long player_payroll = 0;
    long long marketing_budget = 5000000;
    long long stadium_expenses = 10000000;

    std::vector<Player> players;

    // Default constructor
    Team() : id(0), city(""), mascot_theme(""), union_type(UnionType::UNKNOWN),
             region_type(RegionType::UNKNOWN), wins(0), losses(0), apex_points(0) {}

    // Parameterized constructor
    Team(int _id, const std::string& _city, const std::string& _mascot_theme,
         UnionType _union_type, RegionType _region_type)
        : id(_id), city(_city), mascot_theme(_mascot_theme),
          union_type(_union_type), region_type(_region_type),
          wins(0), losses(0), apex_points(0) {}
    
    // Overload the == operator for easy comparison
    bool operator==(const Team& other) const {
        return this->id == other.id;
    }
};

} // namespace LeagueSchedulerNS

#endif // TEAM_DATA_H
