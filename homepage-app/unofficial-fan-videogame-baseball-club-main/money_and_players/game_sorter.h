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

#include "i_schedule_manager.h"
#include "game_data.h"

namespace LeagueSchedulerNS {

class GameSorter : public IScheduleManager {
public:
    // This public method fulfills the interface contract.
    void sortSchedule(std::vector<Game>& games) const override;

private:
    // This private method contains the actual sorting logic.
    void sort_impl(std::vector<Game>& games) const;

    static int parseDayFromDate(const Game& game);
};

} // namespace LeagueSchedulerNS

#endif // GAME_SORTER_H
