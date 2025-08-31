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

import 'dart:async';
import 'package:flutter/material.dart';
import 'package:cloud_firestore/cloud_firestore.dart'; // Required for Timestamp
import 'package:firebase_core/firebase_core.dart'; // Required for Firebase initialization

import './adaptive_agenda_screen.dart';
import './firestore_service.dart'; // Import the new service

// You will need to add your own firebase_options.dart file from the FlutterFire CLI
// import 'firebase_options.dart'; 

void main() async {
  // Required for Firebase
  WidgetsFlutterBinding.ensureInitialized(); 
  // TODO: Uncomment and configure with your Firebase project
  // await Firebase.initializeApp(
  //   options: DefaultFirebaseOptions.currentPlatform,
  // );
  runApp(const AdvocacyOSApp());
}

class AdvocacyOSApp extends StatelessWidget {
  const AdvocacyOSApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'AdvocacyOS',
      theme: ThemeData(
        primarySwatch: Colors.indigo,
        fontFamily: 'Inter',
        scaffoldBackgroundColor: const Color(0xFFF5F5F7),
         textTheme: const TextTheme(
          headlineSmall: TextStyle(
              fontSize: 28.0,
              fontWeight: FontWeight.bold,
              color: Color(0xFF1D1D1F)),
          bodyLarge:
              TextStyle(fontSize: 18.0, color: Color(0xFF4A4A4A), height: 1.5),
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
      home: const DashboardScreen(), // The new home screen
    );
  }
}

/// The new main screen of the app, focusing on the work timer.
class DashboardScreen extends StatefulWidget {
  const DashboardScreen({super.key});

  @override
  State<DashboardScreen> createState() => _DashboardScreenState();
}

class _DashboardScreenState extends State<DashboardScreen> {
  final FirestoreService _firestoreService = FirestoreService();
  
  // Timer state
  Timer? _timer;
  int _sessionSeconds = 0;
  String? _currentSessionId;

  // Weekly progress state
  int _weeklyTotalSeconds = 0;
  bool _isLoading = true;
  
  // The goal: 33% of a 40-hour week in seconds.
  final int _weeklyGoalSeconds = (40 * 0.33 * 3600).toInt();

  @override
  void initState() {
    super.initState();
    _loadWeeklyProgress();
  }
  
  Future<void> _loadWeeklyProgress() async {
    setState(() => _isLoading = true);
    final weeklySeconds = await _firestoreService.getWeeklyWorkSeconds();
    if (mounted) {
      setState(() {
        _weeklyTotalSeconds = weeklySeconds;
        _isLoading = false;
      });
    }
  }

  void _toggleTimer() async {
    if (_timer?.isActive ?? false) {
      // Stop the timer
      _timer?.cancel();
      await _firestoreService.stopWorkSession(_currentSessionId!, _sessionSeconds);
      setState(() {
        _weeklyTotalSeconds += _sessionSeconds;
        _sessionSeconds = 0;
        _currentSessionId = null;
      });
    } else {
      // Start the timer
      final sessionId = await _firestoreService.startWorkSession();
      setState(() => _currentSessionId = sessionId);
      _timer = Timer.periodic(const Duration(seconds: 1), (timer) {
        setState(() {
          _sessionSeconds++;
        });
      });
    }
  }

  String _formatDuration(int totalSeconds) {
    final duration = Duration(seconds: totalSeconds);
    final hours = duration.inHours;
    final minutes = duration.inMinutes.remainder(60);
    final seconds = duration.inSeconds.remainder(60);
    return '${hours.toString().padLeft(2, '0')}:${minutes.toString().padLeft(2, '0')}:${seconds.toString().padLeft(2, '0')}';
  }

  @override
  void dispose() {
    _timer?.cancel();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    final bool isTimerRunning = _timer?.isActive ?? false;
    final double weeklyProgress = _weeklyTotalSeconds / _weeklyGoalSeconds;

    return Scaffold(
      appBar: AppBar(
        title: const Text('AdvocacyOS Dashboard'),
        backgroundColor: Colors.white,
        elevation: 1,
      ),
      body: Center(
        child: Padding(
          padding: const EdgeInsets.all(24.0),
          child: Column(
            mainAxisAlignment: MainAxisAlignment.center,
            children: <Widget>[
              const Text(
                'Life-System R&D Block',
                style: TextStyle(fontSize: 22, fontWeight: FontWeight.w600),
                textAlign: TextAlign.center,
              ),
              const SizedBox(height: 8),
              Text(
                'Weekly Goal: ${_formatDuration(_weeklyGoalSeconds)}',
                style: const TextStyle(fontSize: 16, color: Colors.black54),
              ),
              const SizedBox(height: 32),

              // Progress Indicator
              if (_isLoading)
                const CircularProgressIndicator()
              else
                Column(
                  children: [
                    LinearProgressIndicator(
                      value: weeklyProgress > 1.0 ? 1.0 : weeklyProgress,
                      minHeight: 12,
                      borderRadius: BorderRadius.circular(6),
                    ),
                    const SizedBox(height: 8),
                    Text(
                      'This Week: ${_formatDuration(_weeklyTotalSeconds)}',
                       style: const TextStyle(fontSize: 18, fontWeight: FontWeight.bold),
                    ),
                  ],
                ),
              
              const Spacer(),

              // Timer Display
              Text(
                _formatDuration(_sessionSeconds),
                style: const TextStyle(fontSize: 72, fontWeight: FontWeight.bold),
              ),
              const SizedBox(height: 32),

              // Start/Stop Button
              ElevatedButton(
                onPressed: _toggleTimer,
                style: ElevatedButton.styleFrom(
                  backgroundColor: isTimerRunning ? Colors.redAccent : Colors.green,
                  padding: const EdgeInsets.symmetric(horizontal: 50, vertical: 20),
                ),
                child: Text(
                  isTimerRunning ? 'Stop Session' : 'Start Session',
                  style: const TextStyle(fontSize: 20),
                ),
              ),

              const Spacer(),

              // Disabled button for the check-in flow
              ElevatedButton.icon(
                // The `onPressed: null` makes the button disabled.
                onPressed: null, 
                icon: const Icon(Icons.favorite_border),
                label: const Text('Compassionate Check-In'),
                style: ElevatedButton.styleFrom(
                  backgroundColor: Colors.grey.shade300,
                  foregroundColor: Colors.grey.shade600,
                ),
              ),
              const SizedBox(height: 8),
              const Text(
                '(Capability Engine features are in development)',
                style: TextStyle(fontSize: 12, color: Colors.grey),
              )
            ],
          ),
        ),
      ),
    );
  }
}


// --- The original check-in screen code is preserved below but is not currently used ---

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
  double _energyOutlook = 3.0;
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
  final TextEditingController _costController = TextEditingController();

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
    final double? cost = double.tryParse(_costController.text);

    Navigator.of(context).push(
      MaterialPageRoute(
        builder: (context) => AdaptiveAgendaScreen(
          energyLevel: _energyLevel,
          energyOutlook: _energyOutlook,
          limitations: _selectedLimitations,
          associatedCost: cost,
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
        Text('Let\'s check in.',
            style: Theme.of(context).textTheme.headlineSmall),
        const Spacer(),
        Semantics(
          label: "Current energy level slider",
          value: "Current level is ${_energyLevel.round()} out of 5",
          child: Column(
            children: [
              const Text("How is your energy right now?",
                  style: TextStyle(fontSize: 16)),
              Center(
                child: Text(
                  _energyLevel.round().toString(),
                  style: const TextStyle(
                      fontSize: 60, fontWeight: FontWeight.bold),
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
        Semantics(
          label: "Energy outlook slider",
          value: "Current outlook is ${_energyOutlook.round()} out of 5",
          child: Column(
            children: [
              const Text("How do you feel about using energy?",
                  style: TextStyle(fontSize: 16)),
              Center(
                child: Text(
                  _energyOutlook.round().toString(),
                  style: const TextStyle(
                      fontSize: 60, fontWeight: FontWeight.bold),
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
                children: [
                  Text('Wary / Need to Recover'),
                  Text('Confident / Ready to Act')
                ],
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
            maxLines: 3,
            decoration: InputDecoration(
              hintText: 'e.g., "A moment of quiet," "Some gentle stretching"...',
              border: OutlineInputBorder(
                borderRadius: BorderRadius.circular(12),
              ),
            ),
          ),
        ),
        const SizedBox(height: 24),
        Semantics(
          label: "Optional: associated cost to meet this need in dollars.",
          child: TextField(
            controller: _costController,
            keyboardType: const TextInputType.numberWithOptions(decimal: true),
            decoration: InputDecoration(
              hintText: 'e.g., "30.00"',
              labelText: 'Associated Cost to Meet This Need? (\$)',
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

