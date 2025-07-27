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
#include <algorithm>
#include <ranges>
#include <stdexcept> // <-- ADD THIS LINE


namespace LeagueSchedulerNS {

// The public interface method calls the private implementation.
void GameSorter::sortSchedule(std::vector<Game>& games) const {
    sort_impl(games);
}

// The private implementation contains the C++23 ranges sort logic.
void GameSorter::sort_impl(std::vector<Game>& games) const {
    std::ranges::sort(games, {}, &GameSorter::parseDayFromDate);
}

// The static helper function for parsing remains the same.
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
