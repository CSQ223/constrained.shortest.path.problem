cmake_minimum_required(VERSION 3.0)

project(
    example
    VERSION 1.0.0
    DESCRIPTION "example"
)

link_libraries(fmt::fmt-header-only)
link_libraries(network)

add_exec()

message("[PROJECT_SOURCE_DIR]: " ${PROJECT_SOURCE_DIR})
