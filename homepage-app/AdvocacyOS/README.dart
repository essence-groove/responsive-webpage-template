/*
 * AdvocacyOS: A Personal Operating System for Justice
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

/// A class designed to act as a 'Table of Contents' and architectural overview
/// for the AdvocacyOS Flutter application. Each static constant provides a
/// high-level description of a key file within the project.
///
/// This structure makes the project documentation API-ready and serves as a
/// single source of truth for understanding the codebase.
class ProjectOverviewDoc {
  /// ## Project Overview
  /// This document provides a high-level overview of the key files that
  /// make up the AdvocacyOS Flutter application. It is intended to serve as a
  /// "Table of Contents" for developers and contributors, explaining the role
  /// and responsibility of each component in the system.
  static const String introduction = '''
### Project Overview
This document provides a high-level overview of the key files that make up the AdvocacyOS Flutter application. It is intended to serve as a "Table of Contents" for developers and contributors, explaining the role and responsibility of each component in the system.
''';

  /// ### 1. `pubspec.yaml`
  /// The project's configuration file. It defines the application's metadata,
  /// dependencies, and SDK constraints, ensuring a consistent development
  /// environment for all contributors.
  static const String pubspecFile = '''
### 1. `pubspec.yaml`
The project's configuration file. It defines the application's metadata, dependencies, and SDK constraints.

- **SDK Versions**: Configured for Flutter 3.35 and Dart 3.9 to leverage the latest accessibility and performance features.
- **Key Dependencies**: Manages essential packages, including `flutter_gemini` for AI model interaction.
''';

  /// ### 2. `main.dart`
  /// The entry point of the Flutter application. It handles app initialization,
  /// theme configuration, and launches the primary user-facing UI.
  static const String mainFile = '''
### 2. `main.dart`
The entry point of the Flutter application.

- **Initialization**: Responsible for initializing the AI service with the necessary API key when the app starts.
- **Theme & Accessibility**: Defines the application's high-contrast, accessible theme.
- **Core UI**: Contains the `CompassionateCheckInScreen`, which guides the user through the multi-step process of logging their energy level, outlook, limitations, and associated costs. This is the first half of the "Acknowledge, then Act" workflow.
''';

  /// ### 3. `ai_service.dart`
  /// The service layer that acts as the bridge between the application and the
  /// external AI model. It is designed with safety and resilience as its top
  /// priorities, directly implementing APM-WORLD risk management principles.
  static const String aiServiceFile = '''
### 3. `ai_service.dart`
The service layer that acts as the bridge between the application and the external AI model.

- **Prompt Engineering**: Constructs a detailed, safety-first prompt based on the user's check-in data. The prompt includes strict rules to ensure the AI's response is calm, grounding, and actionable.
- **API Call**: Makes the live call to the AI model to generate the action plan.
- **Safe Fallback Mechanism**: Contains a pre-written, safe emergency action plan that is returned to the user if the live AI call fails for any reason (e.g., no network, API error). This guarantees the app is always helpful in a crisis.
''';

  /// ### 4. `adaptive_agenda_screen.dart`
  /// The UI screen where the user's goal is combined with their check-in data to
  /// generate and display a live, actionable plan.
  static const String adaptiveAgendaFile = '''
### 4. `adaptive_agenda_screen.dart`
The UI screen where the "Act" part of the "Acknowledge, then Act" workflow takes place.

- **Goal Input**: Allows the user to input their high-level goal for the day (e.g., the emergency situation).
- **AI Service Integration**: Calls the `AiService` to get the adaptive action plan.
- **Dynamic Display**: Displays the returned list of micro-tasks in an interactive, checkable list, complete with timers and a mechanism for the user to re-evaluate their energy.
- **Entry Point to Ledger**: Provides the navigation button to access the "Holistic Energy Ledger."
''';

  /// ### 5. `energy_ledger_screen.dart`
  /// The UI screen for the "Holistic Energy Ledger." This feature allows users to
  /// track their "Energy Economy" by logging wellness and financial entries.
  static const String energyLedgerFile = '''
### 5. `energy_ledger_screen.dart`
The UI screen for the Phase 2 feature, "The Holistic Energy Ledger."

- **Energy Balance Visualization**: Displays the qualitative "Depleted" to "Replenished" bar at the top for at-a-glance feedback.
- **One-Tap Logging**: Features a grid of tappable tags for logging "Energy Credits" (e.g., "Nutritious Meal") and "Energy Debits" (e.g., "Stressful Event").
- **Frictionless Design**: Implements the core UI/UX principles of non-judgmental framing and gentle reinforcement.
''';
}
