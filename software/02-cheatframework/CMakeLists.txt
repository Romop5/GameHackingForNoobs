project(cheatframework)

add_library(cheatlib cheatlib.cpp) 

add_executable(mafia-cheat mafia-cheat.cpp)
target_link_libraries(mafia-cheat cheatlib)
