# Create a standard library named 'scheduling_lib' from its source file.
# This assumes league_scheduler.cpp is directly in the 'scheduling/' directory.
add_library(scheduling_lib league_scheduler.cpp)

# Expose the current directory as a public include path for its headers (e.g., league_scheduler_2.h).
target_include_directories(scheduling_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# This module depends on the money_and_players module because
# LeagueScheduler2 operates on Team and Game objects (which contain Player objects).
target_link_libraries(scheduling_lib PRIVATE money_and_players_lib)
