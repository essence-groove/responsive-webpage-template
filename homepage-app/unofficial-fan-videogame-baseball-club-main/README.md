<code language="markdown">
# APMW Baseball Simulator (unofficial-fan-videogame-baseball-club)

This is an unofficial fan-made baseball video game, serving as the **C++ 3.7.0 core** for the Ayurveda Project Management World (APMW) project. It is a text-based simulation of a baseball league's season schedule, built with a focus on modularity, agent-driven-logic, and deep lore integration.

## Generated Schedule

📄 [**View the Latest Generated Schedule (v3.7.0)**](schedule_report_v3.7.0.md)

*This report is automatically generated and updated by our CI/CD workflow on every push to the `main` branch.*

## Features (v3.7.0)

* **Modular C++ Core:** Built with a clean separation of concerns, separating data structures (like players, teams, and games) from the scheduling logic.

* **18-Team League Structure:** Simulates a full league with two unions (Atlantic and Pacific) and unique fictional regions, as defined by the project lore.

* **Advanced Scheduling Agent (`LeagueScheduler2`):**

  * **Extended Residency Blocks:** Generates complex, multi-week residency blocks where a host team stays home to play multiple visiting teams, reducing travel and enhancing narrative depth.

  * **"Regional Games":** Formally incorporates a new game type where two visiting teams from the same region play a neutral-site game, creating opportunities for local rivalries on the road.

  * **"Crossroads Games":** Manages neutral-site games between visiting teams from different regions, implementing the lore-specific "alternating first bat" rule for fairness.

* **Reduced Season Length:** Targets a \~94-102 game season to increase the significance of each game and align with the league's environmental and risk-management goals.

* **"Money and Players" Concept:** Includes detailed `Player` data structures with skill ratings, fatigue, and financial attributes (salary, market value), allowing for future player-centric simulation.

* **CMake Build System:** Uses a modern CMake configuration for robust and scalable builds.

## How to Build and Run

This project uses CMake. You will need a C++ compiler (like G++, Clang, or MSVC) and CMake installed.

1. **Clone the repository:**

   ```
   git clone https://github.com/your-username/unofficial-fan-videogame-baseball-club.git
   cd unofficial-fan-videogame-baseball-club
   
   ```

2. **Configure the project with CMake:**

   ```
   # This creates a 'build' directory and generates the build files inside it.
   cmake -S . -B build
   
   ```

3. **Compile the code:**

   ```
   # This runs the actual compilation process.
   cmake --build build
   
   ```

4. **Run the executable:**

   ```
   # The executable will be inside the 'build' directory.
   ./build/apmw_baseball_simulator
   
   ```

## License

This project is licensed under the GNU Affero General Public License v3.0. See the [LICENSE](LICENSE) file for details.
</code>
