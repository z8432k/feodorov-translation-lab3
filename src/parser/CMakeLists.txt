set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE  ON)

find_package(FLEX REQUIRED)

flex_target(Lexer lexer.l
        ${CMAKE_CURRENT_SOURCE_DIR}/lexer.c
        DEFINES_FILE ${CMAKE_CURRENT_LIST_DIR}/lexer.h)

add_library(lexer
        OBJECT
        ${FLEX_Lexer_OUTPUTS})
target_compile_options(lexer PRIVATE "-Wno-sign-compare" "-Wno-unused-function")
target_include_directories(lexer
        PRIVATE
        ${GLIB2_INCLUDE_DIRS})
target_link_libraries(lexer
        PUBLIC
        parser)

add_library(actions
        OBJECT
        actions.c)
target_include_directories(actions
        PUBLIC
        ${GLIB2_INCLUDE_DIRS})
target_compile_options(actions PRIVATE "-Wno-unused-parameter")

add_library(parser
        OBJECT
        parser.c)
target_link_libraries(parser
        PRIVATE
        actions)

