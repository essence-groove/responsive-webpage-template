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

/// A definitive, API-ready guide to the AdvocacyOS Firestore database schema.
///
/// This document serves as the architectural blueprint for the backend data structures.
/// It is designed to be the single source of truth for all database interactions,
/// ensuring consistency and clarity for development and future integrations.
///
/// **Project Versions:**
/// - **AdvocacyOS Version:** 1.0 (in development)
/// - **APM IO Version:** 1.0 (in development)
/// - **APM-WORLD Version:** 7.0.0 (in development)
///
/// **Core Principles:**
/// 1. **Security First:** Assumes a non-negotiable, secure Google Cloud perimeter
///    and HIPAA-compliant data handling.
/// 2. **Iterative Evolution:** This schema is the baseline for APMW 7.0.0 and is
///    designed to be extensible with a clear versioning strategy.
///
class AdvocacyOSDatabaseSchema {
  /// **Collection: work_sessions**
  ///
  /// Tracks the time spent in the "Life-System Integration & R&D Block".
  /// This is the foundational data for measuring and optimizing the 33% of the
  /// 40-hour work week dedicated to this cycle.
  static const String workSessions = '''
    Collection: work_sessions
    - sessionId (Document ID)
      - userId: String (Reference to users)
      - startTime: Timestamp
      - endTime: Timestamp (null until session ends)
      - durationInSeconds: Number
  ''';

  /// **Collection: users**
  ///
  /// Stores core user account information. Designed to be minimal and secure.
  static const String users = '''
    Collection: users
    - userId (Document ID)
      - email: String (Encrypted)
      - createdAt: Timestamp
      - schemaVersion: String (e.g., "1.0") - For managing data model migrations.
  ''';

  /// **Collection: case_files**
  ///
  /// The central collection for the external advocacy features of AdvocacyOS.
  /// Each document represents a distinct case a user is managing.
  static const String caseFiles = '''
    Collection: case_files
    - caseFileId (Document ID)
      - userId: String (Reference to users)
      - title: String (e.g., "Housing Dispute")
      - createdAt: Timestamp
      - status: String (e.g., "open", "closed")
      - incidents: Sub-collection of incident documents.
      - evidence: Sub-collection of evidence documents.
  ''';

  /// **Collection: check_ins**
  ///
  /// Captures the daily "Compassionate Check-In" data. This is the primary
  /// source for the "Acknowledge" phase of the Capability Engine and provides
  /// the core snapshot of the user's state for APM IO analysis.
  static const String checkIns = '''
    Collection: check_ins
    - checkInId (Document ID)
      - userId: String (Reference to users)
      - timestamp: Timestamp
      - energyLevel: Number (1-5)
      - energyOutlook: Number (1-5)
      - limitations: Array<String>
      - associatedCost: Number (Optional)
      - privacySetting: String (e.g., "private", "allow_anonymized_analysis")
  ''';

  /// **Collection: energy_ledger_entries**
  ///
  /// Stores all "Energy Credit" and "Energy Debit" entries for the
  /// "Holistic Energy Ledger". This data fuels the "Energy Economy" analysis.
  static const String energyLedgerEntries = '''
    Collection: energy_ledger_entries
    - entryId (Document ID)
      - userId: String (Reference to users)
      - timestamp: Timestamp
      - entryType: String ("CREDIT" or "DEBIT")
      - entryCategory: String ("Financial" or "Wellness")
      - entryDescription: String (e.g., "Nutritious Home-Cooked Meal")
      - entryValue: Number (Optional, for financial entries)
      - tags: Array<String> (e.g., ["pressure-cooker", "5-minutes"])
      - relatedCheckInId: String (Reference to check_ins)
  ''';

  /// **Collection: ai_interactions**
  ///
  /// Logs every interaction with the AI model for the purpose of the
  /// "AdvocacyOS Evaluation and Review Workflow". This is the foundation for
  /// ensuring AI safety, transparency, and continuous improvement.
  static const String aiInteractions = '''
    Collection: ai_interactions
    - interactionId (Document ID)
      - userId: String (Reference to users)
      - timestamp: Timestamp
      - userQuery: String (The user's goal/situation)
      - aiPrompt: String (The full, safety-engineered prompt sent to the AI)
      - aiResponse: String (The raw response from the AI)
      - userRating: Map ({accuracy, safety, tone, actionability})
      - status: String (e.g., "pending_review", "reviewed")
  ''';

  /// **Collection: evaluator_members**
  ///
  /// Manages the membership status for the "AdvocacyOS Evaluation Membership" program.
  static const String evaluatorMembers = '''
    Collection: evaluator_members
    - userId (Document ID)
      - membershipStatus: String (e.g., "active", "expired")
      - role: String (e.g., "peer_evaluator")
  ''';

  /// **Collection: schema_migrations**
  ///
  /// A critical component for the iterative deployment strategy. This collection
  /// provides a clear audit trail of all database schema changes.
  static const String schemaMigrations = '''
    Collection: schema_migrations
    - migrationId (Document ID)
      - version: String (e.g., "7.1.0")
      - description: String (e.g., "Add relatedCheckInId to energy_ledger_entries")
      - executedAt: Timestamp
  ''';
}
