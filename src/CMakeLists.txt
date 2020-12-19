project(src)

set(HEADER_FILES
        lib/includes/single_linked_list.h
        )

set(SOURCE_FILES
        lib/single_linked_list.c
        )

add_library(src STATIC ${SOURCE_FILES} ${HEADER_FILES})
#target_include_directories(src PUBLIC includes)
#set_target_properties(src PROPERTIES PUBLIC_HEADER )
#set_target_properties(src PROPERTIES SOVERSION 1)

add_subdirectory(lib)
add_executable(main main.c)
target_link_libraries(main single_linked_list)