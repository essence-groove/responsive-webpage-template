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

class AdaptiveAgendaScreen extends StatefulWidget {
  final double energyLevel;
  final double energyOutlook;
  final List<String> limitations;
  final double associatedCost; // NEW: Added cost parameter

  const AdaptiveAgendaScreen({
    super.key,
    required this.energyLevel,
    required this.energyOutlook,
    required this.limitations,
    required this.associatedCost, // NEW: Required in constructor
  });

  @override
  State<AdaptiveAgendaScreen> createState() => _AdaptiveAgendaScreenState();
}

class _AdaptiveAgendaScreenState extends State<AdaptiveAgendaScreen> {
  bool _isLoading = false;
  List<MicroTask> _plan = [];
  final TextEditingController _goalController = TextEditingController();
  bool _planCreated = false;

  Future<void> _createPlan() async {
    if (_goalController.text.isEmpty) return;

    setState(() {
      _isLoading = true;
      _planCreated = true;
    });

    final plan = await AiService.getAdaptivePlan(
      goal: _goalController.text,
      energyLevel: widget.energyLevel,
      energyOutlook: widget.energyOutlook,
      limitations: widget.limitations,
    );

    setState(() {
      _plan = plan;
      _isLoading = false;
    });
  }

  @override
  void dispose() {
    _goalController.dispose();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Your Action Plan'),
        backgroundColor: Colors.indigo,
        foregroundColor: Colors.white,
      ),
      body: Padding(
        padding: const EdgeInsets.all(24.0),
        child: _planCreated ? _buildLiveAgendaView() : _buildGoalInputView(),
      ),
    );
  }

  Widget _buildGoalInputView() {
    String outlookText = "";
    if (widget.energyOutlook <= 2) {
      outlookText = "and I hear that you're feeling wary right now.";
    } else if (widget.energyOutlook >= 4) {
      // UPDATED: Changed from "understand" to "noted" for neutrality.
      outlookText = "and I've noted your outlook on using it.";
    } else {
      // UPDATED: Changed from "understand" to "noted" for neutrality.
      outlookText = "and I've noted your outlook.";
    }

    return Column(
      crossAxisAlignment: CrossAxisAlignment.start,
      children: [
        Text(
          "Okay, you've shared that your energy level is around a ${widget.energyLevel.round()}. $outlookText Let's create a clear path forward.",
          style: Theme.of(context).textTheme.bodyLarge,
        ),
        const SizedBox(height: 24),
        Text(
          "What is the most urgent thing you need to accomplish?",
          style: Theme.of(context).textTheme.headlineSmall,
        ),
        const SizedBox(height: 16),
        Semantics(
          label: "Input for your most urgent goal or situation.",
          child: TextField(
            controller: _goalController,
            decoration: InputDecoration(
              hintText:
                  'e.g., "My two support relatives are unresponsive"',
              border: OutlineInputBorder(
                borderRadius: BorderRadius.circular(12),
              ),
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
    if (_isLoading) {
      return const Center(child: CircularProgressIndicator());
    }

    return Column(
      crossAxisAlignment: CrossAxisAlignment.start,
      children: [
        Text(
          _goalController.text,
          style: Theme.of(context).textTheme.headlineSmall,
        ),
        const SizedBox(height: 16),
        Semantics(
          label: "AI-suggested first step.",
          child: Card(
            elevation: 2,
            shape:
                RoundedRectangleBorder(borderRadius: BorderRadius.circular(12)),
            child: const Padding(
              padding: EdgeInsets.all(16.0),
              child: Text(
                "Here is a safe, grounding place to start. Take one step at a time.",
                style: TextStyle(fontSize: 16, fontStyle: FontStyle.italic),
              ),
            ),
          ),
        ),
        const SizedBox(height: 24),
        Expanded(
          child: ListView.builder(
            itemCount: _plan.length,
            itemBuilder: (context, index) {
              final task = _plan[index];
              return Semantics(
                label:
                    "Task ${index + 1}: ${task.description}. Status: ${task.isCompleted ? 'Completed' : 'Not completed'}",
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

class MicroTask {
  final String description;
  bool isCompleted;

  MicroTask({required this.description, this.isCompleted = false});
}

