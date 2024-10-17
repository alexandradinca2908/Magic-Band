/* DINCĂ Alexandra-Cristina - 311CD */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "struct.h"
#include "create.h"
#include "update.h"
#include "query.h"

//  ALLOCING SPACE FOR A LIST, STACK, AND QUEUE AND THEIR RESPECTIVE NODES

ListNode* createNode (char elem) {
    ListNode *newNode = malloc(sizeof(ListNode));
    newNode->elem = elem;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

List* createList (void) {
    List *list = malloc(sizeof(List));
    list->sentinel = createNode(0);
    list->finger = NULL;
    return list;
}

StackNode* createStackNode (ListNode *position) {
    StackNode *newNode = malloc(sizeof(StackNode));
    newNode->position = position;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

Stack* createStack (void) {
    Stack *list = malloc(sizeof(Stack));
    list->sentinel = createStackNode(NULL);
    list->finger = NULL;
    return list;
}

QueueNode* createQueueNode (char *command) {
    QueueNode *newNode = malloc(sizeof(QueueNode));
    newNode->command = malloc(strlen(command) + 1);
    strcpy(newNode->command, command);
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

Queue* createQueue (void) {
    Queue *list = malloc(sizeof(Queue));
    list->sentinel = createQueueNode("0");
    list->finger = NULL;
    return list;
}