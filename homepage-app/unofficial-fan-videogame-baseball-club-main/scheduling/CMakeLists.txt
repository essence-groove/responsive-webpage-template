# Create a standard library named 'scheduling_lib' from its source file.
# For v3.8.0, this uses league_scheduler_2.cpp, which contains the LeagueScheduler2 class logic.
add_library(scheduling_lib league_scheduler_2.cpp)

# Expose the current directory as a public include path for its headers (e.g., league_scheduler_2.h).
target_include_directories(scheduling_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# This module depends on the money_and_players module because
# LeagueScheduler2 operates on Team and Game objects.
# FIX v3.8.0: Changed to PUBLIC to ensure transitive include directories are propagated correctly.
# This makes headers from money_and_players available to headers in scheduling.
target_link_libraries(scheduling_lib PUBLIC money_and_players_lib)
