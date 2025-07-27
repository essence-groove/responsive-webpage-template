add_library(money_and_players_lib
    league_scheduler_2.cpp
    environmental_agent.cpp
    days.cpp # <-- Add your new source file here
)

target_include_directories(money_and_players_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
