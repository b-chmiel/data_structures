//
// Created by incvis on 18.12.2020.
//

#include "gtest/gtest.h"

extern "C" {
#include <single_linked_list.h>
#include <limits.h>
}


TEST(SingleLinkedList, SequentialAdd)
{
        node_t *head = NULL;
        int list_size = 7;
        int items[] = {1, 3, 2, 4, 5, 22, -23};

        for (int i = 0; i < list_size; i++)
                add_at(i, items[i], &head);

        for (int i = 0; i < list_size; i++)
                EXPECT_EQ(get_at(i, head), items[i]);

        delete_list(&head);
}

TEST(SingleLinkedList, RandomAdd)
{
        node_t *head = NULL;
        int list_size = 7;

        add_at(0, 1, &head);
        add_at(5, 2, &head);
        add_at(3, 3, &head);
        add_at(6, 4, &head);
        add_at(2, 5, &head);
        add_at(2, 6, &head);
        add_at(1, 7, &head);

        int result[] = {1, 7, 2, 6, 5, 3, 4};
        for (int i = 0; i < list_size; i++)
                EXPECT_EQ(get_at(i, head), result[i]);

        delete_list(&head);
}

TEST(SingleLinkedList, GetAtFailCases)
{
        node_t *head = NULL;
        int list_size = 7;

        EXPECT_EQ(get_at(-1, head), INT_MIN);


        for (int i = 0; i < list_size; i++)
                add_at(i, i, &head);

        EXPECT_EQ(get_at(9, head), INT_MAX);

        delete_list(&head);
}

TEST(SingleLinkedList, DeleteByContent)
{
        node_t *head = NULL;
        int list_size = 10;

        for (int i = 0; i < list_size; i++)
                add_at(i, i, &head);

        EXPECT_TRUE(delete_by_content(0, &head));
        EXPECT_TRUE(delete_by_content(4, &head));
        EXPECT_TRUE(delete_by_content(9, &head));

        EXPECT_FALSE(delete_by_content(112, &head));

        int result[] = {1, 2, 3, 5, 6, 7, 8};

        for (int i = 0; i < list_size - 3; i++)
                EXPECT_EQ(get_at(i, head), result[i]);

        delete_list(&head);
}

TEST(SingleLinkedList, DeleteByIndex)
{
        node_t *head = NULL;
        int list_size = 10;

        for (int i = 0; i < list_size; i++)
                add_at(i, i, &head);

        EXPECT_TRUE(delete_by_index(0, &head));
        EXPECT_TRUE(delete_by_index(4, &head));
        EXPECT_TRUE(delete_by_index(7, &head));

        EXPECT_FALSE(delete_by_index(112, &head));

        int result[] = {1, 2, 3, 4, 6, 7, 8};

        for (int i = 0; i < list_size - 3; i++)
                EXPECT_EQ(get_at(i, head), result[i]);

        delete_list(&head);
}

TEST(SingleLinkedList, DeleteList)
{
        node_t *head = NULL;
        int list_size = 10;

        for (int i = 0; i < list_size; i++)
                add_at(i, i, &head);

        delete_list(&head);

        EXPECT_EQ(get_at(0, head), INT_MAX);
        EXPECT_TRUE(head == NULL);
}
