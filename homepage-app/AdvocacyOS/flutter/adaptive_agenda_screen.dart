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
import './ai_service.dart';
import './energy_ledger_screen.dart'; // Import the new screen

// A simple class to hold the data for a micro-task.
class MicroTask {
  final String description;
  bool isCompleted;

  MicroTask({required this.description, this.isCompleted = false});
}

class AdaptiveAgendaScreen extends StatefulWidget {
  final double energyLevel;
  final double energyOutlook;
  final List<String> limitations;
  final double? associatedCost;

  const AdaptiveAgendaScreen({
    super.key,
    required this.energyLevel,
    required this.energyOutlook,
    required this.limitations,
    this.associatedCost,
  });

  @override
  State<AdaptiveAgendaScreen> createState() => _AdaptiveAgendaScreenState();
}

class _AdaptiveAgendaScreenState extends State<AdaptiveAgendaScreen> {
  bool _isLoading = false;
  String _userGoal = '';
  List<MicroTask> _actionPlan = [];
  final TextEditingController _goalController = TextEditingController();

  // This function is called when the user taps "Create Action Plan".
  Future<void> _createPlan() async {
    if (_goalController.text.isEmpty) return;

    setState(() {
      _isLoading = true;
      _userGoal = _goalController.text;
    });

    // Call the mock AI service
    final plan = await AiService.getAdaptivePlan(
      goal: _userGoal,
      energyLevel: widget.energyLevel,
      energyOutlook: widget.energyOutlook,
      limitations: widget.limitations,
    );

    setState(() {
      _actionPlan = plan;
      _isLoading = false;
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Your Action Plan'),
        backgroundColor: Colors.white,
        foregroundColor: Colors.black,
        elevation: 1,
        // NEW: Button to navigate to the Energy Ledger
        actions: [
          Padding(
            padding: const EdgeInsets.only(right: 8.0),
            child: Semantics(
              label: "View your energy ledger",
              child: IconButton(
                icon: const Icon(Icons.assessment_outlined),
                onPressed: () {
                  Navigator.of(context).push(
                    MaterialPageRoute(
                      builder: (context) => const HolisticEnergyLedgerScreen(),
                    ),
                  );
                },
                tooltip: 'Energy Ledger',
              ),
            ),
          ),
        ],
      ),
      body: SafeArea(
        child: Padding(
          padding: const EdgeInsets.all(24.0),
          child: _userGoal.isEmpty
              ? _buildGoalInputView()
              : _buildLiveAgendaView(),
        ),
      ),
    );
  }

  // Builds the initial view where the user inputs their goal.
  Widget _buildGoalInputView() {
    String outlookText = "";
    if (widget.energyOutlook >= 4) {
      outlookText = "and I have noted your outlook on using it.";
    } else if (widget.energyOutlook <= 2) {
      outlookText = "and I have noted your wariness about using it.";
    } else {
      outlookText = "and I have noted your outlook on using it.";
    }

    return Column(
      crossAxisAlignment: CrossAxisAlignment.start,
      children: [
        Text(
          "Okay, you have provided to me that your energy level may be at a ${widget.energyLevel.round()} $outlookText Let's create a clear path forward.",
          style: Theme.of(context).textTheme.bodyLarge,
        ),
        const SizedBox(height: 16),
        Text(
          'What is one urgent thing you need to address right now?',
          style: Theme.of(context).textTheme.headlineSmall,
        ),
        const SizedBox(height: 24),
        Semantics(
          label: "Enter your urgent goal or situation.",
          child: TextField(
            controller: _goalController,
            decoration: InputDecoration(
              hintText:
                  'e.g., "My two support members are unreachable..."',
              border: OutlineInputBorder(
                borderRadius: BorderRadius.circular(12),
              ),
            ),
          ),
        ),
        const Spacer(),
        Center(
          child: _isLoading
              ? const CircularProgressIndicator()
              : ElevatedButton(
                  onPressed: _createPlan,
                  child: const Text('Create Action Plan'),
                ),
        ),
      ],
    );
  }

  // Builds the view that displays the live, interactive action plan.
  Widget _buildLiveAgendaView() {
    return Column(
      crossAxisAlignment: CrossAxisAlignment.start,
      children: [
        Text(
          'Emergency Plan:',
          style: Theme.of(context).textTheme.bodyLarge,
        ),
        Text(
          _userGoal,
          style: Theme.of(context).textTheme.headlineSmall,
        ),
        const SizedBox(height: 24),
        Card(
          elevation: 2,
          shape:
              RoundedRectangleBorder(borderRadius: BorderRadius.circular(12)),
          color: Colors.indigo[50],
          child: Padding(
            padding: const EdgeInsets.all(16.0),
            child: Semantics(
              label:
                  "AI generated suggestion.",
              child: Text(
                "Based on the information you have provided, I am generating a plan that prioritizes calm, grounding actions first. Here is a safe place to start. Take one step at a time.",
                style: TextStyle(
                    color: Colors.indigo[900],
                    fontStyle: FontStyle.italic,
                    height: 1.5),
              ),
            ),
          ),
        ),
        const SizedBox(height: 24),
        Expanded(
          child: ListView.builder(
            itemCount: _actionPlan.length,
            itemBuilder: (context, index) {
              final task = _actionPlan[index];
              return Card(
                margin: const EdgeInsets.symmetric(vertical: 6.0),
                child: CheckboxListTile(
                  title: Text(task.description),
                  value: task.isCompleted,
                  onChanged: (bool? value) {
                    setState(() {
                      task.isCompleted = value ?? false;
                    });
                  },
                  controlAffinity: ListTileControlAffinity.leading,
                ),
              );
            },
          ),
        ),
      ],
    );
  }
}

