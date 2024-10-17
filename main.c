/* DINCĂ Alexandra-Cristina - 311CD */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "struct.h"
#include "create.h"
#include "update.h"
#include "query.h"

int main () {
    ListNode *newNode = createNode('#');
    List *list = createList();  //  LIST
    list->sentinel->next = newNode;
    list->finger = newNode;
    newNode->prev = list->sentinel;

    Stack *undo = createStack();    //  UNDO STACK
    Stack *redo = createStack();    //  REDO STACK
    Queue *execute = createQueue();   //  EXECUTE QUEUE

    QueueNode *iter = execute->sentinel; //  COMMAND ITERATOR

    FILE *in, *out;     //  CREATING FILES
    in = fopen("tema1.in", "rt");
    out = fopen("tema1.out", "wt");
    if (in == NULL || out == NULL) {
        return -1;
    }
    
    char command[30], cmdHolder[30];   //  STORES COMMANDS FROM FILE, STORES COMMANDS FROM QUEUE
    ListNode *prevFinger = NULL;    //  STORES THE PREVIOUS FINGER LOCATION; IS USED IN UNDO/REDO

    int numOfCmds = 0;  //  NUMBER OF COMMANDS; EXTRACTED FROM THE FILE AS A STRING, THEN CONVERTED TO INT
    int index = 0;

    fgets(command, sizeof(command), in);    //  EXTRACTING THE NUMBER OF COMMANDS
    while (command[index] != '\n') {
        index++;
    }
    index--;
    int powOfTen = 1;
    while (index >= 0) {    //  CONVERTING EACH CHAR INTO INT
        int charToInt = command[index] - '0';
        numOfCmds += charToInt * powOfTen;
        index--;
        powOfTen *= 10;
    }

    while (numOfCmds > 0 && fgets(command, sizeof(command), in) != NULL) {
        if (strstr(command, "EXECUTE")) {   //  EXECUTES COMANDS
            if (execute->finger != NULL) {
                iter = iter->next;
                
                if (strstr(iter->command, "MOVE")) {    //  ALL 4 MOVE COMMANDS
                    prevFinger = list->finger;
                    strcpy(cmdHolder, iter->command);
                    if (strstr(cmdHolder, "CHAR")) {
                        moveToChar(list, cmdHolder, out);
                    } else {
                        moveFinger(list, cmdHolder);
                    }
                    if (undo->finger == NULL) {
                        undo->sentinel->next = createStackNode(prevFinger);
                        undo->sentinel->next->prev = undo->sentinel;
                        undo->finger = undo->sentinel->next;
                    } else if (prevFinger != list->finger){
                        undo->finger->next = createStackNode(prevFinger);
                        undo->finger->next->prev = undo->finger;
                        undo->finger = undo->finger->next;
                    }        

                } else if (strstr(iter->command, "INSERT")) {   //  INSERT COMMAND
                    strcpy(cmdHolder, iter->command);
                    insertChar(list, cmdHolder, out);

                } else if (strstr(iter->command, "WRITE")) {    //  WRITE COMMAND
                    strcpy(cmdHolder, iter->command);
                    writeChar(list, cmdHolder);

                    //  CLEARING THE STACKS
                    if (undo->sentinel->next != NULL) {
                        while (undo->finger != undo->sentinel) {
                            undo->finger = undo->finger->prev;
                            free(undo->finger->next);
                        }
                    }
                    if (redo->sentinel->next != NULL) {
                        while (redo->finger != redo->sentinel) {
                            redo->finger = redo->finger->prev;
                            free(redo->finger->next);
                        }
                    }

                }   
            }

        } else if (strstr(command, "SHOW")) {     //  SHOW COMMANDS
            strcpy(cmdHolder, command);
            if (strstr(cmdHolder, "CURRENT")) {
                showCurrent(list, out);
            } else {
                showAll(list, out);
            }

        } else if (strstr(command, "UNDO")) {   //  UNDO
            prevFinger = list->finger;
            if (undo->sentinel != undo->finger) {
                if (redo->finger == NULL) {
                    redo->sentinel->next = createStackNode(prevFinger);
                    redo->sentinel->next->prev = redo->sentinel;
                    redo->finger = redo->sentinel->next;
                } else {
                    redo->finger->next = createStackNode(prevFinger);
                    redo->finger->next->prev = redo->finger;
                    redo->finger = redo->finger->next;
                }
                list->finger = undo->finger->position;
                undo->finger = undo->finger->prev;
                free(undo->finger->next);
            }

        } else if (strstr(command, "REDO")) {   //  REDO
            prevFinger = list->finger;
            if (redo->sentinel != redo->finger) {
                if (undo->finger == NULL) {
                    undo->sentinel->next = createStackNode(prevFinger);
                    undo->sentinel->next->prev = undo->sentinel;
                    undo->finger = undo->sentinel->next;
                } else {
                    undo->finger->next = createStackNode(prevFinger);
                    undo->finger->next->prev = undo->finger;
                    undo->finger = undo->finger->next;
                }
                list->finger = redo->finger->position;
                redo->finger = redo->finger->prev;
                free(redo->finger->next);
            }

        } else {
            if (execute->finger == NULL) {      //  ADDS COMMAND TO UNDO STACK
                execute->sentinel->next = createQueueNode(command);
                execute->sentinel->next->prev = execute->sentinel;
                execute->finger = execute->sentinel->next;
            } else {
                execute->finger->next = createQueueNode(command);
                execute->finger->next->prev = execute->finger;
                execute->finger = execute->finger->next;
            }            
        }
        numOfCmds--;
    }

    // CLOSING FILES
    fclose(in);
    fclose(out);

    //  DEALLOCATING MEMORY:

    //  LIST
    if (list->sentinel->next != NULL) {
        while (list->finger->next != NULL) {
            list->finger = list->finger->next;
        }
        while (list->finger != list->sentinel) {
            list->finger = list->finger->prev;
            free(list->finger->next);
        }
    }    
    free(list->sentinel);
    free(list);

    //  UNDO STACK
    if (undo->sentinel->next != NULL) {
        while (undo->finger != undo->sentinel) {
            undo->finger = undo->finger->prev;
            free(undo->finger->next);
        }
    }
    free(undo->sentinel);
    free(undo);

    //  REDO STACK
    if (redo->sentinel->next != NULL) {
        while (redo->finger != redo->sentinel) {
            redo->finger = redo->finger->prev;
            free(redo->finger->next);
        }
    }
    free(redo->sentinel);
    free(redo);

    //  EXECUTION QUEUE
    if (execute->sentinel->next != NULL) {
        while (execute->finger != execute->sentinel) {
            execute->finger = execute->finger->prev;
            free(execute->finger->next->command);
            free(execute->finger->next);
        }
    }
    free(execute->sentinel->command);
    free(execute->sentinel);
    free(execute);

    return 0;
}
