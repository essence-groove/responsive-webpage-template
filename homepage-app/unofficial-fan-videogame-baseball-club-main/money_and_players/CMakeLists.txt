# MyAPMWProject/money_and_players/CMakeLists.txt

# 1. Define a variable holding the path to this directory's headers.
#    This makes the path available to child directories.
set(MONEY_AND_PLAYERS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)

# 2. Process the nested scheduling module. It can now access the variable we just defined.
add_subdirectory(scheduling)

# 3. Create an INTERFACE library to bundle everything for the main executable.
add_library(money_and_players_lib INTERFACE)

# 4. Add this module's own include directories to the interface.
target_include_directories(money_and_players_lib INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# 5. Link the compiled scheduling logic into the interface.
target_link_libraries(money_and_players_lib INTERFACE scheduling_lib)
