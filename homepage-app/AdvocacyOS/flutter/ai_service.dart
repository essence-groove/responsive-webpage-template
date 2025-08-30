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

import 'package:flutter_gemini/flutter_gemini.dart';
import './adaptive_agenda_screen.dart'; // We need the MicroTask class

class AiService {
  static Future<List<MicroTask>> getAdaptivePlan({
    required String goal,
    required double energyLevel,
    required double energyOutlook,
    required List<String> limitations,
  }) async {
    // 1. Construct the Safety-First Prompt
    final prompt = """
      Act as a supportive, risk-aware partner for a person with a physical disability who is in a high-stress emergency.
      Their goal is: "$goal"
      Their self-reported energy level is ${energyLevel.round()}/5.
      Their self-reported outlook on using energy is ${energyOutlook.round()}/5 (1 is wary, 5 is confident).
      Their self-reported limitations are: ${limitations.join(', ')}.

      Based ONLY on this information, create a simple, step-by-step action plan.

      RULES:
      1.  Your tone must be calm, grounding, and acknowledging, never demanding or presumptive.
      2.  The first one or two steps MUST be non-demanding, grounding actions (e.g., 'Sit down', 'Take a deep breath').
      3.  Prioritize low-energy, low-risk communication methods (e.g., text messages before phone calls).
      4.  Break down complex actions into small, manageable micro-tasks.
      5.  Return the plan as a numbered list with each step on a new line. Do not include any other text, titles, or summaries.
      """;

    try {
      // 2. Make the API Call
      final response = await Gemini.instance.text(prompt);
      final text = response?.content?.parts?.last.text;

      if (text == null || text.trim().isEmpty) {
        // Return a safe default if the AI gives an empty response
        return [
          MicroTask(
              description: 'There was an issue creating a plan. Please rest.')
        ];
      }

      // 3. Parse the Response
      // Splits the response by newlines and removes any empty lines.
      final steps = text
          .split('\n')
          .where((s) => s.trim().isNotEmpty)
          .map((s) => MicroTask(
              description: s.replaceAll(RegExp(r'^\d+\.\s*'), ''))) // Remove numbering
          .toList();

      return steps;
    } catch (e) {
      // Return a safe default if there is a network or API error
      print('AI Service Error: $e');
      return [
        MicroTask(description: 'Could not connect to the service. Please rest.')
      ];
    }
  }
}

