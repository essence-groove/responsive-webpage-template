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

/// A class designed to act as a 'Table of Contents' for the project's
/// documentation. Each static constant holds a piece of the contributor setup
/// guide, allowing for programmatic access and display within the app.
///
/// This approach makes the documentation a part of the app itself, ensuring it
/// is always up-to-date and easily accessible to contributors.
class ContributorGuide {
  /// The main title and welcome message for the guide.
  static const String header = '''
### Contributor Setup Guide: AdvocacyOS
Welcome to the AdvocacyOS project! We're thrilled you're here to help. This guide will walk you through setting up your local development environment so you can get the application running and start contributing.
''';

  /// A section detailing the necessary prerequisites before starting.
  static const String prerequisites = '''
##### Prerequisites
Before you begin, please make sure you have **Git** installed on your system. You can download it from git-scm.com.
''';

  /// Step 1: Instructions for cloning the project repository from GitHub.
  static const String step1_getTheCode = '''
##### Step 1: Get the Project Code
First, you need to clone the project's repository from GitHub to your local machine. Open your terminal or command prompt and run the following command:

`git clone https://github.com/essence-groove/homepage-app.git`

This will download the entire homepage-app repository. Navigate into the AdvocacyOS project directory:

`cd homepage-app/AdvocacyOS`
''';

  /// Step 2: Instructions for installing the correct Flutter SDK version.
  static const String step2_installFlutter = '''
##### Step 2: Install the Flutter SDK
AdvocacyOS is built with Flutter. To ensure compatibility, we are targeting **Flutter version 3.35** which uses **Dart 3.9**.

The best way to install Flutter is by following the official documentation, as it provides the most up-to-date, step-by-step instructions for your specific operating system (Windows, macOS, or Linux).

[➡️ **Follow the Official Flutter Installation Guide**](https://docs.flutter.dev/get-started/install)

After installation, you can ensure you are on the correct version by running `flutter --version`.
''';

  /// Step 3: Instructions for verifying the local development setup.
  static const String step3_verifySetup = '''
##### Step 3: Verify Your Setup
Flutter comes with a handy tool called `flutter doctor` that checks your environment and displays a report of the status of your installation. Run this command to see if there are any dependencies you need to install or tasks you need to perform.

`flutter doctor`

Address any issues that `flutter doctor` reports before proceeding.
''';

  /// Step 4: Instructions for installing the project's dependencies.
  static const String step4_installDependencies = '''
##### Step 4: Install Project Dependencies
Once your Flutter environment is ready, you need to install the specific packages that AdvocacyOS depends on. These are listed in the `pubspec.yaml` file.

From the root of the project directory, run:

`flutter pub get`

This command will download all the necessary packages into your project.
''';

  /// Step 5: Instructions for running the application.
  static const String step5_runTheApp = '''
##### Step 5: Run the App
You're all set! You can now run the application on a connected device, simulator (iOS), or emulator (Android).

`flutter run`

The app should now build and launch. Because we are using a mock AI service for the initial MVP, you will be able to test the full user flow without needing an API key.
''';

  /// The closing message for the contributor guide.
  static const String footer = '''
Thank you for contributing to AdvocacyOS! We look forward to seeing your work.
''';
}
