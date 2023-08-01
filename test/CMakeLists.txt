include_directories(SYSTEM
    ${gtest_SOURCE_DIR}
    ${gtest_SOURCE_DIR}/include)

include(GoogleTest)

file(GLOB_RECURSE test_cases *.cc)
foreach(case_file ${test_cases})
    get_filename_component(case_name ${case_file} NAME_WE)
    set(case_name test_${case_name})
    add_executable(${case_name} ${case_file})
    target_link_libraries(${case_name} ${PROJECT_NAME}
                          ${LINK_LIBS} gtest_main pthread)
    include_directories(${case_name} ${PROJECT_SOURCE_DIR}/test)
    # Would add whole file as a single test case.
    #add_test(NAME ${case_name}
    #         COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test/${case_name}
    #         WORKING_DIRECTORY
    #         ${PROJECT_BINARY_DIR})
    # Better: add each test case in the file as a separate test.
    gtest_discover_tests(${case_name})
endforeach()