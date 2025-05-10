#include <stdlib.h>
#include "list.h"

List *list_create() {
    List *list = malloc(sizeof(List));
    list->head = NULL;
    list->current = NULL;
    return list;
}

void list_push_back(List *list, void *data) {
    Node *new_node = malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    if (!list->head) {
        list->head = new_node;
    } else {
        Node *temp = list->head;
        while (temp->next) temp = temp->next;
        temp->next = new_node;
    }
}

void *list_first(List *list) {
    if (!list->head) return NULL;
    list->current = list->head;
    return list->current->data;
}

void *list_next(List *list) {
    if (!list->current || !list->current->next) return NULL;
    list->current = list->current->next;
    return list->current->data;
}