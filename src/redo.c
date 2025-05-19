#include <stdio.h>
#include <string.h>
#include "texteditor.h"

extern struct Stack redo_stack;
extern struct Stack function_call_stack;

// extern void push(struct Stack* stack, int operation, int index, const char* previous_text);
// extern void pop(struct Stack* stack);
// extern struct StackNode* peek(struct Stack* stack);
// extern int isEmpty(struct Stack* stack);

// typedef enum {
//     INSERT,
//     DELETE,
//     EDIT
// } action_type;

// struct StackNode {
//     action_type operation;
//     int index;
//     char text_before[40];
//     struct StackNode* next;
// };

// struct Stack {
//     struct StackNode* top;
// };

void redo() {
    if (isEmpty(&redo_stack)) {
        printf("Nothing to redo.\n");
        return;
    }

    struct StackNode* topNode = peek(&redo_stack);

    switch (topNode->operation) {
        case INSERT:
            insert(topNode->index, topNode->text_before);
            push(&function_call_stack, INSERT, topNode->index, "");
            break;

        case DELETE:
            push(&function_call_stack, DELETE, topNode->index, textbuffer[topNode->index].statement);
            delete(topNode->index);
            break;

        // case EDIT:
        //     push(&function_call_stack, EDIT, topNode->index, textbuffer[topNode->index].statement);
        //     strcpy(textbuffer[topNode->index].statement, topNode->text_before);
        //     break;

        default:
            break;
    }

    pop(&redo_stack);
}

void insert_without_push(int index, char* text) {
    if (free_head == -1) {
        printw("No space left in buffer.\n");
        return;
    }

    int new_node = free_head;
    free_head = textbuffer[free_head].next;

    strncpy(textbuffer[new_node].statement, text, 39);
    textbuffer[new_node].statement[39] = '\0';
    textbuffer[new_node].prev = -1;
    textbuffer[new_node].next = -1;

    if (inuse_head == -1 || index == 0) {
        textbuffer[new_node].next = inuse_head;
        if (inuse_head != -1)
            textbuffer[inuse_head].prev = new_node;
        inuse_head = new_node;
    } else {
        int current = inuse_head;
        int count = 0;
        while (count < index - 1 && textbuffer[current].next != -1) {
            current = textbuffer[current].next;
            count++;
        }

        int next_node = textbuffer[current].next;
        textbuffer[current].next = new_node;
        textbuffer[new_node].prev = current;
        textbuffer[new_node].next = next_node;

        if (next_node != -1)
            textbuffer[next_node].prev = new_node;
    }

    // Bu versiyon stack'e push yapmaz!
}
