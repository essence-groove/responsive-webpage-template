# MyAPMWProject/money_and_players/scheduling/CMakeLists.txt

# Create a standard library named 'scheduling_lib' from its source file.
add_library(scheduling_lib league_scheduler_2.cpp)

# Expose the current directory as a public include path for this library's
# header file (league_scheduler_2.h).
target_include_directories(scheduling_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# DIRECT FIX: Explicitly add the absolute path to the parent 'money_and_players' directory.
# This tells the compiler exactly where to find game_data.h, team_data.h, etc.,
# bypassing any issues with transitive dependency propagation.
target_include_directories(scheduling_lib PRIVATE
    ${CMAKE_SOURCE_DIR}/money_and_players
)
