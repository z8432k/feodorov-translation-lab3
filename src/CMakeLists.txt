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
                $<TARGET_OBJECTS:parser>)
target_include_directories(common
        PUBLIC
                parser)

add_executable(programm
        programm.c)
target_include_directories(programm
        PRIVATE
                ${GLIB2_INCLUDE_DIRS})
target_link_libraries(programm
        PRIVATE
                runner
                ${GLIB2_LDFLAGS})
target_compile_options(programm PRIVATE "-Wno-unused-parameter")


add_subdirectory(parser)
