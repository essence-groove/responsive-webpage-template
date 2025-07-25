#ifndef GAME_DATA_H
#define GAME_DATA_H

#include <string>
#include <vector>
#include "team_data.h" // Assuming team_data.h defines the Team struct

namespace LeagueSchedulerNS { // Ensure this is within the LeagueSchedulerNS namespace
enum class GameType {
    REGULAR_SEASON,
    CROSSROADS_GAME,
    // NEW: Type for Apex Residency games
    APEX_RESIDENCY_GAME 
};

struct Game {
    Team team1;
    Team team2;
    Team designated_home_team_for_batting; // Crucial for alternating first bat rule
    Team actual_host_stadium;
    std::string date;
    GameType game_type;
    // Potentially add more game-specific attributes here for future
};

struct ResidencyBlock {
    Team host_team;
    std::vector<Team> visiting_residents;
    std::vector<Game> games;
    std::string start_date; // Placeholder
    std::string end_date;   // Placeholder
    // Add an identifier for special residency types, if needed
    bool is_apex_residency = false; // NEW: Flag to identify Apex Residencies
};

} // namespace LeagueSchedulerNS

#endif // GAME_DATA_H
