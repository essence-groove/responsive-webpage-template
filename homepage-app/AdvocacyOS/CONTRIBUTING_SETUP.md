##### AdvocacyOS Contributor Setup Guide
### Contributor Setup Guide: AdvocacyOS
Welcome to the AdvocacyOS project! We're thrilled you're here to help. This guide will walk you through setting up your local development environment so you can get the application running and start contributing.

##### Prerequisites
Before you begin, please make sure you have **Git** installed on your system. You can download it from git-scm.com [1].

##### Step 1: Get the Project Code
First, you need to clone the project's repository from GitHub to your local machine. Open your terminal or command prompt and run the following command:

```
git clone https://github.com/your-username/advocacyos.git
```
This will download the entire homepage-app repository. Navigate into the AdvocacyOS project directory:
```
cd homepage-app/AdvocacyOS
```

Navigate into the newly created project directory:
cd advocacyos
[2]

##### Step 2: Install the Flutter SDK
AdvocacyOS is built with Flutter [2]. To ensure compatibility, we are targeting **Flutter version 3.35** which uses **Dart 3.9** [2].
The best way to install Flutter is by following the official documentation, as it provides the most up-to-date, step-by-step instructions for your specific operating system (Windows, macOS, or Linux) [2].
[➡️ **Follow the Official Flutter Installation Guide**](https://docs.flutter.dev/get-started/install) [2]

After installation, you can ensure you are on the correct version by running `flutter --version` [3].

##### Step 3: Verify Your Setup
Flutter comes with a handy tool called `flutter doctor` that checks your environment and displays a report of the status of your installation [3]. Run this command to see if there are any dependencies you need to install or tasks you need to perform [3].
```
flutter doctor
```
Address any issues that `flutter doctor` reports before proceeding [3].

##### Step 4: Install Project Dependencies
Once your Flutter environment is ready, you need to install the specific packages that AdvocacyOS depends on. These are listed in the `pubspec.yaml` file [4].

From the root of the project directory, run:
```
flutter pub get
```
This command will download all the necessary packages into your project [4].

##### Step 5: Run the App
You're all set! You can now run the application on a connected device, simulator (iOS), or emulator (Android) [4].
```
flutter run
```
The app should now build and launch [4]. Because we are using a mock AI service for the initial MVP, you will be able to test the full user flow without needing an API key [4].

Thank you for contributing to AdvocacyOS! We look forward to seeing your work [4].

