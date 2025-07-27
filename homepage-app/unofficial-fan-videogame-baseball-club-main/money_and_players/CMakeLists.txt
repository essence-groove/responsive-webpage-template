# MyAPMWProject/money_and_players/CMakeLists.txt

# v3.9.0: Simplified architecture with a single library.
# Add all .cpp files in this directory to the library definition.
add_library(money_and_players_lib
    league_scheduler_2.cpp
    money_and_players.cpp
    environmental_agent.cpp
    days.cpp

)

target_include_directories(money_and_players_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
