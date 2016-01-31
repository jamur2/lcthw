#include <lcthw/list.h>
#include <lcthw/dbg.h>

List *List_create()
{
    return calloc(1, sizeof(List));
}

void List_destroy(List * list)
{
    check(list != NULL, "list must not be NULL");
    LIST_FOREACH(list, first, next, cur) {
        if (cur->prev) {
            free(cur->prev);
        }
    }

    free(list->last);
    free(list);

error:
    return;
}

int List_validate(List * list)
{
    check(list != NULL, "list must not be NULL");
    check(list->count >= 0, "Count must not be negative");
    if(list->count == 0) {
        check(list->first != NULL, "Can't have count of 0 with non-null first");
    }

error:
    return 1;
}

void List_clear(List * list)
{
    check(List_validate(list), "Invalid list");
    List_validate(list);
    check(list != NULL, "list must not be NULL");
    LIST_FOREACH(list, first, next, cur) {
        free(cur->value);
    }
    check(List_validate(list), "Invalid list");
error:
    return;
}

void List_clear_destroy(List * list)
{
    check(List_validate(list), "Invalid list");
    LIST_FOREACH(list, first, next, cur) {
        if (cur->value) {
            free(cur->value);
        }
        if (cur->prev) {
            free(cur->prev);
        }
    }

    free(list->last);
    free(list);

error:
    return;
}

void List_push(List * list, void *value)
{
    check(List_validate(list), "Invalid list");
    check(list != NULL, "list must not be NULL");
    ListNode *node = calloc(1, sizeof(ListNode));
    check_mem(node);

    node->value = value;

    if(list->last == NULL) {
        list->first = node;
        list->last = node;
    } else {
        list->last->next = node;
        node->prev = list->last;
        list->last = node;
    }

    list->count++;
    check(List_validate(list), "Invalid list");

error:
    return;
}

void *List_pop(List * list)
{
    check(List_validate(list), "Invalid list");
    ListNode *node = list->last;
    check(List_validate(list), "Invalid list");
    return node != NULL ? List_remove(list, node) : NULL;

error:
    return NULL;
}

void List_unshift(List * list, void *value)
{
    check(List_validate(list), "Invalid list");
    ListNode *node = calloc(1, sizeof(ListNode));
    check_mem(node);

    node->value = value;

    if (list->first == NULL) {
        list->first = node;
        list->last = node;
    } else {
        node->next = list->first;
        list->first->prev = node;
        list->first = node;
    }

    list->count++;
    check(List_validate(list), "Invalid list");

error:
    return;
}

void *List_shift(List * list)
{
    check(List_validate(list), "Invalid list");
    ListNode *node = list->first;
    return node != NULL ? List_remove(list, node) : NULL;

error:
    return NULL;
}

void *List_remove(List * list, ListNode * node)
{
    void *result = NULL;
    check(List_validate(list), "Invalid list");
    check(list->first && list->last, "List is empty.");
    check(node, "node can't be NULL");

    if(node == list->first && node == list->last) {
        list->first = NULL;
        list->last = NULL;
    } else if (node == list->first) {
        list->first = node->next;
        check(list->first != NULL,
                "Invalid list, somehow got a first that is NULL.");
        list->first->prev = NULL;
    } else if (node == list->last) {
        list->last = node->prev;
        check(list->last != NULL,
                "Invalid list, somehow got a next that is NULL.");
        list->last->next = NULL;
    } else {
        ListNode *after = node->next;
        ListNode *before = node->prev;
        after->prev = before;
        before->next = after;
    }

    list->count--;
    result = node->value;
    free(node);
    check(List_validate(list), "Invalid list");

error:
    return result;
}
