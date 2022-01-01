cmake_minimum_required(VERSION 3.0)

project(
    network
    VERSION 1.0.0
    DESCRIPTION "network"
)

link_libraries(fmt::fmt-header-only)
link_libraries(nlohmann_json::nlohmann_json)

add_lib(SHARED)

message("[PROJECT_SOURCE_DIR]: " ${PROJECT_SOURCE_DIR})
