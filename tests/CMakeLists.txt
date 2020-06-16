list(APPEND _tests
        parser_test0
        parser_test1
        parser_test2
        parser_test3
        parser_test4
        parser_test5
        parser_test6
        parser_test7
        parser_test8
        parser_test9)

foreach(_test IN LISTS _tests)
                add_executable(${_test} ${_test}.c)

                target_include_directories(${_test}
                                PRIVATE
                                                ${GLIB2_INCLUDE_DIRS})

                target_link_libraries(${_test}
                                runner
                                ${GLIB2_LDFLAGS})
endforeach()

add_test(NAME test_'n'
        COMMAND $<TARGET_FILE:parser_test0>)

add_test(NAME test_'n+m'
        COMMAND $<TARGET_FILE:parser_test1>)

add_test(NAME test_'n+m*k'
        COMMAND $<TARGET_FILE:parser_test2>)

add_test(NAME test_'n*m+k+m'
        COMMAND $<TARGET_FILE:parser_test3>)

add_test(NAME test_'n*m+n*k'
        COMMAND $<TARGET_FILE:parser_test4>)

add_test(NAME test_'n*m+k*m+m*m*m+k'
        COMMAND $<TARGET_FILE:parser_test5>)

add_test(NAME test_'n*m+k*m+m+m*m+k*k+m+n'
        COMMAND $<TARGET_FILE:parser_test6>)

add_test(NAME test_fail_'n*mm'
        COMMAND $<TARGET_FILE:parser_test7>)
set_tests_properties(test_fail_'n*mm' PROPERTIES WILL_FAIL true)

add_test(NAME test_fail_'n++m'
        COMMAND $<TARGET_FILE:parser_test8>)
set_tests_properties(test_fail_'n++m' PROPERTIES WILL_FAIL true)

add_test(NAME test_fail_'n**'
        COMMAND $<TARGET_FILE:parser_test9>)
set_tests_properties(test_fail_'n**' PROPERTIES WILL_FAIL true)


enable_testing()


