#include <stdio.h>
#include "src/single_linked_list.h"


int main()
{
        node_t *head = NULL;

        for (int i = 0; i < 10; i++) {
                add_at(i, i, &head);
        }
        add_at(2, 10, &head);
        print_list(head);
        delete_by_content(10, &head);
        print_list(head);
        delete_by_content(0, &head);
        print_list(head);
        delete_by_content(9, &head);
        print_list(head);
        delete_by_content(1, &head);
        print_list(head);
        delete_list(&head);
        print_list(head);

        printf("Delete by index\n");
        for (int i = 0; i < 10; i++) {
                add_at(i, i, &head);
        }
        print_list(head);
        for (int i = 9; i >= 0; i--) {
                delete_by_index(i, &head);
        }
        print_list(head);

        printf("Get by index\n");
        for (int i = 0; i < 10; i++) {
                add_at(i, i, &head);
        }
        print_list(head);
        printf("first item: %d\n", get_at(0, head));
        printf("at index 4: %d\n", get_at(4, head));
        printf("last item: %d\n", get_at(9, head));
        print_list(head);
        return 0;
}
