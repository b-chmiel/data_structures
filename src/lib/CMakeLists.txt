add_library(single_linked_list single_linked_list.c)
target_include_directories(single_linked_list PUBLIC includes)
set_target_properties(single_linked_list PROPERTIES PUBLIC_HEADER includes/single_linked_list.h)
set_target_properties(single_linked_list PROPERTIES SOVERSION 1)

install(TARGETS single_linked_list
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        PUBLIC_HEADER DESTINATION include
        )
