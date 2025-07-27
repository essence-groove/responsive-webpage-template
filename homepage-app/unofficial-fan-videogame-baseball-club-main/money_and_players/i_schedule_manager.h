/**
 * @file i_schedule_manager.h
 * @brief An interface for classes that manage and operate on game schedules.
 * @author Eeshvar Das (Erik Douglas Ward)
 * @date 2025-Jul-26
 *
 * @warning This is a PREVIEW FEATURE and is not intended for production use
 * until v3.9.0. The API is subject to change.
 *
 * This abstract class allows the orchestrator to work with any scheduling
 * tool without being tied to a specific implementation.
 */
#ifndef I_SCHEDULE_MANAGER_H
#define I_SCHEDULE_MANAGER_H

#include "game_data.h" // Defines struct Game
#include <vector>

namespace LeagueSchedulerNS {

class IScheduleManager {
public:
    virtual ~IScheduleManager() = default;
    virtual void sortSchedule(std::vector<Game>& games) const = 0;
};

} // namespace LeagueSchedulerNS

#endif // I_SCHEDULE_MANAGER_H
