cmake_minimum_required(VERSION 3.24)
project(ext2fs_check)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} main.cpp options_parser/options_parser.cpp options_parser/options_parser.h)

target_include_directories(${PROJECT_NAME} PRIVATE options_parser)

find_package(Boost 1.71.0 COMPONENTS program_options system REQUIRED)
target_include_directories(${PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} Boost::program_options Boost::system)

