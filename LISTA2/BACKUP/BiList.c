#include "headers.h"
#include "structs.h"

BiList *List_create()
{
    return calloc(1, sizeof(BiList));
}

void List_destroy(BiList *list)
{
    LIST_FOREACH(list, first, next, cur) {
        if(cur->prev) {
            free(cur->prev);
        }
    }

    free(list->last);
    free(list);
}


void List_clear(BiList *list)
{
    LIST_FOREACH(list, first, next, cur) {
        free(cur->val);
    }
}


void List_clear_destroy(BiList *list)
{
    List_clear(list);
    List_destroy(list);
}


void List_push(BiList *list, void *val)
{
    LNode *node = calloc(1, sizeof(LNode));

    node->val = val;

    if(list->last == NULL) {
        list->first = node;
        list->last = node;
    } else {
        list->last->next = node;
        node->prev = list->last;
        list->last = node;
    }

    list->count++;

error:
    return;
}

void *List_pop(BiList *list)
{
    LNode *node = list->last;
    return node != NULL ? List_remove(list, node) : NULL;
}

void List_unshift(BiList *list, void *val)
{
    LNode *node = calloc(1, sizeof(LNode));

    node->val = val;

    if(list->first == NULL) {
        list->first = node;
        list->last = node;
    } else {
        node->next = list->first;
        list->first->prev = node;
        list->first = node;
    }

    list->count++;

error:
    return;
}

void *List_shift(BiList *list)
{
    LNode *node = list->first;
    return node != NULL ? List_remove(list, node) : NULL;
}

void *List_remove(BiList *list, LNode *node)
{
    void *result = NULL;


    if(node == list->first && node == list->last) {
        list->first = NULL;
        list->last = NULL;
    } else if(node == list->first) {
        list->first = node->next;
        list->first->prev = NULL;
    } else if (node == list->last) {
        list->last = node->prev;
        list->last->next = NULL;
    } else {
        LNode *after = node->next;
        LNode *before = node->prev;
        after->prev = before;
        before->next = after;
    }

    list->count--;
    result = node->val;
    free(node);

error:
    return result;
}
