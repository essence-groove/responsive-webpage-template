# MyAPMWProject/money_and_players/CMakeLists.txt

# 1. Define an INTERFACE library specifically for the data headers in this directory.
#    This makes its include paths available to child modules.
add_library(money_and_players_data INTERFACE)
target_include_directories(money_and_players_data INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# 2. Now, process the nested scheduling module. It will be able to link against
#    the 'money_and_players_data' library we just defined.
add_subdirectory(scheduling)

# 3. Create the main library for this module. This bundles the data headers and the
#    compiled scheduling logic together for the main executable.
add_library(money_and_players_lib INTERFACE)
target_link_libraries(money_and_players_lib INTERFACE
    money_and_players_data
    scheduling_lib
)
