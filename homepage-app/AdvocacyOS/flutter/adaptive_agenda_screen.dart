// FILE: adaptive_agenda_screen.dart
// This is a new file you should create in your project.

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

import 'package:flutter/material.dart';

// Represents a single micro-task in the agenda
class MicroTask {
  final String description;
  bool isCompleted;

  MicroTask({required this.description, this.isCompleted = false});
}

// The "Adaptive Now Agenda" screen
class AdaptiveAgendaScreen extends StatefulWidget {
  final double energyLevel;
  final List<String> limitations;

  const AdaptiveAgendaScreen({
    super.key,
    required this.energyLevel,
    required this.limitations,
  });

  @override
  State<AdaptiveAgendaScreen> createState() => _AdaptiveAgendaScreenState();
}

class _AdaptiveAgendaScreenState extends State<AdaptiveAgendaScreen> {
  final TextEditingController _goalController = TextEditingController();
  String _mainGoal = '';
  bool _planCreated = false;

  // Mock data for the task list. This will be replaced by the Gemini AI response.
  final List<MicroTask> _tasks = [
    MicroTask(description: 'Clear the coffee table (10 mins)'),
    MicroTask(description: 'Rest for 5 minutes'),
    MicroTask(description: 'Fold the blanket on the chair'),
  ];

  void _createPlan() {
    if (_goalController.text.isNotEmpty) {
      setState(() {
        _mainGoal = _goalController.text;
        _planCreated = true;
        // In the next step, we will call the Gemini AI here to populate the _tasks list
        // based on the _mainGoal and the user's energy/limitations.
      });
    }
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Your Adaptive Agenda'),
        backgroundColor: Colors.transparent,
        elevation: 0,
        foregroundColor: Colors.black,
      ),
      body: Padding(
        padding: const EdgeInsets.all(24.0),
        child: _planCreated ? _buildLiveAgendaView() : _buildGoalInputView(),
      ),
    );
  }

  // The initial view where the user inputs their goal for the day
  Widget _buildGoalInputView() {
    // Joining the limitations for a more natural sentence.
    String limitationsText = widget.limitations.join(' and ');
    if (limitationsText.isEmpty) {
      limitationsText = 'no specific limitations';
    }

    return Column(
      crossAxisAlignment: CrossAxisAlignment.start,
      children: [
        Text(
          "I hear that your energy is at a ${widget.energyLevel.round()} and you're feeling some $limitationsText. Let's build a day that respects that.",
          style: Theme.of(context).textTheme.bodyLarge,
        ),
        const SizedBox(height: 24),
        Text(
          'What is one thing you\'d like to accomplish today?',
          style: Theme.of(context).textTheme.headlineSmall,
        ),
        const SizedBox(height: 16),
        TextField(
          controller: _goalController,
          decoration: InputDecoration(
            hintText: 'e.g., "Tidy up the living room"',
            border: OutlineInputBorder(
              borderRadius: BorderRadius.circular(12),
            ),
          ),
        ),
        const Spacer(),
        Center(
          child: ElevatedButton(
            onPressed: _createPlan,
            child: const Text('Create Plan'),
          ),
        ),
      ],
    );
  }

  // The view that shows the live, actionable agenda
  Widget _buildLiveAgendaView() {
    // This is a placeholder for the AI's suggestion.
    final String aiSuggestion =
        "Let's start with something that doesn't require bending.";
    final MicroTask currentTask =
        _tasks.firstWhere((task) => !task.isCompleted, orElse: () => _tasks.first);

    return Column(
      crossAxisAlignment: CrossAxisAlignment.start,
      children: [
        Text(
          "Today's Plan",
          style: Theme.of(context).textTheme.bodyLarge,
        ),
        Text(
          _mainGoal,
          style: Theme.of(context).textTheme.headlineSmall,
        ),
        const SizedBox(height: 24),
        // AI Suggestion Card
        Card(
          elevation: 2,
          shape:
              RoundedRectangleBorder(borderRadius: BorderRadius.circular(12)),
          child: Padding(
            padding: const EdgeInsets.all(16.0),
            child: Column(
              crossAxisAlignment: CrossAxisAlignment.start,
              children: [
                Text(
                  aiSuggestion,
                  style: const TextStyle(
                      fontStyle: FontStyle.italic, color: Colors.black54),
                ),
                const SizedBox(height: 16),
                Text(
                  'Current Task: ${currentTask.description}',
                  style: const TextStyle(
                      fontSize: 18, fontWeight: FontWeight.bold),
                ),
                const SizedBox(height: 16),
                Center(
                  child: ElevatedButton(
                    onPressed: () {
                      // Logic for the timer would go here
                    },
                    child: const Text('Start Timer'),
                  ),
                ),
              ],
            ),
          ),
        ),
        const SizedBox(height: 24),
        // Task List
        Expanded(
          child: ListView.builder(
            itemCount: _tasks.length,
            itemBuilder: (context, index) {
              final task = _tasks[index];
              return CheckboxListTile(
                title: Text(
                  task.description,
                  style: TextStyle(
                    decoration: task.isCompleted
                        ? TextDecoration.lineThrough
                        : TextDecoration.none,
                  ),
                ),
                value: task.isCompleted,
                onChanged: (bool? value) {
                  setState(() {
                    task.isCompleted = value ?? false;
                  });
                },
              );
            },
          ),
        ),
        Center(
          child: TextButton.icon(
            icon: const Icon(Icons.sentiment_satisfied_alt),
            label: const Text('How are you feeling now?'),
            onPressed: () {
              // This would trigger a re-evaluation and adapt the plan
            },
          ),
        )
      ],
    );
  }
}

// ==================================================================
// FILE: main.dart
// This is the updated version of your existing main.dart file.
// ==================================================================

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

import 'package:flutter/material.dart';
import './adaptive_agenda_screen.dart'; // Import the new screen

// Main function to run the app
void main() {
  runApp(const AdvocacyOSApp());
}

// Root widget of the application
class AdvocacyOSApp extends StatelessWidget {
  const AdvocacyOSApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Capability Engine',
      theme: ThemeData(
        primarySwatch: Colors.indigo,
        fontFamily: 'Inter',
        // A gentle, supportive theme
        scaffoldBackgroundColor: const Color(0xFFF5F5F7),
        textTheme: const TextTheme(
          headlineSmall: TextStyle(
              fontSize: 28.0,
              fontWeight: FontWeight.bold,
              color: Color(0xFF1D1D1F)),
          bodyLarge: TextStyle(
              fontSize: 18.0, color: Color(0xFF4A4A4A), height: 1.5),
        ),
        elevatedButtonTheme: ElevatedButtonThemeData(
          style: ElevatedButton.styleFrom(
            backgroundColor: Colors.indigo,
            foregroundColor: Colors.white,
            padding: const EdgeInsets.symmetric(horizontal: 30, vertical: 15),
            textStyle:
                const TextStyle(fontSize: 16, fontWeight: FontWeight.bold),
            shape: RoundedRectangleBorder(
              borderRadius: BorderRadius.circular(12),
            ),
          ),
        ),
      ),
      // Set the initial route and define all possible routes
      initialRoute: '/',
      routes: {
        '/': (context) => const CompassionateCheckInScreen(),
        // We will define the '/agenda' route later, but it's good practice
        // to have a placeholder. The actual navigation will pass arguments.
      },
    );
  }
}

// The main screen for the "Compassionate Check-In" flow
class CompassionateCheckInScreen extends StatefulWidget {
  const CompassionateCheckInScreen({super.key});

  @override
  State<CompassionateCheckInScreen> createState() =>
      _CompassionateCheckInScreenState();
}

class _CompassionateCheckInScreenState
    extends State<CompassionateCheckInScreen> {
  // Using an enum to manage the flow of the check-in process
  CheckInStep _currentStep = CheckInStep.energyLevel;

  // State variables to hold the user's selections
  double _energyLevel = 3.0;
  final List<String> _selectedLimitations = [];
  final List<String> _predefinedLimitations = [
    'Fatigue',
    'Joint Pain',
    'Brain Fog',
    'Stiffness'
  ];
  final TextEditingController _notesController = TextEditingController();
  final TextEditingController _customLimitationController =
      TextEditingController();

  // Function to move to the next step in the check-in flow
  void _nextStep() {
    setState(() {
      if (_currentStep == CheckInStep.energyLevel) {
        _currentStep = CheckInStep.limitations;
      } else if (_currentStep == CheckInStep.limitations) {
        _currentStep = CheckInStep.needs;
      }
    });
  }

  // **UPDATED FUNCTION**
  // Function to handle the final submission and navigate to the new screen
  void _finishCheckIn() {
    // This now navigates to the AdaptiveAgendaScreen and passes the data.
    Navigator.of(context).push(
      MaterialPageRoute(
        builder: (context) => AdaptiveAgendaScreen(
          energyLevel: _energyLevel,
          limitations: _selectedLimitations,
        ),
      ),
    );
  }

  // Function to show a dialog for adding a custom limitation
  void _showAddCustomLimitationDialog() {
    showDialog(
      context: context,
      builder: (context) {
        return AlertDialog(
          title: const Text('Add a Custom Limitation'),
          content: TextField(
            controller: _customLimitationController,
            autofocus: true,
            decoration: const InputDecoration(hintText: "e.g., 'Headache'"),
          ),
          actions: [
            TextButton(
              onPressed: () {
                Navigator.of(context).pop();
              },
              child: const Text('Cancel'),
            ),
            ElevatedButton(
              onPressed: () {
                if (_customLimitationController.text.isNotEmpty) {
                  setState(() {
                    _selectedLimitations.add(_customLimitationController.text);
                  });
                  _customLimitationController.clear();
                }
                Navigator.of(context).pop();
              },
              child: const Text('Add'),
            ),
          ],
        );
      },
    );
  }

  // Build the UI for the current step
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: SafeArea(
        child: Padding(
          padding: const EdgeInsets.all(24.0),
          child: AnimatedSwitcher(
            duration: const Duration(milliseconds: 300),
            child: _buildStepWidget(),
          ),
        ),
      ),
    );
  }

  // Helper function to return the widget for the current step
  Widget _buildStepWidget() {
    switch (_currentStep) {
      case CheckInStep.energyLevel:
        return _buildEnergyLevelStep();
      case CheckInStep.limitations:
        return _buildLimitationsStep();
      case CheckInStep.needs:
        return _buildNeedsStep();
    }
  }

  // Widget for the Energy Level selection step
  Widget _buildEnergyLevelStep() {
    return Column(
      key: const ValueKey('energyStep'),
      crossAxisAlignment: CrossAxisAlignment.start,
      children: [
        const Text('Good morning.', style: TextStyle(fontSize: 20)),
        const SizedBox(height: 8),
        Text('Let\'s check in. How is your energy level right now?',
            style: Theme.of(context).textTheme.headlineSmall),
        const Spacer(),
        Center(
          child: Text(
            _energyLevel.round().toString(),
            style: const TextStyle(fontSize: 80, fontWeight: FontWeight.bold),
          ),
        ),
        Slider(
          value: _energyLevel,
          min: 1,
          max: 5,
          divisions: 4,
          label: _energyLevel.round().toString(),
          onChanged: (double value) {
            setState(() {
              _energyLevel = value;
            });
          },
        ),
        const Row(
          mainAxisAlignment: MainAxisAlignment.spaceBetween,
          children: [Text('Very Low'), Text('Very High')],
        ),
        const Spacer(),
        Center(
          child: ElevatedButton(
            onPressed: _nextStep,
            child: const Text('Next'),
          ),
        ),
      ],
    );
  }

  // Widget for the Limitations selection step
  Widget _buildLimitationsStep() {
    return Column(
      key: const ValueKey('limitationsStep'),
      crossAxisAlignment: CrossAxisAlignment.start,
      children: [
        Text('Got it.', style: Theme.of(context).textTheme.bodyLarge),
        const SizedBox(height: 8),
        Text('Are you noticing any specific physical limitations or pain today?',
            style: Theme.of(context).textTheme.headlineSmall),
        const SizedBox(height: 8),
        const Text('(Select any that apply)'),
        const SizedBox(height: 24),
        Wrap(
          spacing: 12.0,
          runSpacing: 12.0,
          children: [
            ..._predefinedLimitations.map((limitation) {
              final isSelected = _selectedLimitations.contains(limitation);
              return ChoiceChip(
                label: Text(limitation),
                selected: isSelected,
                onSelected: (bool selected) {
                  setState(() {
                    if (selected) {
                      _selectedLimitations.add(limitation);
                    } else {
                      _selectedLimitations.remove(limitation);
                    }
                  });
                },
                selectedColor: Colors.indigo[100],
                labelStyle: TextStyle(
                    color: isSelected ? Colors.indigo[900] : Colors.black),
              );
            }).toList(),
            ActionChip(
              avatar: const Icon(Icons.add),
              label: const Text('Add Custom'),
              onPressed: _showAddCustomLimitationDialog,
            ),
          ],
        ),
        const Spacer(),
        Center(
          child: ElevatedButton(
            onPressed: _nextStep,
            child: const Text('Next'),
          ),
        ),
      ],
    );
  }

  // Widget for the final "Needs" step
  Widget _buildNeedsStep() {
    return Column(
      key: const ValueKey('needsStep'),
      crossAxisAlignment: CrossAxisAlignment.start,
      children: [
        Text('Thank you for sharing.',
            style: Theme.of(context).textTheme.bodyLarge),
        const SizedBox(height: 8),
        Text('What does your body feel like it needs at this moment?',
            style: Theme.of(context).textTheme.headlineSmall),
        const SizedBox(height: 8),
        const Text('(Optional)'),
        const SizedBox(height: 24),
        TextField(
          controller: _notesController,
          maxLines: 5,
          decoration: InputDecoration(
            hintText: 'e.g., "A quiet space," "Some gentle stretching"...',
            border: OutlineInputBorder(
              borderRadius: BorderRadius.circular(12),
            ),
          ),
        ),
        const Spacer(),
        Center(
          child: ElevatedButton(
            onPressed: _finishCheckIn,
            child: const Text('Finish Check-In'),
          ),
        ),
      ],
    );
  }
}

// Enum to represent the different steps in the check-in process
enum CheckInStep {
  energyLevel,
  limitations,
  needs,
}
