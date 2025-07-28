/**
 * @file report_logic.h
 * @brief Defines the ReportGenerator class for creating the schedule report (v3.9.2).
 * @author  Eeshvar Das (Erik Douglas Ward)
 * @date 2025-Jul-27
 *
 * @copyright Copyright (C) 2025 Eeshvar Das (Erik Douglas Ward)
 *
 * @license SPDX-License-Identifier: AGPL-3.0-or-later
 */

#ifndef REPORT_LOGIC_H
#define REPORT_LOGIC_H

#include <vector>
#include <string>
#include "game_data.h"

namespace LeagueSchedulerNS {

/**
 * @class ReportGenerator
 * @brief Encapsulates the logic for generating the season schedule report.
 */
class ReportGenerator {
public:
    /**
     * @brief Generates a markdown report from a season schedule.
     * @param schedule The vector of ResidencyBlock objects.
     * @param filename The name of the output file.
     */
    void generate(const std::vector<ResidencyBlock>& schedule, const std::string& filename);

private:
    /**
     * @brief Helper to convert a GameType enum to its string representation.
     */
    std::string getGameTypeString(GameType type);
};

} // namespace LeagueSchedulerNS

#endif // REPORT_LOGIC_H
