/* DINCĂ Alexandra-Cristina - 311CD */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "struct.h"
#include "create.h"
#include "update.h"
#include "query.h"

void moveFinger (List *list, char *command) {
    if (strstr(command, "MOVE_LEFT")) {
        if (list->finger != list->sentinel->next) {     //  MOVES FINGER TO THE LEFT ONLY IF AN ELEMENT EXISTS
            list->finger = list->finger->prev; 
        }
    } else if (strstr(command, "MOVE_RIGHT")) {
        if (list->finger->next == NULL) {       //  CREATES NODE TO THE RIGHT IF THERE ISN'T ONE ALREADY
            list->finger->next = createNode('#');
            list->finger->next->prev = list->finger;
            list->finger = list->finger->next;
        } else {
            list->finger = list->finger->next;      //  MOVES FINGER
        }
    }
}

void moveToChar (List *list, char *command, FILE *out) {
    if (strstr(command, "MOVE_LEFT_CHAR")) {
        char *letter = strchr(command, ' ');    //  ARRAY CONSISTING OF A SPACE AND THE CHAR
        ListNode *temp = list->finger;
        while (list->finger != list->sentinel) {   //  LOOKS FOR THE CHAR  
            if (list->finger->elem == letter[1]) {
                return;
            }
            list->finger = list->finger->prev;
        }
        fprintf(out, "ERROR\n");    //  RETURNS AN ERROR MESSAGE IF CHAR ISN'T FOUND
        list->finger = temp;        //  FINGER KEEPS THE SAME POSITION
    } else if (strstr(command, "MOVE_RIGHT_CHAR")) {
        char *letter = strchr(command, ' ');
        while (list->finger->next != NULL) {
            if (list->finger->elem == letter[1]) {
                return;
            }
            list->finger = list->finger->next;
        }
        if (list->finger->elem == letter[1]) {
            return;
        }
        list->finger->next = createNode('#');   //  CREATES NEW NODE IF CHAR ISN'T FOUND
        list->finger->next->prev = list->finger;    //  FINGER POINTS TO THE NEW NODE 
        list->finger = list->finger->next;        
    }
}

void writeChar (List *list, char *command) {
    char *letter = strchr(command, ' ');
    list->finger->elem = letter[1];
}

void insertChar (List *list, char *command, FILE *out) {
    if (strstr(command, "INSERT_LEFT")) {
        char *letter = strchr(command, ' ');
        if (list->finger->prev != list->sentinel) {     //  CAN'T INSERT CHAR BEFORE THE FIRST ELEMENT
            ListNode *newNode = createNode(letter[1]);  //  CREATES NODE BETWEEN TWO OTHER NODES
            newNode->next = list->finger;
            newNode->prev = list->finger->prev;
            list->finger->prev->next = newNode;
            list->finger->prev = newNode;
            list->finger = newNode;
            return;
        }
        fprintf(out, "ERROR\n");    //  ERROR MESSAGE IF THE CONDITION ISN'T MET
    } else if (strstr(command, "INSERT_RIGHT")) {
        char *letter = strchr(command, ' ');
        if (list->finger->next != NULL) {       //  CREATES A NODE AT THE END OF THE LIST
            ListNode *newNode = createNode(letter[1]);
            newNode->next = list->finger->next;
            newNode->prev = list->finger;
            list->finger->next->prev = newNode;
            list->finger->next = newNode;
            list->finger = newNode;
        } else {    //  CREATES NODE BETWEEN TWO OTHER NODES
            ListNode *newNode = createNode(letter[1]);
            newNode->prev = list->finger;
            list->finger->next = newNode;
            list->finger = newNode;
        }
    }
}