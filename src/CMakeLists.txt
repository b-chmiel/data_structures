project(src)

set(HEADER_FILES
        single_linked_list.h
        )

set(SOURCE_FILES
        single_linked_list.c
        )

add_library(src STATIC ${SOURCE_FILES} ${HEADER_FILES})
