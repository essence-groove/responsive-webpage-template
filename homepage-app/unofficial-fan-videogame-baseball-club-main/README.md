# APMW Baseball Simulator (unofficial-fan-videogame-baseball-club)

This is an unofficial fan-made baseball video game, serving as the **C++ 3.8.0 core** for the Ayurveda Project Management World (APMW) project. It is a text-based simulation of a baseball league's season schedule, built with a focus on modularity, agent-driven-logic, and deep lore integration.

## Generated Schedule

📄 [**View the Latest Generated Schedule (v3.8.0)**](schedule_report_v3.8.md)

*This report is automatically generated and updated by our CI/CD workflow on every push to the `main` branch.*

## Features (v3.8.0)

* **Sophisticated Concurrent Scheduling Engine:** The core of v3.8.0 is a completely re-architected `LeagueScheduler2` agent. It now manages multiple concurrent "scheduling windows," allowing several multi-week residency blocks to happen at the same time. This ensures a balanced, geographically distributed, and realistically timed season.

* **Flawless Extended Residency Consistency:** The scheduling algorithm has been meticulously refined to ensure the accurate calculation and distribution of all games (Regular, Crossroads, and Regional) within the complex, extended residency blocks.

* **Precise Rest Day Management:** The system now precisely accounts for and schedules travel/rest days, ensuring player wellness and logistical realism are built directly into the schedule's DNA.

* **Location-Aware Environmentalism:** Leverages geographical data to provide more nuanced and meaningful environmental notes in the schedule report, particularly for fan travel during Regional Games.

* **Modular C++ Core:** Built with a clean separation of concerns, separating data structures (players, teams, geography) from the advanced scheduling logic.

* **CMake Build System:** Uses a modern CMake configuration (C++23 standard) for robust and scalable builds.

## How to Build and Run

This project uses CMake. You will need a C++ compiler (like G++, Clang, or MSVC) and CMake installed.

1.  **Clone the repository:**
    ```bash
    git clone [https://github.com/your-username/unofficial-fan-videogame-baseball-club.git](https://github.com/your-username/unofficial-fan-videogame-baseball-club.git)
    cd unofficial-fan-videogame-baseball-club
    ```

2.  **Configure the project with CMake:**
    ```bash
    # This creates a 'build' directory and generates the build files inside it.
    cmake -S . -B build
    ```

3.  **Compile the code:**
    ```bash
    # This runs the actual compilation process.
    cmake --build build
    ```

4.  **Run the executable:**
    ```bash
    # The executable will be inside the 'build' directory.
    ./build/apmw_baseball_simulator
    ```

## License

This project is licensed under the GNU Affero General Public License v3.0. See the [LICENSE](LICENSE) file for details.
