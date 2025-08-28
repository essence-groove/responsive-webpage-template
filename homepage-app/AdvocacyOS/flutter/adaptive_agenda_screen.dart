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

  // **UPDATED UI TEXT**
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
            // **UPDATED HINT TEXT for Escalated Emergency**
            hintText: 'e.g., "My essential support plan has failed"',
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
      return const Center(
          child: Text("No tasks were generated. Please try again."));
    }

    final String aiSuggestion = "Let's start with one small, grounding step.";
    final MicroTask currentTask = _tasks.firstWhere(
        (task) => !task.isCompleted,
        orElse: () => _tasks.first);

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
