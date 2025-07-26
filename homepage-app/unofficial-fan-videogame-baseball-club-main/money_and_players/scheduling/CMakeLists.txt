# MyAPMWProject/money_and_players/scheduling/CMakeLists.txt

# Create a standard library named 'scheduling_lib' from its source file.
add_library(scheduling_lib league_scheduler_2.cpp)

# Expose the current directory as a public include path for this library's
# header file (league_scheduler_2.h).
target_include_directories(scheduling_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# THE FIX: Explicitly add the parent directory ('money_and_players') to this
# library's private include paths. This tells the compiler where to find
# the data headers (game_data.h, team_data.h, etc.) that are included
# with a relative path like "../game_data.h".
target_include_directories(scheduling_lib PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/.."
)
