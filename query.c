/* DINCĂ Alexandra-Cristina - 311CD */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "struct.h"
#include "create.h"
#include "update.h"
#include "query.h"

//  EITHER SHOWS THE ELEMENT AT THE CURRENT ADDRESS OR ITERATES THROUGH THE LIST AND SHOWS ALL ELEMENTS

void showCurrent (List *list, FILE *out) {
    fprintf(out, "%c\n", list->finger->elem);
}

void showAll (List *list, FILE *out) {
    ListNode *iter = list->sentinel->next;
    while (iter != NULL) {
        if (iter == list->finger) {
            fprintf(out, "|%c|", iter->elem);
        } else {
            fprintf(out, "%c", iter->elem);
        }
        iter = iter->next;
    }
    fprintf(out, "\n");
}