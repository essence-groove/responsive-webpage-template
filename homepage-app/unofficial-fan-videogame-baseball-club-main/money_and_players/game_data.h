/**
 * @file game_data.h
 * @brief Defines core data structures for games and residency blocks (v3.7.0).
 * @author  Eeshvar Das (Erik Douglas Ward)
 * @date 2025-Jul-26
 *
 * @copyright Copyright (C) 2025 Eeshvar Das (Erik Douglas Ward)
 *
 * @license SPDX-License-Identifier: AGPL-3.0-or-later
 */

#ifndef GAME_DATA_H
#define GAME_DATA_H

#include <string>
#include <vector>
#include "team_data.h" // Defines the Team struct

namespace LeagueSchedulerNS {

/**
 * @enum GameType
 * @brief Defines the different categories of games in the APMW schedule.
 *
 * v3.7.0 introduces REGIONAL_GAME for intra-regional matchups at a neutral site.
 */
enum class GameType {
    REGULAR_SEASON,      // A standard game between a host and a visitor.
    CROSSROADS_GAME,     // A neutral-site game between two visiting teams from different regions.
    REGIONAL_GAME,       // v3.7.0: A neutral-site game between two visiting teams from the SAME region.
    APEX_RESIDENCY_GAME  // A special game type for the league's pinnacle event.
};

/**
 * @struct Game
 * @brief Represents a single scheduled baseball game.
 */
struct Game {
    Team team1;
    Team team2;
    Team designated_home_team_for_batting; // Crucial for alternating first bat rule in neutral-site games.
    Team actual_host_stadium;              // The team whose city the game is played in.
    std::string date;
    std::string time;
    GameType game_type;
};

/**
 * @struct ResidencyBlock
 * @brief Represents a period where a host team stays home to play multiple visiting teams.
 *
 * v3.7.0 logic extends these blocks to three weeks or more, featuring complex game mixes.
 */
struct ResidencyBlock {
    Team host_team;
    std::vector<Team> visiting_residents;
    std::vector<Game> games;
    std::string start_date;
    std::string end_date;
    bool is_apex_residency = false; // Flag to identify Apex Residencies.
};

} // namespace LeagueSchedulerNS

#endif // GAME_DATA_H
