#pragma once

#include <stdio.h>
#include <curses.h>

typedef struct node{
    int prev; // points to the textbuffer[] index of the previous statement
    char statement[40]; // max. 40 characters
    int next; // points to the textbuffer[] index of the next statement
}node;

//Don't change here !!!
extern node textbuffer[25]; // Create struct as node textbuffer[25] (Without struct !!!!)
extern int free_head; 
extern int inuse_head; 

// Implement these functions 
void edit(char*);
void insert(int, char*);
void delete(int);
void undo();
void redo();
void display();
void save(char *);
void quit();


//
//Create a stack for functions: edit, insert, delete
//Enumeration for operation types: insert, delete, edit
typedef enum{
	INSERT,
	DELETE,
	EDIT
}action_type;

//Node structure for the stack
typedef struct Node{
	action_type operation;
	int index;
	char text_before[40];
	struct Node* next;
} Node;

//Stack structure for the function call stack
typedef struct Stack{
	Node* top;
} Stack;


extern Stack function_call_stack;
extern Stack redo_stack;

void push(Stack* stack, action_type action, int index, const char* previous_text);
void pop(struct Stack* stack);
struct Node* peek(struct Stack* stack);
int isEmpty(struct Stack* stack);
