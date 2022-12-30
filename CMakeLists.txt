cmake_minimum_required(VERSION 3.23)
project(ext2fs_check)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} main.cpp options_parser/options_parser.cpp options_parser/options_parser.h
        run_check/run_check.cpp run_check/run_check.h check_super/check_super.cpp check_super/check_super.h run_check/file_entry.h check_group/check_group.cpp check_group/check_group.h
        iterate_fs/iterate_filesystem_tree.cpp iterate_fs/iterate_filesystem_tree.h)

target_include_directories(${PROJECT_NAME} PRIVATE options_parser)

find_package(Boost 1.71.0 COMPONENTS program_options system REQUIRED)
target_include_directories(${PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} Boost::program_options Boost::system)

INSTALL(PROGRAMS
        $<TARGET_FILE:${PROJECT_NAME}>	# ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}
        DESTINATION bin)

