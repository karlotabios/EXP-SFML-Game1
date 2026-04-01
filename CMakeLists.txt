cmake_minimum_required(VERSION 3.28)
project(EXP-SFML-Game1 LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)


file(GLOB SOURCE RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

foreach(SRC_FILE ${SOURCES})
    get_filename_component(FILE_NAME ${SRC_FILE} NAME_WE)
    target_link_libraries(${FILE_NAME} PRIVATE SFML::Graphics)
endforeach()

add_executable(main src/main.cpp ${SOURCES})
target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE SFML::Graphics)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT main)