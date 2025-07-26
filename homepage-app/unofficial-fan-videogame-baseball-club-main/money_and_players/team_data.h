<code language="cpp">
/**
 * @file team_data.h
 * @brief Defines the data structure for a single team (v3.7.0).
 * @author  Eeshvar Das (Erik Douglas Ward)
 * @date 2025-Jul-25
 *
 * @copyright Copyright (C) 2025 Eeshvar Das (Erik Douglas Ward)
 *
 * @license SPDX-License-Identifier: AGPL-3.0-or-later
 *
 * Note: The structure of a team is unchanged in v3.7.0, as the updates
 * focus on high-level league scheduling logic rather than team attributes.
 */

#ifndef TEAM_DATA_H
#define TEAM_DATA_H

#include <string>
#include <vector>
#include "player_data.h" // Include the player data structure

namespace LeagueSchedulerNS {

// Enum for Union types (e.g., Atlantic Union, Pacific Union)
enum class UnionType {
    ATLANTIC,
    PACIFIC,
    UNKNOWN
};

// Enum for Region types within Unions, used for scheduling Regional Games in v3.7.0
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
    std::string mascot_theme; // Placeholder for mascot or fan theme
    UnionType union_type;
    RegionType region_type;
    int wins;
    int losses;
    // A roster of Player objects for this team
    std::vector<Player> players;

    // Default constructor
    Team() : id(0), city(""), mascot_theme(""), union_type(UnionType::UNKNOWN),
             region_type(RegionType::UNKNOWN), wins(0), losses(0) {}

    // Parameterized constructor for easy initialization
    Team(int _id, const std::string& _city, const std::string& _mascot_theme,
         UnionType _union_type, RegionType _region_type)
        : id(_id), city(_city), mascot_theme(_mascot_theme),
          union_type(_union_type), region_type(_region_type),
          wins(0), losses(0) {}
    
    // Overload the == operator for easy comparison
    bool operator==(const Team& other) const {
        return this->id == other.id;
    }
};

} // namespace LeagueSchedulerNS

#endif // TEAM_DATA_H
```
