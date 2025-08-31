/*
 * AdvocacyOS: A Personal Operating System for Justice
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

/// A document capturing the strategic shift from experimental R&D to an
/// AI-driven efficiency estimation framework. This class serves as a "Table of
/// Contents" for the new methodology, detailing the prompts and the integration
/// with the APM IO user interface.
class AiDrivenRAndDFrameworkDoc {
  /// ## Introduction: A Strategic Shift to AI-Driven Estimation
  /// This document outlines a strategic shift in the "Life-System Integration &
  /// R&D" framework. Instead of using personal time to conduct manual,
  /// experimental R&D (e.g., timing appliance energy usage), the new approach
  /// leverages an advanced AI model as a strategic consultant. This is a more
  /// efficient, higher-leverage use of time, aligning with the "Ayurveda Tycoon"
  /// model. The AI will generate baseline estimates and optimal workflows,
  /// allowing the project to start with a data-driven plan.
  static const String introduction = '''
### Introduction: A Strategic Shift to AI-Driven Estimation
This document outlines a strategic shift in the "Life-System Integration & R&D" framework. Instead of using personal time to conduct manual, experimental R&D (e.g., timing appliance energy usage), the new approach leverages an advanced AI model as a strategic consultant. This is a more efficient, higher-leverage use of time, aligning with the "Ayurveda Tycoon" model. The AI will generate baseline estimates and optimal workflows, allowing the project to start with a data-driven plan.
''';

  /// ## 1. Methodology: Strategic Prompt Engineering
  /// The core of this framework is the use of carefully engineered prompts to
  /// extract specific, actionable data from the AI model. The AI's responses
  /// will provide the initial estimates before any real-world experiments are
  /// conducted.
  static const String methodology = '''
### 1. Methodology: Strategic Prompt Engineering
The core of this framework is the use of carefully engineered prompts to extract specific, actionable data from the AI model. The AI's responses will provide the initial estimates before any real-world experiments are conducted.
''';

  /// ### 1.1. Prompt for Energy Efficiency (Reheating Meal)
  /// This prompt is designed to get a probable estimate of energy savings without
  /// needing a physical electricity usage monitor.
  static const String energyEfficiencyPrompt = '''
### 1.1. Prompt for Energy Efficiency (Reheating Meal)
```
Based on general principles of thermodynamics and typical energy consumption of modern kitchen appliances, compare the probable electricity usage (in kWh) of reheating a single-serving, pre-cooked meal from the refrigerator to a standard eating temperature using an electric stovetop versus a countertop electric pressure cooker. Provide a percentage estimate of the potential energy savings.
```
''';

  /// ### 1.2. Prompt for Physical Asset Liquidation
  /// This prompt is designed to generate a project plan with time estimates for
  /// a key "Life-System Integration" task.
  static const String assetLiquidationPrompt = '''
### 1.2. Prompt for Physical Asset Liquidation
```
Create a project plan for liquidating 50 non-essential items from a storage unit. Break down the process into key phases: inventory/sorting, research/pricing, photography/listing, and packing/shipping. Provide a realistic time estimate in hours for each phase, assuming the goal is to maximize capital return.
```
''';

  /// ### 1.3. Prompt for Digital Asset Conversion
  /// This prompt is designed to generate a scalable workflow and time estimate
  /// for another key "Life-System Integration" task.
  static const String documentConversionPrompt = '''
### 1.3. Prompt for Digital Asset Conversion
```
Outline a scalable workflow for digitizing 3 standard file boxes of physical documents. The goal is to create organized, secure digital files while minimizing physical clutter. Provide a time estimate in hours for the entire process, including scanning, OCR processing, and a simple tagging/organization scheme.
```
''';

  /// ## 2. Integration with APM IO UI/UX (The Payoff)
  /// The outputs from these AI queries will serve as the initial, estimated data
  /// that populates the "Detailed Cycle & Vault View" in the Ayurveda Project
  /// Management IO platform. This transforms the wireframes from a design concept
  /// into a pre-populated, strategic dashboard.
  static const String uiIntegration = '''
### 2. Integration with APM IO UI/UX (The Payoff)
The outputs from these AI queries will serve as the initial, estimated data that populates the "Detailed Cycle & Vault View" in the Ayurveda Project Management IO platform. This transforms the wireframes from a design concept into a pre-populated, strategic dashboard.
''';

  /// ### 2.1. Updated "Energy Economy & Budgeting" Card Wireframe
  /// This wireframe shows how the AI-generated energy analysis directly informs
  /// the strategic insight engine.
  static const String energyEconomyCardWireframe = '''
### 2.1. Updated "Energy Economy & Budgeting" Card Wireframe
**(Card Title): ⚡️ Energy Economy & Budgeting**

*Note: The values shown below are examples of the initial estimates the AI is expected to generate based on the prompts. They serve as a starting point for strategic planning.*

*Header: Efficiency Insight: Reheating Meal Analysis*
*Content:*
  - **AI-Generated Finding:** The AI model estimates that using the **pressure cooker** for reheating likely reduces direct energy costs by **40-50%** per meal compared to the stove.
  - **Initial Data (AI Estimate):**
    - Stove Avg. Cost: **~\$0.15 / meal**
    - Pressure Cooker Avg. Cost: **~\$0.08 / meal**
  - **Actionable Recommendation (AI-Generated):**
    - **Strategy:** The AI recommends prioritizing the pressure cooker for reheating to optimize your "\$ENERGY" vault, with a projected annual savings of **~\$25.00**.
''';

  /// ### 2.2. New "Physical Asset Liquidation" Card Wireframe
  /// This new card demonstrates how the AI-generated project plan is visualized
  /// as an actionable strategy.
  static const String assetLiquidationCardWireframe = '''
### 2.2. New "Physical Asset Liquidation" Card Wireframe
**(Card Title): 📦 Physical Asset Liquidation**

*Note: The values shown below are examples of the initial estimates the AI is expected to generate based on the prompts. They serve as a starting point for strategic planning.*

*Header: Projected Workflow & Time Allocation*
*Content:*
  - **AI-Generated Project Plan (50 Items):**
    - Inventory & Sorting: **~4 hours**
    - Research & Pricing: **~6 hours**
    - Photography & Listing: **~8 hours**
    - Packing & Shipping: **~5 hours**
  - **Actionable Recommendation (AI-Generated):**
    - **Strategy:** The AI recommends allocating **~23 hours** from your `Samadhi` cycle over the next 4-6 weeks to complete this objective.
''';

  /// ### 2.3. New "Digital Asset Conversion" Card Wireframe
  /// This new card shows how the AI-generated workflow for digitization is
  /// translated into a clear, time-bound objective.
  static const String documentConversionCardWireframe = '''
### 2.3. New "Digital Asset Conversion" Card Wireframe
**(Card Title): 📄 Digital Asset Conversion**

*Note: The values shown below are examples of the initial estimates the AI is expected to generate based on the prompts. They serve as a starting point for strategic planning.*

*Header: Projected Workflow & Time Allocation*
*Content:*
  - **AI-Generated Workflow (3 Boxes):**
    - Scanning: **~6 hours**
    - OCR & Processing: **~2 hours**
    - Tagging & Organization: **~4 hours**
  - **Actionable Recommendation (AI-Generated):**
    - **Strategy:** The AI recommends allocating **~12 hours** from your `Samadhi` cycle to complete this objective.
''';
}

