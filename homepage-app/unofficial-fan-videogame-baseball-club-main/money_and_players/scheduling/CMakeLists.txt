# MyAPMWProject/money_and_players/scheduling/CMakeLists.txt

# Create a standard library named 'scheduling_lib' from its source file.
add_library(scheduling_lib league_scheduler_2.cpp)

# Expose the current directory as a public include path for this library's
# header file (league_scheduler_2.h).
target_include_directories(scheduling_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Link against the data library from the parent module. The PRIVATE keyword
# is correct here, as the data headers are an internal implementation detail
# of the scheduling library. The INTERFACE properties of the data library
# ensure the include paths are correctly passed for compilation.
target_link_libraries(scheduling_lib PRIVATE money_and_players_data)
