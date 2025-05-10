#ifndef LIST_H
#define LIST_H

typedef struct Node {
    void *data;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
    Node *tail;
    Node *current;
} List;

List* list_create();
void list_push_back(List *list, void *data);
void* list_first(List *list);
void* list_next(List *list);

#endif