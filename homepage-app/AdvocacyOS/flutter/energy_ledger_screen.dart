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

// Represents a single loggable item in the ledger.
class LedgerItem {
  final IconData icon;
  final String label;

  LedgerItem({required this.icon, required this.label});
}

class HolisticEnergyLedgerScreen extends StatefulWidget {
  const HolisticEnergyLedgerScreen({super.key});

  @override
  State<HolisticEnergyLedgerScreen> createState() =>
      _HolisticEnergyLedgerScreenState();
}

class _HolisticEnergyLedgerScreenState
    extends State<HolisticEnergyLedgerScreen> {
  // Mock data for the energy balance. In a real app, this would come from a state management solution.
  double _energyBalance = 0.6; // Represents 60% replenished

  // Define the credit and debit items
  final List<LedgerItem> _energyCredits = [
    LedgerItem(icon: Icons.water_drop, label: 'Hydrated Well'),
    LedgerItem(icon: Icons.restaurant, label: 'Nutritious Meal'),
    LedgerItem(icon: Icons.bedtime, label: 'Quality Sleep'),
    LedgerItem(icon: Icons.self_improvement, label: 'Gentle Movement'),
    LedgerItem(icon: Icons.wb_sunny, label: 'Time Outside'),
    LedgerItem(icon: Icons.favorite, label: 'Positive Connection'),
  ];

  final List<LedgerItem> _energyDebits = [
    LedgerItem(icon: Icons.fastfood, label: 'Processed Food'),
    LedgerItem(icon: Icons.no_food, label: 'Skipped Meal'),
    LedgerItem(icon: Icons.fitness_center, label: 'Overexertion'),
    LedgerItem(icon: Icons.access_time_filled, label: 'Skipped Rest'),
    LedgerItem(icon: Icons.cloudy, label: 'Stressful Event'),
    LedgerItem(icon: Icons.nightlight_round, label: 'Poor Sleep'),
  ];

  void _logEntry(bool isCredit) {
    setState(() {
      // Animate the energy balance bar. This is a simple simulation.
      if (isCredit) {
        _energyBalance = (_energyBalance + 0.05).clamp(0.0, 1.0);
        ScaffoldMessenger.of(context).showSnackBar(
          const SnackBar(
            content: Text('Noted. Thank you for taking that time for yourself.'),
            backgroundColor: Colors.green,
            duration: Duration(seconds: 2),
          ),
        );
      } else {
        _energyBalance = (_energyBalance - 0.05).clamp(0.0, 1.0);
        ScaffoldMessenger.of(context).showSnackBar(
          const SnackBar(
            content: Text('Noted.'),
            backgroundColor: Colors.black87,
            duration: Duration(seconds: 2),
          ),
        );
      }
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Holistic Energy Ledger'),
        backgroundColor: Colors.white,
        foregroundColor: Colors.black,
        elevation: 1,
      ),
      body: SingleChildScrollView(
        child: Padding(
          padding: const EdgeInsets.all(16.0),
          child: Column(
            crossAxisAlignment: CrossAxisAlignment.start,
            children: [
              _buildEnergyBalanceBar(),
              const SizedBox(height: 24),
              _buildLedgerSection(
                title: 'Log an Energy Credit',
                items: _energyCredits,
                isCredit: true,
                headerColor: Colors.green.shade700,
              ),
              const SizedBox(height: 24),
              _buildLedgerSection(
                title: 'Log an Energy Debit',
                items: _energyDebits,
                isCredit: false,
                headerColor: Colors.grey.shade800,
              ),
            ],
          ),
        ),
      ),
    );
  }

  // Builds the "Energy Balance" visualization bar at the top of the screen.
  Widget _buildEnergyBalanceBar() {
    return Semantics(
      label: "Your current energy balance is ${_energyBalance * 100}% replenished.",
      child: Column(
        crossAxisAlignment: CrossAxisAlignment.start,
        children: [
          Text(
            'Your Energy Balance',
            style: Theme.of(context).textTheme.titleLarge?.copyWith(fontWeight: FontWeight.bold),
          ),
          const SizedBox(height: 8),
          Container(
            height: 25,
            decoration: BoxDecoration(
              color: Colors.grey.shade300,
              borderRadius: BorderRadius.circular(12.5),
            ),
            child: ClipRRect(
              borderRadius: BorderRadius.circular(12.5),
              child: AnimatedContainer(
                duration: const Duration(milliseconds: 500),
                width: MediaQuery.of(context).size.width * _energyBalance,
                color: Colors.teal,
              ),
            ),
          ),
          const SizedBox(height: 4),
          const Row(
            mainAxisAlignment: MainAxisAlignment.spaceBetween,
            children: [
              Text('Depleted', style: TextStyle(color: Colors.grey)),
              Text('Replenished', style: TextStyle(color: Colors.grey)),
            ],
          ),
        ],
      ),
    );
  }

  // A reusable function to build a section for either credits or debits.
  Widget _buildLedgerSection({
    required String title,
    required List<LedgerItem> items,
    required bool isCredit,
    required Color headerColor,
  }) {
    return Column(
      crossAxisAlignment: CrossAxisAlignment.start,
      children: [
        Text(
          title,
          style: TextStyle(
            fontSize: 18,
            fontWeight: FontWeight.bold,
            color: headerColor,
          ),
        ),
        const SizedBox(height: 12),
        GridView.builder(
          physics: const NeverScrollableScrollPhysics(),
          shrinkWrap: true,
          gridDelegate: const SliverGridDelegateWithFixedCrossAxisCount(
            crossAxisCount: 3,
            crossAxisSpacing: 12,
            mainAxisSpacing: 12,
            childAspectRatio: 1,
          ),
          itemCount: items.length,
          itemBuilder: (context, index) {
            final item = items[index];
            return _buildLedgerCard(item, isCredit);
          },
        ),
      ],
    );
  }

  // Builds a single tappable card for the grid.
  Widget _buildLedgerCard(LedgerItem item, bool isCredit) {
    return Semantics(
      button: true,
      label: "Log ${item.label}",
      child: InkWell(
        onTap: () => _logEntry(isCredit),
        borderRadius: BorderRadius.circular(12),
        child: Card(
          elevation: 2,
          shape: RoundedRectangleBorder(
            borderRadius: BorderRadius.circular(12),
          ),
          child: Column(
            mainAxisAlignment: MainAxisAlignment.center,
            children: [
              Icon(item.icon, size: 32, color: Colors.indigo),
              const SizedBox(height: 8),
              Text(
                item.label,
                textAlign: TextAlign.center,
                style: const TextStyle(fontSize: 12),
              ),
            ],
          ),
        ),
      ),
    );
  }
}
