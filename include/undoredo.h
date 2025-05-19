#ifndef UNDO_REDO_H_
#define UNDO_REDO_H_

//Create a stack for functions: edit, insert, delete
//Enumeration for operation types: insert, delete, edit
typedef enum{
	INSERT,
	DELETE,
	EDIT
} action_type;

//StackNode structure for the stack
typedef struct StackNode{
	action_type operation;
	int index;
	char text_before[40];
	struct StackNode* next;
} StackNode;

//Stack structure for the function call stack
typedef struct Stack{
	StackNode* top;
} Stack;

extern Stack function_call_stack;
extern Stack redo_stack;

void push(Stack* stack, action_type action, int index, const char* previous_text);
void pop(struct Stack* stack);
struct StackNode* peek(struct Stack* stack);
int isEmpty(struct Stack* stack);

#endif  // UNDO_REDO_H_