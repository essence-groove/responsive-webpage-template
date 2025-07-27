# MyAPMWProject/money_and_players/CMakeLists.txt

# v3.8.1: Simplified architecture with a single library.
# Create a single library from all source files in this directory.
add_library(money_and_players_lib
    league_scheduler_2.cpp
    money_and_players.cpp
    environmental_agent.cpp

)

# Expose the current directory so that any target linking against this library
# (like the main executable) can find all the header files within it.
target_include_directories(money_and_players_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
