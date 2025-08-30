AdvocacyOS Contributor Setup Guide
### Contributor Setup Guide: AdvocacyOS
Welcome to the AdvocacyOS project! We're thrilled you're here to help. This guide will walk you through setting up your local development environment so you can get the application running and start contributing [1-5].

##### Prerequisites
Before you begin, please make sure you have **Git** installed on your system. You can download it from git-scm.com [1-5].

##### Step 1: Get the Project Code
First, you need to clone the project's repository from GitHub to your local machine. Open your terminal or command prompt and run the following command [1-5]:

git clone https://github.com/essence-groove/homepage-app.git
This will download the entire homepage-app repository. Navigate into the AdvocacyOS project directory [2, 3, 6, 7]:

cd homepage-app/AdvocacyOS

##### Step 2: Install the Flutter SDK
AdvocacyOS is built with Flutter [1-8]. To ensure compatibility, we are targeting **Flutter version 3.35** which uses **Dart 3.9** [1-9].
The best way to install Flutter is by following the official documentation, as it provides the most up-to-date, step-by-step instructions for your specific operating system (Windows, macOS, or Linux) [1-3, 5-9].
➡️ **Follow the Official Flutter Installation Guide** [9]
After installation, you can ensure you are on the correct version by running `flutter --version` [10].

##### Step 3: Verify Your Setup
Flutter comes with a handy tool called `flutter doctor` that checks your environment and displays a report of the status of your installation. Run this command to see if there are any dependencies you need to install or tasks you need to perform [10, 11].

flutter doctor
Address any issues that `flutter doctor` reports before proceeding [10].

##### Step 4: Install Project Dependencies
Once your Flutter environment is ready, you need to install the specific packages that AdvocacyOS depends on. These are listed in the `pubspec.yaml` file [10].

flutter pub get

##### Step 5: Run the Application
Finally, you can run the AdvocacyOS application on a connected device or emulator [11].

flutter run
Thank you for contributing to AdvocacyOS! We look forward to seeing your work [12, 13].
