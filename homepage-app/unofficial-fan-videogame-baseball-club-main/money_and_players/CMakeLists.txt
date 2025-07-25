# MyAPMWProject/money_and_players/CMakeLists.txt
add_library(money_and_players_lib INTERFACE)

# Expose the current directory as an include path for anyone using this library.
# This allows #include "player_data.h" or "team_data.h" etc.
target_include_directories(money_and_players_lib
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)
