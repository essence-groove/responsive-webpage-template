# MyAPMWProject/money_and_players/CMakeLists.txt



# 2. Define money_and_players_lib as a standard library, compiling the new .cpp file.
add_library(money_and_players_lib league_scheduler_2.cpp)

# 3. Expose the current directory for its own headers (player_data.h, team_data.h, etc.)
target_include_directories(money_and_players_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

