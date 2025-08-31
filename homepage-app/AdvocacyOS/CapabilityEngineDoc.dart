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
/// of "The Capability Engine" module. Each static constant holds a piece of the
/// conceptual documentation, allowing for programmatic access and display.
///
/// This structure makes the documentation API-ready and easy to integrate
/// into other parts of the application or external systems.
class CapabilityEngineDoc {
  /// The main title and high-level introduction to The Capability Engine.
  static const String header = '''
# The Capability Engine: Acknowledge and Act

The Capability Engine represents the next evolution of AdvocacyOS, shifting its focus from external advocacy to internal empowerment. This proposed new module is specifically designed to help individuals with physical disabilities build physical capability and reclaim agency over their daily lives, transforming AdvocacyOS from a defensive tool into a proactive one for personal growth.
''';

  /// The core guiding principle of the module's two-step workflow.
  static const String corePrinciple = '''
The core principle guiding this module is a two-step process: **Acknowledge, then Act**.
''';

  /// The header and introduction for the first step of the workflow.
  static const String step1_Header = '''
## Step 1: The Compassionate Check-In (Acknowledge Your State)

Before a user can effectively plan their day, they must first achieve a clear and compassionate understanding of their current capabilities. This feature provides a private, judgment-free space to do just that.
''';

  /// A detailed breakdown of the features within the "Compassionate Check-In".
  static const String step1_Features = '''
* **Guided Journaling Interface:** Instead of a sterile form, users interact with a gentle, conversational user interface (UI). It prompts them with questions designed to gauge their current state, such as:
    * "Good morning. Let's check in. How is your energy level right now, from 1 (very low) to 5 (very high)?"
    * "Are you noticing any specific physical limitations or pain today?"
    * "What does your body feel like it needs at this moment?"
* **Limitation & Energy Tracking:** Users can log their current physical and energy state, tagging entries with recurring themes like fatigue, joint-pain, or brain-fog. Over time, this process creates a private, personal dataset that helps the user understand their own patterns without any external pressure.
* **Strictly for You:** This check-in is designed as a personal conversation with oneself. All data collected through this process is encrypted and intended solely for the user's eyes, reinforcing the "personal fortress" principle that underpins AdvocacyOS. The goal is to build self-awareness, not to track performance for others.
''';

  /// The header and introduction for the second step of the workflow.
  static const String step2_Header = '''
## Step 2: The Adaptive "Now" Agenda (Act with Intention)

Immediately following the compassionate check-in, the app transitions from reflection to action. The primary objective is to help the user build a realistic, empowering, and **live** agenda for their immediate future—specifically for the current day.
''';

  /// A detailed breakdown of the features within the "Adaptive 'Now' Agenda".
  static const String step2_Features = '''
* **From Check-In to Plan:** The system intelligently utilizes the information gathered during the check-in to assist in creating the day's schedule. For example, if a user reports low energy and knee pain, the system might respond with:
    * *"Thank you for sharing. I hear that your energy is at a 2 and your knee is bothering you. Let's build a day that respects that. What is one small thing you'd like to accomplish today?"*
* **AI-Assisted Task Management:** When a user sets a goal, such as "Tidy up the living room," the integrated AI helps break down this larger task into manageable micro-tasks, taking into account the user's stated limitations.
    * **User:** "I need to tidy the living room."
    * **AI:** *"Okay. Let's start with something that doesn't require bending. How about we spend 10 minutes clearing the coffee table first? We can take a break right after."*
* **A Live, Dynamic Schedule:** This module provides more than just a static to-do list; it offers an active and dynamic agenda. Users can start a timer for a task, check it off upon completion, and receive gentle encouragement or reminders to take rests. Crucially, if a user reports a dip in energy mid-task, the agenda can adapt on the fly, suggesting a shorter task or an immediate break. The continuous focus remains on what is truly possible **right now** for the user.
''';

  /// The concluding summary of the "Acknowledge, then Act" workflow.
  static const String conclusion = '''
This "Acknowledge, then Act" workflow extends the core mission of AdvocacyOS by applying the principle of **strategic energy management** not only to the fight against discrimination but also to the personal and vital work of living a capable and fulfilling life.
''';
}
