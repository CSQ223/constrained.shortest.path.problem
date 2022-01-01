project(
    tests
    DESCRIPTION "unit tests"
)

include_directories(include)

macro(doctest_add_test test_name test_file)
    add_executable(${test_name} ${test_file})

    enable_testing()

    add_test(
        NAME ${test_name}
        COMMAND $<TARGET_FILE:${test_name}> --success
    )
endmacro()

link_libraries(network)

doctest_add_test(test_network src/test_network.cc)
