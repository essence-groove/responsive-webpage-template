/**
 * @file money_and_players.cpp
 * @brief Source file for the money_and_players library.
 * @author  Eeshvar Das (Erik Douglas Ward)
 * @date 2025-Jul-25
 *
 * @copyright Copyright (C) 2025 Eeshvar Das (Erik Douglas Ward)
 *
 * @license SPDX-License-Identifier: AGPL-3.0-or-later
 *
 * This file is part of the v3.8.0 refactoring. Its existence allows the
 * 'money_and_players' module to be compiled as a standard library,
 * simplifying the dependency chain for its child modules.
 */

#include <string>

// v3.8.0: Add a simple function to give this compilation unit substance.
// This ensures the library is non-empty and correctly linked by the build system.
namespace LeagueSchedulerNS {
    /**
     * @brief Get the version of the money_and_players data module.
     * @return A string literal representing the current version.
     */
    const char* getMoneyAndPlayersVersion() {
        return "3.8.0";
    }
}
