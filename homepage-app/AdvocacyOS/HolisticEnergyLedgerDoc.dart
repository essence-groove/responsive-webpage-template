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
/// of "The Holistic Energy Ledger" UI wireframe. Each static constant holds a
/// piece of the design documentation, allowing for programmatic access.
///
/// This structure makes the design principles API-ready and easy to reference
/// during development and for future system integration.
class HolisticEnergyLedgerDoc {
  /// The main title and high-level introduction to the wireframe.
  static const String header = '''
# UI Wireframe: The Holistic Energy Ledger

This document outlines the visual layout and user flow for the main screen of the Energy Ledger. It is designed to be simple, scannable, and non-judgmental, adhering to our core UI/UX principles.
''';

  /// The header for the main screen layout section.
  static const String screenLayoutHeader = '''
## Screen Layout: Main Ledger View
''';

  /// The primary goal of the main ledger view.
  static const String goal = '''
**Goal:** Provide an at-a-glance view of the user's energy balance and allow for one-tap logging of both "Credits" and "Debits."
''';

  /// The header for the energy balance visualization component.
  static const String visualizationHeader = '''
### 1. Energy Balance Visualization (Top of Screen)
''';

  /// A detailed breakdown of the visualization component's design.
  static const String visualizationDetails = '''
* **Component:** A simple, horizontal bar graph.
* **Labels:** The bar is labeled "Depleted" on the left and "Replenished" on the right.
* **Visuals:** The bar fills from left to right with a soft, neutral color (e.g., a calm blue or teal). It is explicitly not a percentage or a hard number, but a qualitative indicator that shifts gently based on the last few days of logged entries.
* **Placement:** Positioned prominently at the top of the screen for instant, at-a-glance feedback.
''';

  /// The header for the main content area where users log entries.
  static const String loggingSectionsHeader = '''
### 2. Logging Sections (Main Content Area)
''';

  /// The introductory text for the logging sections.
  static const String loggingSectionsIntro = '''
The screen is divided into two clear, distinct sections, each with a grid of selectable tags.
''';

  /// The header for the "Energy Credit" logging section.
  static const String sectionA_Header = '''
#### Section A: "Log an Energy Credit"
''';

  /// A detailed breakdown of the "Energy Credit" section, including example tags.
  static const String sectionA_Details = '''
* **Header Color:** A calming green.
* **Layout:** A grid of tappable cards. Each card contains a simple icon and a short text label.
* **Example Tags (with conceptual icons):**
    * [Icon: Water Drop] Hydrated Well
    * [Icon: Apple] Nutritious Meal
    * [Icon: Moon] Quality Sleep
    * [Icon: Stretching Figure] Gentle Movement
    * [Icon: Sun] Time Outside
    * [Icon: Heart] Positive Connection
''';

  /// The header for the "Energy Debit" logging section.
  static const String sectionB_Header = '''
#### Section B: "Log an Energy Debit"
''';

  /// A detailed breakdown of the "Energy Debit" section, including example tags.
  static const String sectionB_Details = '''
* **Header Color:** A neutral grey.
* **Layout:** A similar grid of tappable cards.
* **Example Tags (with conceptual icons):**
    * [Icon: Fast Food] Processed Food
    * [Icon: Skipped Plate] Skipped Meal
    * [Icon: Weight] Overexertion
    * [Icon: Clock] Skipped Rest
    * [Icon: Storm Cloud] Stressful Event
    * [Icon: Broken Z's] Poor Sleep
''';

  /// The header for the user interaction flow section.
  static const String interactionFlowHeader = '''
## User Interaction Flow
''';

  /// A step-by-step description of the user's interaction with the ledger.
  static const String interactionFlowSteps = '''
1.  User opens the Energy Ledger screen. They immediately see their current "Energy Balance".
2.  User taps a tag. For example, they tap the "[Icon: Apple] Nutritious Meal" card.
3.  A gentle, non-blocking confirmation appears. A small banner or "toast" message shows at the bottom of the screen for a few seconds with the text: "Noted. Thank you for taking that time for yourself."
4.  The "Energy Balance" bar subtly adjusts. The bar animates smoothly to reflect the new positive entry.
5.  The user can immediately tap another tag or navigate away. The process is complete.
''';

  /// The concluding summary of the wireframe's design principles.
  static const String conclusion = '''
This design directly implements our principles: it's frictionless (one tap to log), visual, and uses non-judgmental framing with gentle reinforcement, creating a safe and supportive tool for building self-awareness.
''';
}
