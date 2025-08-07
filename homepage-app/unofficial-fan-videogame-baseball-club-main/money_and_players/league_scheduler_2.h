/**
 * @file league_scheduler_2.h
 * @brief Header for the v3.9.1 league scheduling logic.
 * @author  Eeshvar Das (Erik Douglas Ward)
 * @date 2025-Jul-27
 *
 * @copyright Copyright (C) 2025 Eeshvar Das (Erik Douglas Ward)
 *
 * @license SPDX-License-Identifier: AGPL-3.0-or-later
 */

#ifndef LEAGUE_SCHEDULER_2_H
#define LEAGUE_SCHEDULER_2_H

#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <map>
#include "game_data.h" 
#include "team_data.h" 
#include "geography_data.h"

namespace LeagueSchedulerNS { 

class LeagueScheduler2 {
public:
    LeagueScheduler2();
    std::vector<ResidencyBlock> generateSeasonSchedule(std::vector<Team>& all_teams, int games_per_team);

private:
    struct TeamScheduleStatus {
        int available_day = 1;
        int games_scheduled = 0;
        int host_blocks_assigned = 0;
    };

    ResidencyBlock createApexResidency(std::vector<Team*>& participants, int start_day);
    std::vector<Team*> selectApexParticipants(std::vector<Team>& all_teams);
    void simulateApexEventAndAwardPoints(const ResidencyBlock& apex_block, std::vector<Team>& all_teams);
    ResidencyBlock createResidencyBlock(const Team& host, const std::vector<Team>& visitors, int start_day, int& out_duration_days);
    std::vector<Game> generateNeutralSiteSeries(const Team& visitor1, const Team& visitor2, const Team& host_stadium, int num_games, GameType game_type, int start_day, int& day_offset);
    
    // v3.9.1: New helper for creating the Apex tournament games.
    std::vector<Game> createApexTournamentGames(std::vector<Team*>& participants, const Team& host_team, int start_day, int& day_offset);

    std::mt19937 rng;
    bool apex_event_scheduled = false;
};

} // namespace LeagueSchedulerNS

#endif // LEAGUE_SCHEDULER_2_H
