# MyAPMWProject/money_and_players/CMakeLists.txt

# 1. Process the nested scheduling module first. This creates the 'scheduling_lib' target.
add_subdirectory(scheduling)

# 2. Create the money_and_players_lib. It is no longer just an INTERFACE library
#    because it now logically contains the compiled scheduling logic.
add_library(money_and_players_lib)

# 3. Expose the current directory for its own headers (player_data.h, team_data.h, etc.)
target_include_directories(money_and_players_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# 4. Link the scheduling logic library into the money_and_players library.
#    Using PUBLIC ensures that any target linking against money_and_players_lib
#    (like the main executable) also gets the necessary include paths from scheduling_lib.
target_link_libraries(money_and_players_lib PUBLIC scheduling_lib)
