set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE  ON)

add_library(runner
        OBJECT
                runner.c)
target_link_libraries(runner
        PUBLIC
                common)
target_include_directories(runner
        PUBLIC
                include)

add_library(common
        STATIC
                $<TARGET_OBJECTS:lexer>
                $<TARGET_OBJECTS:parser>
                $<TARGET_OBJECTS:module>)
target_include_directories(common
        INTERFACE
                parser
                ${GLIB2_INCLUDE_DIRS})
target_link_libraries(common
        INTERFACE
                ${GLIB2_LDFLAGS})

add_executable(programm
        programm.c)
target_link_libraries(programm
        PRIVATE
                runner)
target_compile_options(programm PRIVATE "-Wno-unused-parameter")


add_subdirectory(parser)
