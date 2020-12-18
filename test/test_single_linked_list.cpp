//
// Created by incvis on 18.12.2020.
//

#include "gtest/gtest.h"

extern "C" {
#include <single_linked_list.h>
#include <limits.h>
}

TEST(Adding, Add)
{
        struct node *head = nullptr;
        int list_size = 5;

        for (int i = 0; i < list_size; i++)
                add(&head, i);

        for (int i = 0; i < list_size; i++)
                EXPECT_EQ(get_at(i, head), i);

        delete_list(&head);
}

TEST(Adding, AddMany)
{
        struct node *head = NULL;
        int list_size = 5;

        add_many(&head, list_size, 0, 1, 2, 3, 4);

        for (int i = 0; i < list_size; i++)
                EXPECT_EQ(get_at(i, head), i);

        delete_list(&head);
}

TEST(Adding, SequentialAddAt)
{
        struct node *head = NULL;
        int list_size = 7;
        int items[] = {1, 3, 2, 4, 5, 22, -23};

        for (int i = 0; i < list_size; i++)
                add_at(i, items[i], &head);

        for (int i = 0; i < list_size; i++)
                EXPECT_EQ(get_at(i, head), items[i]);

        delete_list(&head);
}

TEST(Adding, RandomAdd)
{
        struct node *head = nullptr;
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

TEST(Splitting, SplitIntoTwoEven)
{
        struct node *head = nullptr;
        struct node *first = nullptr;
        struct node *second = nullptr;
        int list_size = 10;

        for (int i = 0; i < list_size; i++)
                add(&head, i);

        split_into_two(head, &first, &second);

        int list1[] = {0, 1, 2, 3, 4};
        int list2[] = {5, 6, 7, 8, 9};

        for (int i = 0; i < list_size / 2; i++) {
                EXPECT_EQ(get_at(i, first), list1[i]);
                EXPECT_EQ(get_at(i, second), list2[i]);
        }

        delete_list(&first);
        delete_list(&second);
}

TEST(Splitting, SplitIntoTwoOdd)
{
        struct node *head = nullptr;
        struct node *first = nullptr;
        struct node *second = nullptr;
        int list_size = 9;

        for (int i = 0; i < list_size; i++)
                add(&head, i);

        split_into_two(head, &first, &second);

        int list1[] = {0, 1, 2, 3, 4};
        int list2[] = {5, 6, 7, 8};
        for (int i = 0; i < list_size / 2 - 1; i++) {
                EXPECT_EQ(get_at(i, first), list1[i]);
                EXPECT_EQ(get_at(i, second), list2[i]);
        }

        delete_list(&first);
        delete_list(&second);
}

TEST(Splitting, SplitOneElement)
{
        struct node *head = nullptr;
        struct node *first = nullptr;
        struct node *second = nullptr;
        int list_size = 1;

        for (int i = 0; i < list_size; i++)
                add(&head, i);

        split_into_two(head, &first, &second);

        EXPECT_EQ(get_at(0, head), 0);
        EXPECT_TRUE(second == nullptr);
        EXPECT_TRUE(first->next == nullptr);

        delete_list(&first);
        delete_list(&second);
}

//TEST(Sorting, MergeSortedEven)
//{
//        struct node *head = nullptr;
//        struct node *first = nullptr;
//        struct node *second = nullptr;
//
//        int list_size = 10;
//        int list1[] = {1, 23, 2, 4, 5};
//        int list2[] = {4, 2, 6, 1, -3};
//
//        for (int i = 0; i < list_size / 2; i++) {
//                add(&first, list1[i]);
//                add(&second, list2[i]);
//        }
//
//        merge_sorted(&head, first, second, nullptr);
//        print_list(head);
//        int result[] = {1, 4, 2, 6, 1, -3, 23, 2, 4, 5};
//
//        for (int i = 0; i < list_size; i++)
//                EXPECT_EQ(get_at(i, head), result[i]);
//
//        delete_list(&head);
//}

TEST(GetElement, GetAtFailCases)
{
        struct node *head = nullptr;
        int list_size = 7;

        EXPECT_EQ(get_at(-1, head), INT_MIN);


        for (int i = 0; i < list_size; i++)
                add_at(i, i, &head);

        EXPECT_EQ(get_at(9, head), INT_MAX);

        delete_list(&head);
}

TEST(Deletion, DeleteByContent)
{
        struct node *head = nullptr;
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

TEST(Deletion, DeleteByIndex)
{
        struct node *head = nullptr;
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

TEST(Deletion, DeleteList)
{
        struct node *head = nullptr;
        int list_size = 10;

        for (int i = 0; i < list_size; i++)
                add_at(i, i, &head);

        delete_list(&head);

        EXPECT_EQ(get_at(0, head), INT_MAX);
        EXPECT_TRUE(head == nullptr);
}