// FILE: main.dart
// This file remains the same as the previous version. It handles app startup
// and the initial check-in screen.

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
import './adaptive_agenda_screen.dart'; // Import the agenda screen

// Main function to run the app
void main() {
  // No API key initialization is needed for the mock service.
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
      home: const CompassionateCheckInScreen(),
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
  CheckInStep _currentStep = CheckInStep.energyLevel;
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

  void _nextStep() {
    setState(() {
      if (_currentStep == CheckInStep.energyLevel) {
        _currentStep = CheckInStep.limitations;
      } else if (_currentStep == CheckInStep.limitations) {
        _currentStep = CheckInStep.needs;
      }
    });
  }

  void _finishCheckIn() {
    Navigator.of(context).push(
      MaterialPageRoute(
        builder: (context) => AdaptiveAgendaScreen(
          energyLevel: _energyLevel,
          limitations: _selectedLimitations,
        ),
      ),
    );
  }

  void _showAddCustomLimitationDialog() {
    showDialog(
      context: context,
      builder: (context) {
        return AlertDialog(
          title: const Text('Add a Custom Limitation'),
          content: TextField(
            controller: _customLimitationController,
            autofocus: true,
            decoration: const InputDecoration(hintText: "e.g., 'Anxiety'"),
          ),
          actions: [
            TextButton(
              onPressed: () => Navigator.of(context).pop(),
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

  Widget _buildLimitationsStep() {
    return Column(
      key: const ValueKey('limitationsStep'),
      crossAxisAlignment: CrossAxisAlignment.start,
      children: [
        Text('Got it.', style: Theme.of(context).textTheme.bodyLarge),
        const SizedBox(height: 8),
        Text('Are you noticing any other limitations or feelings right now?',
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
            hintText: 'e.g., "A moment of quiet," "Some gentle stretching and breathing"...',
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

enum CheckInStep {
  energyLevel,
  limitations,
  needs,
}


// ==================================================================
// FILE: ai_service.dart
// This file now contains a mock response for the emergency scenario.
// ==================================================================

/*
 * AdvocacyOS: The Capability Engine
 * ... (rest of license header) ...
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


// ==================================================================
// FILE: adaptive_agenda_screen.dart
// This file is updated to reflect the emergency scenario in the UI.
// ==================================================================

/*
 * AdvocacyOS: The Capability Engine
 * ... (rest of license header) ...
 */

import 'package:flutter/material.dart';
import './ai_service.dart'; // Import the MOCK AI service

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
  bool _isLoading = false;

  List<MicroTask> _tasks = [];

  Future<void> _createPlan() async {
    if (_goalController.text.isNotEmpty) {
      setState(() {
        _isLoading = true;
        _mainGoal = _goalController.text;
      });

      final generatedTasks = await AiService.getAdaptivePlan(
        goal: _mainGoal,
        energyLevel: widget.energyLevel,
        limitations: widget.limitations,
      );

      setState(() {
        _tasks = generatedTasks;
        _planCreated = true;
        _isLoading = false;
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
        child: _isLoading
            ? const Center(child: CircularProgressIndicator())
            : (_planCreated ? _buildLiveAgendaView() : _buildGoalInputView()),
      ),
    );
  }

  // **UPDATED UI**
  Widget _buildGoalInputView() {
    String limitationsText = widget.limitations.join(' and ');
    if (limitationsText.isEmpty) {
      limitationsText = 'no specific limitations';
    }

    return Column(
      crossAxisAlignment: CrossAxisAlignment.start,
      children: [
        Text(
          "I hear that your energy is at a ${widget.energyLevel.round()} and you're dealing with $limitationsText. Let's create a clear path forward.",
          style: Theme.of(context).textTheme.bodyLarge,
        ),
        const SizedBox(height: 24),
        Text(
          'What is the most urgent situation you are facing right now?',
          style: Theme.of(context).textTheme.headlineSmall,
        ),
        const SizedBox(height: 16),
        TextField(
          controller: _goalController,
          decoration: InputDecoration(
            // **UPDATED HINT TEXT**
            hintText: 'e.g., "My support person is missing"',
            border: OutlineInputBorder(
              borderRadius: BorderRadius.circular(12),
            ),
          ),
        ),
        const Spacer(),
        Center(
          child: ElevatedButton(
            onPressed: _createPlan,
            child: const Text('Create Action Plan'),
          ),
        ),
      ],
    );
  }

  Widget _buildLiveAgendaView() {
    if (_tasks.isEmpty) {
      return const Center(child: Text("No tasks were generated. Please try again."));
    }

    final String aiSuggestion = "Let's start with one small, grounding step.";
    final MicroTask currentTask =
        _tasks.firstWhere((task) => !task.isCompleted, orElse: () => _tasks.first);

    return Column(
      crossAxisAlignment: CrossAxisAlignment.start,
      children: [
        Text(
          "Emergency Action Plan",
          style: Theme.of(context).textTheme.bodyLarge,
        ),
        Text(
          _mainGoal,
          style: Theme.of(context).textTheme.headlineSmall,
        ),
        const SizedBox(height: 24),
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
                    onPressed: () {},
                    child: const Text('Mark as Complete'),
                  ),
                ),
              ],
            ),
          ),
        ),
        const SizedBox(height: 24),
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
            onPressed: () {},
          ),
        )
      ],
    );
  }
}
