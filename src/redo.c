#include <stdio.h>
#include <string.h>
#include "texteditor.h"

bool redo() {
    if (isEmpty(&redo_stack)) {
        // printf("Nothing to redo.\n");
        return false;
    }

    struct StackNode* topNode = peek(&redo_stack);

    switch (topNode->operation) {
    case INSERT:
        push(&function_call_stack, INSERT, topNode->index, topNode->text_before);
        insert(topNode->index, topNode->text_before);
        break;

    case DELETE:
        push(&function_call_stack, DELETE, topNode->index, textbuffer[topNode->index].statement);
        delete(topNode->index);
        break;

    default:
        return false;
        break;
        
    }

    pop(&redo_stack);

    return true;
}