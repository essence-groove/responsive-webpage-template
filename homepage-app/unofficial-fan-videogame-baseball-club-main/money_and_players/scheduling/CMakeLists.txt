# MyAPMWProject/money_and_players/scheduling/CMakeLists.txt

# Create a standard library named 'scheduling_lib' from its source file.
add_library(scheduling_lib league_scheduler_2.cpp)

# Expose the current directory as a public include path for this library's
# header file (league_scheduler_2.h).
target_include_directories(scheduling_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# FIX v3.8.0: Explicitly link against the data library from the parent module.
# Using PUBLIC is crucial here. It ensures that the include directories
# from 'money_and_players_data' are passed to this library and any other
# target that uses it (like the main executable).
target_link_libraries(scheduling_lib PUBLIC money_and_players_data)
