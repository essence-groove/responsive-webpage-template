# MyAPMWProject/money_and_players/CMakeLists.txt

# 1. Process the nested scheduling module first to create the 'scheduling_lib' target.
add_subdirectory(scheduling)

# 2. Define money_and_players_lib as a standard library, compiling the new .cpp file.
add_library(money_and_players_lib league_scheduler_2.cpp)

# 3. Expose the current directory for its own headers (player_data.h, team_data.h, etc.)
target_include_directories(money_and_players_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# 4. Link the compiled scheduling logic into this library.
#    Using PUBLIC ensures that the executable that links to this library
#    can also see the headers from scheduling_lib.
target_link_libraries(money_and_players_lib PUBLIC scheduling_lib)
