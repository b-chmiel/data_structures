#include <stdio.h>
#include <malloc.h>
#include "single_linked_list.h"

int main()
{
        node *head = NULL;

        head = insert(2, head);
        head = insert(3, head);
        head = insert(4, head);
        head = insert(5, head);
        head = insert(6, head);
        head = insert(7, head);
        head = insert(8, head);
        head = insert(9, head);
        print(head);
        freeList(head);
        print(head);
        //printf("%d ", head->next->data);
        //printf("%d", head->next->next->data);
        //freeList(head);
        //print(head);
        return 0;
}
