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
