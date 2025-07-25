# APMW Baseball Simulator (unofficial-fan-videogame-baseball-club)

This is an unofficial fan-made baseball video game, serving as the C++ 3.5.0 core for the Ayurveda Project Management World (APMW) project. It is a text-based simulation of a baseball league's season schedule, built with a focus on modularity, agent-driven logic, and deep lore integration.

## Features

* **Modular C++ Core:** Built with a clean separation of concerns, separating data structures (like players, teams, and games) from the scheduling logic.
* **18-Team League Structure:** Simulates a full league with two unions (Atlantic and Pacific) and unique fictional regions, as defined by the project lore.
* **"Money and Players" Concept:** Includes detailed `Player` data structures with skill ratings, fatigue, and financial attributes (salary, market value), allowing for player-centric simulation.
* **Advanced Scheduling Agent:** The `LeagueScheduler2` class acts as a "League Agent" to generate complex season schedules based on a "Residency Block" model.
* **"Crossroads Games" Logic:** Implements the lore-specific "alternating first bat" rule for games played between two visiting teams at a neutral site.
* **CMake Build System:** Uses a modern CMake configuration for robust and scalable builds.

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
