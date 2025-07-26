# MyAPMWProject/money_and_players/CMakeLists.txt

# 1. Process the nested scheduling module first. This creates the 'scheduling_lib' target.
add_subdirectory(scheduling)

# 2. Create money_and_players_lib as an INTERFACE library. This allows it to
#    bundle usage requirements (include directories, linked libraries) without
#    needing its own source files to compile.
add_library(money_and_players_lib INTERFACE)

# 3. Expose the current directory for its own headers (player_data.h, team_data.h, etc.)
target_include_directories(money_and_players_lib INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# 4. Link the scheduling logic library into the money_and_players interface library.
#    This ensures that any target linking against money_and_players_lib (like the
#    main executable) also gets the properties and link dependency of scheduling_lib.
target_link_libraries(money_and_players_lib INTERFACE scheduling_lib)
