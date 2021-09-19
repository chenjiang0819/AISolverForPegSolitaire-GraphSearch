/*
 ============================================================================
 Name        : peg-solitaire.c
 Author      : Maurits van der Schee
 Description : Console version of the game "peg-solitaire" for GNU/Linux
 
 Developed by: Chen Jiang
 Student ID  :1127411
 ============================================================================
 */
#include<stdio.h>
#include "stack.h"
#include "utils.h"


void initialize_stack(){ 
	stack_top_idx = -1; 
}

void stack_push(node_t* n) {
  if(stack_top_idx == STACK_SIZE -1) { // overflow case. 
		printf("Error: stack overflow\n");
		return;
	}
	//In order to free all nodes, we make a linked list to store the nodes in the linked list
	stack_top_idx++;
	if(stack[stack_top_idx] != NULL){
		n -> next_free = stack[stack_top_idx];
	}
	stack[stack_top_idx] = n;
}

void stack_pop() {
	if(stack_top_idx == -1) { // If stack is empty, pop should throw error. 
		printf("Error: No element to pop\n");
		return;
	}
	stack_top_idx--;
}

node_t* stack_top() { 
	return stack[stack_top_idx]; 
}

int is_stack_empty() {
    if(stack_top_idx == -1) {
    	return 1;
	}
    return 0;
}

void print_stack() {
	printf("Stack: ");
	for(int i = 0; i<=stack_top_idx; i++){
		drawBoard( &(stack[i]->state) );
	}
	printf("\n");
}

void free_stack() {
	node_t* curr;
	node_t* pre;
	//for releasing all memories used by nodes, we traverse every linked list in the stack
	for(int i = 0; stack[i] != NULL; i++){		
		curr = stack[i];
		while((curr) != NULL){
			pre = curr;
			curr = curr -> next_free;
			free(pre);
		}
	}
    stack_top_idx = -1;
	printf("\n");
}