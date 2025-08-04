# APMW Baseball Simulator (unofficial-fan-videogame-baseball-club)

This is an unofficial fan-made baseball video game, serving as the **C++ 3.9.2 core** for the Ayurveda Project Management World (APMW) project. It is a text-based simulation of a baseball league, built with a focus on modularity, agent-driven-logic, and deep lore integration.

## Generated Schedule

📄 [**View the Latest Generated Schedule (v3.9)**](schedule_report_v3.9.md)

*This report is automatically generated and updated by our CI/CD workflow on every push to the `main` branch.*

## Features (v3.9.2)

* **Advanced Apex Residency Mechanics:** A strategic layer built around the season-ending Apex event.
    * **Dynamic "Earned Participation":** Players are selected for the Apex event based on simulated performance, ensuring a different lineup each season.
    * **Strategic "Capture the Flag" System:** Teams earn "Apex Points" from the event, which are used in a weighted lottery to influence future hosting opportunities.
* **Player Autonomy in Trades:** A new `TradeAgent` respects player preferences, allowing them to veto trades to new regions or unions based on data in their profile.
* **Sophisticated Financials:** The data model is expanded with new financial levers, and a `FinancialAgent` calculates team payrolls, laying the groundwork for a deep economic simulation.
* **Foundation for Offseason:** The project now includes a `PersistenceAgent` and a `LeagueState` structure, establishing the core architecture for a true, multi-season offseason simulation with player progression and drafts.
* **Sophisticated Concurrent Scheduling Engine:** The scheduler manages multiple concurrent "scheduling windows," allowing several multi-week residency blocks to happen at the same time.
* **Simplified Modular Architecture:** The project is organized into a single, clean module that contains all data structures and agent logic, managed by a modern CMake (C++23) build system.

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
