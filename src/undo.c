#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "texteditor.h"

//Push operation to add a function to the stack
void push(Stack* stack, action_type action, int index, const char* previous_text){
	StackNode* newTop = (StackNode*) malloc(sizeof(StackNode));
	if (newTop == NULL){
		printf("Segmentation Fault: Memory could not allocated properly");
		return;
	}
	newTop->operation = action;
	newTop->index = index;
	strncpy(newTop->text_before, previous_text, 39);
	newTop->text_before[39] = '\0';
	newTop->next = stack->top;
	stack->top = newTop;
}

//Pop operation to remove the last function called from the stack
void pop(Stack* stack){
	if (stack->top == NULL){
		printw("Stack UnderFlow Error: pop() from an empty stack");
		return;
	}
	else{
		StackNode* newTop = stack->top->next;
		free(stack->top);
		stack->top = newTop;
	}
}

//Peek operation to return the top of the stack(eventually the last operation done)
StackNode* peek(Stack* stack){
    if (stack->top == NULL){
        printw("Stack UnderFlow Error: peek() from an empty stack");
        return NULL;
    }
	return stack->top;
}

//Function to check whether stack is empty or not
int isEmpty(Stack* stack){
	return stack->top == NULL;
}

void clearStack(Stack* stack){
    StackNode* current = stack->top;
    while (current != NULL){
        StackNode* next = current->next;
        free(current);
        current = next;
    }
    stack->top = NULL;
}

//Function call stack
Stack function_call_stack = {NULL};
Stack redo_stack = {NULL};

bool undo(){    
	if (isEmpty(&function_call_stack)){
		return false;
	}

    StackNode* topNode = peek(&function_call_stack);

	switch(topNode->operation){
    case INSERT:
        push(&redo_stack, INSERT, topNode->index, textbuffer[topNode->index].statement);
        delete(function_call_stack.top->index);
        break;

    case DELETE:
        push(&redo_stack, DELETE, topNode->index, textbuffer[topNode->index].statement);
        insert(function_call_stack.top->index, topNode->text_before);
        break;

    default: // Should never reach
        return false;
        break;

	}

	pop(&function_call_stack);

    return true;
}
