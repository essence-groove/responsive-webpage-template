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
import './adaptive_agenda_screen.dart';

void main() {
  runApp(const AdvocacyOSApp());
}

class AdvocacyOSApp extends StatelessWidget {
  const AdvocacyOSApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Capability Engine',
      theme: ThemeData(
        // Theme choices are intentionally high-contrast for accessibility.
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

class CompassionateCheckInScreen extends StatefulWidget {
  const CompassionateCheckInScreen({super.key});

  @override
  State<CompassionateCheckInScreen> createState() =>
      _CompassionateCheckInScreenState();
}

class _CompassionateCheckInScreenState
    extends State<CompassionateCheckInScreen> {
  CheckInStep _currentStep = CheckInStep.energyLevel;
  
  // State for the two sliders
  double _energyLevel = 3.0;
  double _energyOutlook = 3.0; // NEW: Tracks perception of spent energy

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

  // UPDATED: Now passes the energyOutlook value to the next screen
  void _finishCheckIn() {
    Navigator.of(context).push(
      MaterialPageRoute(
        builder: (context) => AdaptiveAgendaScreen(
          energyLevel: _energyLevel,
          // We will update the AdaptiveAgendaScreen to accept this new parameter next
          // energyOutlook: _energyOutlook, 
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

  // UPDATED: This widget now contains both sliders
  Widget _buildEnergyLevelStep() {
    return Column(
      key: const ValueKey('energyStep'),
      crossAxisAlignment: CrossAxisAlignment.start,
      children: [
        const Text('Good morning.', style: TextStyle(fontSize: 20)),
        const SizedBox(height: 8),
        Text('Let\'s check in.',
            style: Theme.of(context).textTheme.headlineSmall),
        const Spacer(),
        
        // Current Energy Level Slider
        Semantics(
          label: "Current energy level slider",
          value: "Current level is ${_energyLevel.round()} out of 5",
          child: Column(
            children: [
              const Text("How is your energy right now?", style: TextStyle(fontSize: 16)),
              Center(
                child: Text(
                  _energyLevel.round().toString(),
                  style: const TextStyle(fontSize: 60, fontWeight: FontWeight.bold),
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
            ],
          ),
        ),
        const SizedBox(height: 32),

        // NEW: Energy Outlook / Recovery Slider
        Semantics(
          label: "Energy outlook slider",
          value: "Current outlook is ${_energyOutlook.round()} out of 5",
          child: Column(
            children: [
              const Text("How do you feel about using energy?", style: TextStyle(fontSize: 16)),
              Center(
                child: Text(
                  _energyOutlook.round().toString(),
                  style: const TextStyle(fontSize: 60, fontWeight: FontWeight.bold),
                ),
              ),
              Slider(
                value: _energyOutlook,
                min: 1,
                max: 5,
                divisions: 4,
                label: _energyOutlook.round().toString(),
                onChanged: (double value) {
                  setState(() {
                    _energyOutlook = value;
                  });
                },
              ),
              const Row(
                mainAxisAlignment: MainAxisAlignment.spaceBetween,
                children: [Text('Wary / Need to Recover'), Text('Confident / Ready to Act')],
              ),
            ],
          ),
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
        Semantics(
          label: "Select your current limitations",
          child: Wrap(
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
        Semantics(
          label: "Optional notes about your current needs.",
          child: TextField(
            controller: _notesController,
            maxLines: 5,
            decoration: InputDecoration(
              hintText: 'e.g., "A moment of quiet," "Some gentle stretching"...',
              border: OutlineInputBorder(
                borderRadius: BorderRadius.circular(12),
              ),
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
