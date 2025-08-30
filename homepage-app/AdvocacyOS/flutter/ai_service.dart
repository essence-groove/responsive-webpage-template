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
    // This is the safe, pre-written plan that will be used if the AI call fails.
    final fallbackPlan = [
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
        // If the AI gives an empty response, use the safe fallback.
        return fallbackPlan;
      }

      // 3. Parse the Response
      final steps = text
          .split('\n')
          .where((s) => s.trim().isNotEmpty)
          .map((s) => MicroTask(
              description: s.replaceAll(RegExp(r'^\d+\.\s*'), '')))
          .toList();

      return steps.isNotEmpty ? steps : fallbackPlan;
    } catch (e) {
      // If there is a network or API error, use the safe fallback.
      print('AI Service Error: $e');
      return fallbackPlan;
    }
  }
}

