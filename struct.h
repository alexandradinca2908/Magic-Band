/* DINCĂ Alexandra-Cristina - 311CD */

typedef struct ListNode {
    char elem;
    struct ListNode *next;
    struct ListNode *prev;
} ListNode;

typedef struct List {
    ListNode *sentinel;
    ListNode *finger;
} List;

typedef struct StackNode {
    struct ListNode *position;
    struct StackNode *next;
    struct StackNode *prev;
} StackNode;

typedef struct Stack {
    StackNode *sentinel;
    StackNode *finger;
} Stack;

typedef struct QueueNode {
    char *command;
    struct QueueNode *next;
    struct QueueNode *prev;
} QueueNode;

typedef struct Queue {
    QueueNode *sentinel;
    QueueNode *finger;
} Queue;
