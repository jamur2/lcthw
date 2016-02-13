#include <lcthw/list.h>
#include "dbg.h"
#include <stdio.h>
#include <lcthw/list_algos.h>

void List_print(List* list,  char* format)
{
    LIST_FOREACH(list, first, next, cur) {
        printf(format, cur->value);
    }
    printf("\n");
}

int ListNode_swap(ListNode* a, ListNode *b)
{
    void *tmp = a->value;
    a->value = b->value;
    b->value = tmp;

    return 0;
}

int List_bubble_sort(List * list, List_compare cmp)
{
    int sorted = 1;
    do {
        sorted = 1;
        LIST_FOREACH(list, first, next, cur) {
            if (cur->next != NULL && cmp(cur->value, cur->next->value) > 0) {
                    ListNode_swap(cur, cur->next);
                    sorted = 0;
            }
        }
    } while (!sorted);
    return 0;
}

List *List_merge(List *a, List *b, List_compare cmp)
{
    List *combined = List_create();
    while (List_count(a) > 0 || List_count(b) > 0) {
        if (List_count(a) == 0) {
            List_push(combined, List_shift(b));
        } else if (List_count(b) == 0) {
            List_push(combined, List_shift(a));
        } else {
            if (cmp(List_first(a), List_first(b)) < 0) {
                List_push(combined, List_shift(a));
            } else {
                List_push(combined, List_shift(b));
            }
        }
    }
    List_destroy(a);
    List_destroy(b);
    return combined;
}

List *List_merge_sort(List * list, List_compare cmp)
{
    int size = List_count(list);
    if (size <= 1) {
        return list;
    }
    int split = size / 2;

    List *left = List_create();
    List *right = List_create();
    int i = 0;
    LIST_FOREACH(list, first, next, cur) {
        if (i < split) {
            List_push(left, cur->value);
        } else {
            List_push(right, cur->value);
        }
        i++;
    }
    List *sorted_left = List_merge_sort(left, cmp);
    List *sorted_right = List_merge_sort(right, cmp);
    if(sorted_left != left) {
        List_destroy(left);
    }
    if(sorted_right != right) {
        List_destroy(right);
    }

    return List_merge(sorted_left, sorted_right, cmp);
}
