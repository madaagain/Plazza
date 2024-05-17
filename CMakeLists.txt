cmake_minimum_required(VERSION 3.17)
project(plazza)

set(CMAKE_CXX_STANDARD 20)

add_compile_options(-Wall -Wextra -Werror)

set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES
        ${PROJECT_SOURCE_DIR}/plazza)

add_executable(plazza
        src/main.cpp
        src/threading_utils/Pthreadmutex.cpp
        src/parsing/Parser.cpp
        src/plazza/Kitchen.cpp
        src/parsing/programLoop.cpp
        src/parsing/LoopParser.cpp)

target_include_directories(plazza PUBLIC
        include)

add_custom_command(TARGET plazza POST_BUILD
COMMAND cp plazza ${PROJECT_SOURCE_DIR})
