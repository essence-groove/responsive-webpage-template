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

/// A class designed to act as a 'Table of Contents' for the documentation
/// of "The Capability Engine" UI wireframe. Each static constant holds a
/// piece of the design documentation, allowing for programmatic access.
///
/// This structure makes the design principles API-ready and easy to reference
/// during development and for future system integration.
class CapabilityEngineWireframeDoc {
  /// The main header and introduction for the Capability Engine wireframe.
  static const String header = '''
#### UI/UX Wireframes: The Capability Engine
This document outlines the basic user flow and screen layouts for the module. The design prioritizes a gentle, supportive, and non-overwhelming user experience.
''';

  /// The header and goal for the first screen of the user flow.
  static const String screen1_Header = '''
##### **Screen 1: The Compassionate Check-In**
**Goal:** Guide the user through a simple, one-question-at-a-time check-in to assess their current state without pressure.
''';

  /// The detailed interaction flow for the "Compassionate Check-In" screen.
  static const String screen1_Flow = '''
**Flow:**
1.  **Initial Screen:**
    * Good morning.
    * Let's check in. How is your energy level right now?
        * [Slider or 5 selectable buttons: 1 (Very Low) to 5 (Very High)]
        * [Next Button]
2.  **Second Screen (after energy is selected):**
    * Got it. Are you noticing any specific physical limitations or pain today?
    * (Select any that apply)
        * [Tag Button: Fatigue] [Tag Button: Joint Pain]
        * [Tag Button: Brain Fog] [Tag Button: Stiffness]
        * [ + Add Custom Limitation ]
        * [Next Button]
3.  **Final Screen:**
    * Thank you for sharing. What does your body feel like it needs at this moment?
    * (Optional)
        * [Text Input Field for optional notes]
        * [Finish Check-In Button]
''';

  /// The header and goal for the second screen of the user flow.
  static const String screen2_Header = '''
##### **Screen 2: The Adaptive "Now" Agenda**
**Goal:** Transition seamlessly from the check-in to a live, actionable agenda that respects the user's current state.
''';

  /// The detailed interaction flow for the "Adaptive 'Now' Agenda" screen.
  static const String screen2_Flow = '''
**Flow:**
1.  **Transition & Suggestion:**
    * I hear that your energy is at a **2** and you're feeling some **joint pain**. Let's build a day that respects that.
    * What is one thing you'd like to accomplish today?
        * [Text Input Field: e.g., "Tidy up the living room"]
        * [Create Plan Button]
2.  **Live Agenda View (after plan is created):**
    * **Today's Plan: Tidy Up The Living Room**
    * **[AI Suggestion Card]**
        * Let's start with something that doesn't require bending.
    * **Current Task:** Clear the coffee table.
    * [Start 10-Min Timer Button]
    * **[Task List]**
        * [✅] Clear the coffee table
        * [ ] Rest for 5 minutes
        * [ ] Fold the blanket on the chair
        * ...
    * [Button: How are you feeling now?] *(Allows user to re-evaluate energy and adapt the plan)*
''';
}
