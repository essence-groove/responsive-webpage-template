# MyAPMWProject/money_and_players/scheduling/CMakeLists.txt

# Create a standard library named 'scheduling_lib' from its source file.
# We use league_scheduler_2.cpp to be consistent with the class name LeagueScheduler2.
add_library(scheduling_lib league_scheduler_2.cpp)

# Expose the current directory as a public include path for this library's
# header file (league_scheduler_2.h). This allows the parent module and the
# main executable to find it.
target_include_directories(scheduling_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
