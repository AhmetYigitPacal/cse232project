#include <stdio.h>
#include <string.h>
#include "cse232editor.h"

extern struct Stack redo_stack;
extern struct Stack function_call_stack;

// extern void push(struct Stack* stack, int operation, int index, const char* previous_text);
// extern void pop(struct Stack* stack);
// extern struct Node* peek(struct Stack* stack);
// extern int isEmpty(struct Stack* stack);

// typedef enum {
//     INSERT,
//     DELETE,
//     EDIT
// } action_type;

// struct Node {
//     action_type operation;
//     int index;
//     char text_before[40];
//     struct Node* next;
// };

// struct Stack {
//     struct Node* top;
// };

void redo() {
    if (isEmpty(&redo_stack)) {
        printf("Nothing to redo.\n");
        return;
    }

    struct Node* topNode = peek(&redo_stack);

    switch (topNode->operation) {
        case INSERT:
            insert(topNode->index, topNode->text_before);
            push(&function_call_stack, INSERT, topNode->index, "");
            break;

        case DELETE:
            push(&function_call_stack, DELETE, topNode->index, textbuffer[topNode->index].statement);
            delete(topNode->index);
            break;

        case EDIT:
            push(&function_call_stack, EDIT, topNode->index, textbuffer[topNode->index].statement);
            strcpy(textbuffer[topNode->index].statement, topNode->text_before);
            break;

        default:
            break;
    }

    pop(&redo_stack);
}

