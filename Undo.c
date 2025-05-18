#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cse232editor.h"

//Push operation to add a function to the stack
void push(Stack* stack, action_type action, int index, const char* previous_text){
	Node* newTop = (Node*) malloc(sizeof(Node));
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
		printf("Stack UnderFlow Error: pop() from an empty stack");
		return;
	}
	else{
		Node* newTop = stack->top->next;
		free(stack->top);
		stack->top = newTop;
	}
}

//Peek operation to return the top of the stack(eventually the last operation done)
Node* peek(Stack* stack){
	return stack->top;
}

//Function to check wheter stack is empty or not
int isEmpty(Stack* stack){
	if (stack->top != NULL) return 0;
	return 1;
}

//Function call stack
Stack function_call_stack = {NULL};
Stack redo_stack = {NULL};

void undo(){
	//Implement the undo() function after completing the stack
	//Think about how to pop-push from the stack
    Node* topNode = peek(&function_call_stack);

	if (isEmpty(&function_call_stack)){
		printf("Error Stack UnderFlow: pop() from an empty stack");
		return;
	}

	switch(peek(&function_call_stack)->operation){
		case INSERT:
			delete(function_call_stack.top->index);//Be carefull name conflict
            push(&redo_stack, DELETE, topNode->index, textbuffer[topNode->index].statement);
			break;
		case DELETE:
			// insert(function_call_stack.top->index, function_call_stack.top->text_before);//I have to insert a new line for it. I actually have to get back the deleted line
            insert(function_call_stack.top->index, function_call_stack.top->text_before);
            push(&redo_stack, INSERT, topNode->index, "");
			break;
		// case EDIT:
		// 	strcpy(textbuffer[function_call_stack.top->index].statement, function_call_stack.top->text_before);
		// 	break;
		default:
			//Do nothing. No undo operation
			break;
	}
	pop(&function_call_stack);
}
