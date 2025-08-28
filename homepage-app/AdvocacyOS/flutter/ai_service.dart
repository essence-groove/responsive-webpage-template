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
  // This is a MOCK function. It simulates a call to the AI for the escalated emergency.
  static Future<List<MicroTask>> getAdaptivePlan({
    required String goal,
    required double energyLevel,
    required List<String> limitations,
  }) async {
    // Simulate a network delay
    await Future.delayed(const Duration(seconds: 2));

    // **UPDATED MOCK RESPONSE for Escalated Emergency**
    // This plan is more strategic, focusing on information gathering and
    // finding alternative support networks.
    return [
      MicroTask(description: 'Sit down. Take three slow, deep breaths.'),
      MicroTask(
          description:
              'Write down the exact support you need and the deadline.'),
      MicroTask(
          description:
              'Try to contact both family members one last time via text message.'),
      MicroTask(
          description:
              'Open your contacts. Find one other person or local service to call.'),
      MicroTask(
          description:
              'Draft a short, clear message explaining your need before you call.'),
    ];
  }
}
