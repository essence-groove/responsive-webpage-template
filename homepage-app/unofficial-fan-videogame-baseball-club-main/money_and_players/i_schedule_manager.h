#ifndef I_SCHEDULE_MANAGER_H
#define I_SCHEDULE_MANAGER_H

#include "game_data.h" // Defines struct Game
#include <vector>

namespace LeagueSchedulerNS {

/**
 * @brief An interface for classes that manage and operate on game schedules.
 *
 * This abstract class allows the orchestrator to work with any scheduling
 * tool without being tied to a specific implementation.
 */
class IScheduleManager {
public:
    // A virtual destructor is essential for any base class with virtual functions.
    virtual ~IScheduleManager() = default;

    /**
     * @brief Sorts a schedule of games in place.
     * @param games The vector of games to be sorted.
     */
    virtual void sortSchedule(std::vector<Game>& games) const = 0; // Pure virtual function
};

} // namespace LeagueSchedulerNS

#endif // I_SCHEDULE_MANAGER_H
