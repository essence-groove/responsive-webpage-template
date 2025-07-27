/**
 * @file game_sorter.h
 * @brief A concrete implementation of IScheduleManager using C++23 ranges.
 * @author Eeshvar Das (Erik Douglas Ward)
 * @date 2025-Jul-26
 *
 * @warning This is a PREVIEW FEATURE and is not intended for production use
 * until v3.9.0. The API is subject to change.
 */
#ifndef GAME_SORTER_H
#define GAME_SORTER_H

#include "game_data.h" // Defines struct Game
#include "i_schedule_manager.h" // Include the new interface
#include <vector>
#include <string>

namespace LeagueSchedulerNS {

class GameSorter : public IScheduleManager {
public:
    // The 'override' keyword is a C++11 feature that ensures we are
    // correctly implementing a virtual function from the base class.
    void sortSchedule(std::vector<Game>& games) const override;
    /**
     * @brief Sorts a vector of Game objects in chronological order using C++23 ranges.
     * @param games The vector of games to be sorted in-place.
     */
    void sort(std::vector<Game>& games) const;

private:
    /**
     * @brief Helper function to parse a date string (e.g., "Day 12") into an integer.
     * @param game A constant reference to a Game object.
     * @return The integer day number.
     */
    static int parseDayFromDate(const Game& game);
};

} // namespace LeagueSchedulerNS

#endif // GAME_SORTER_H
