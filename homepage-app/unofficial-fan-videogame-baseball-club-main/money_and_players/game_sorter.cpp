/**
 * @file game_sorter.cpp
 * @brief Implements the GameSorter class.
 * @author Eeshvar Das (Erik Douglas Ward)
 * @date 2025-Jul-26
 *
 * @warning This is a PREVIEW FEATURE and is not intended for production use
 * until v3.9.0.
 */
#include "game_sorter.h"
#include <algorithm> // For std::ranges::sort
#include <ranges>    // Required for ranges library
#include <stdexcept>

namespace LeagueSchedulerNS {

void GameSorter::sort(std::vector<Game>& games) const {
    // C++23 Feature: Use std::ranges::sort with a projection.
    // The fourth argument, &GameSorter::parseDayFromDate, is the projection.
    // It tells sort to compare games by applying this function to each one first.
    std::ranges::sort(games, {}, &GameSorter::parseDayFromDate);
}

int GameSorter::parseDayFromDate(const Game& game) {
    const std::string& date_str = game.date;
    size_t space_pos = date_str.find(' ');
    if (space_pos == std::string::npos) { return 0; }
    try {
        return std::stoi(date_str.substr(space_pos + 1));
    } catch (const std::exception& e) {
        return 0;
    }
}

} // namespace LeagueSchedulerNS
