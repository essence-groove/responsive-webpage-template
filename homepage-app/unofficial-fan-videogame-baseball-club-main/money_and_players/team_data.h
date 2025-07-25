#ifndef TEAM_DATA_H
#define TEAM_DATA_H

#include <string>
#include <vector>
#include "player_data.h" // Include the new player data structure

// Enum for Union types (e.g., Atlantic Union, Pacific Union)
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

// Represents a baseball team in the league.
// For C++ 3.5.0, no official team name field is included,
// but city and mascot_theme are used as placeholders.
struct Team {
    int id;
    std::string city;
    std::string mascot_theme; // Placeholder for mascot or fan theme
    UnionType union_type;
    RegionType region_type;
    int wins;
    int losses;
    // New: A roster of Player objects for this team
    std::vector<Player> players;

    // Default constructor
    Team() : id(0), city(""), mascot_theme(""), union_type(UnionType::UNKNOWN),
             region_type(RegionType::UNKNOWN), wins(0), losses(0) {}

    // Parameterized constructor
    Team(int _id, const std::string& _city, const std::string& _mascot_theme,
         UnionType _union_type, RegionType _region_type)
        : id(_id), city(_city), mascot_theme(_mascot_theme),
          union_type(_union_type), region_type(_region_type),
          wins(0), losses(0) {}
};

#endif // TEAM_DATA_H
