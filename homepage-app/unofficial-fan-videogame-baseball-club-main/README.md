# APMW Baseball Simulator (unofficial-fan-videogame-baseball-club)

This is an unofficial fan-made baseball video game, serving as the **C++ 3.9.0 core** for the Ayurveda Project Management World (APMW) project. It is a text-based simulation of a baseball league's season schedule, built with a focus on modularity, agent-driven-logic, and deep lore integration.

## Generated Schedule

📄 [**View the Latest Generated Schedule (v3.9.0)**](schedule_report_v3.9.md)

*This report is automatically generated and updated by our CI/CD workflow on every push to the `main` branch.*

## Features (v3.9.0)

* **Advanced Apex Residency Mechanics:** The core of v3.9.0 is a new strategic layer built around the season-ending Apex Residency event.
    * **Dynamic "Earned Participation":** Players are now selected for the Apex event based on a simulated regular season performance, ensuring a different lineup of teams and players in every simulation.
    * **Strategic "Capture the Flag" System:** Teams earn "Apex Points" based on their performance in the event. These points are then used in a weighted lottery system to influence which teams get to host residency blocks in the *next* season, creating a dynamic, multi-season strategic loop.
* **Sophisticated Concurrent Scheduling Engine:** The scheduler manages multiple concurrent "scheduling windows," allowing several multi-week residency blocks to happen at the same time, ensuring a balanced, geographically distributed, and realistically timed season.
* **Prioritized Regional Matchups:** The scheduling algorithm is now refined to increase the frequency of regional games, reinforcing the league's environmental goals.
* **Hierarchical Modular Architecture:** The project is structured with a clear, hierarchical dependency flow, where the scheduling logic is a child of the data module it depends on.
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
