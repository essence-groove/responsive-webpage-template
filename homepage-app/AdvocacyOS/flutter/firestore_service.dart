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

import 'package:cloud_firestore/cloud_firestore.dart';

/// A service class to handle all interactions with the Firestore database.
class FirestoreService {
  final FirebaseFirestore _db = FirebaseFirestore.instance;
  // This would be replaced with the actual authenticated user's ID.
  final String _userId = "eeshvar_das_dev"; 

  /// Starts a new work session by creating a document in the `work_sessions` collection.
  /// Returns the ID of the new session document.
  Future<String> startWorkSession() async {
    final session = {
      'userId': _userId,
      'startTime': FieldValue.serverTimestamp(),
      'endTime': null,
      'durationInSeconds': 0,
    };
    final docRef = await _db.collection('work_sessions').add(session);
    return docRef.id;
  }

  /// Stops a work session by updating the document with an end time and duration.
  Future<void> stopWorkSession(String sessionId, int durationInSeconds) async {
    await _db.collection('work_sessions').doc(sessionId).update({
      'endTime': FieldValue.serverTimestamp(),
      'durationInSeconds': durationInSeconds,
    });
  }

  /// Fetches all work sessions for the current week to calculate total time.
  /// This is a foundational query for the dashboard.
  Future<int> getWeeklyWorkSeconds() async {
    // Get the start and end of the current week (assuming Sunday is the first day)
    final now = DateTime.now();
    final startOfWeek = now.subtract(Duration(days: now.weekday % 7));
    final endOfWeek = startOfWeek.add(const Duration(days: 7));

    final querySnapshot = await _db
        .collection('work_sessions')
        .where('userId', isEqualTo: _userId)
        .where('startTime', isGreaterThanOrEqualTo: Timestamp.fromDate(startOfWeek))
        .where('startTime', isLessThan: Timestamp.fromDate(endOfWeek))
        .get();

    int totalSeconds = 0;
    for (var doc in querySnapshot.docs) {
      totalSeconds += (doc.data()['durationInSeconds'] as num).toInt();
    }
    return totalSeconds;
  }
}
