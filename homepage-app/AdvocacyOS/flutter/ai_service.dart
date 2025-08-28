/*
 * AdvocacyOS: The Capability Engine
 * A Flutter module for self-empowerment and building physical capability.
 * Copyright (C) 2025 Eeshvar Das (Erik Douglas Ward)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

import './adaptive_agenda_screen.dart'; // We need the MicroTask class

class AiService {
  // This is a MOCK function. It simulates a call to the AI for the emergency scenario.
  static Future<List<MicroTask>> getAdaptivePlan({
    required String goal,
    required double energyLevel,
    required List<String> limitations,
  }) async {
    // Simulate a network delay
    await Future.delayed(const Duration(seconds: 2));

    // **UPDATED MOCK RESPONSE**
    // This is a pre-written, sample plan for the emergency scenario.
    // It focuses on calm, grounding, and actionable first steps.
    return [
      MicroTask(description: 'Take one deep breath in and out.'),
      MicroTask(description: 'Confirm their phone is still unresponsive.'),
      MicroTask(description: 'Write down the name of one person to call for help.'),
      MicroTask(description: 'Sit down with a glass of water before calling.'),
    ];
  }
}
