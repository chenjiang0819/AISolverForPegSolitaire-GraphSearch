/*
 ============================================================================
 Name        : peg-solitaire.c
 Author      : Maurits van der Schee
 Description : Console version of the game "peg-solitaire" for GNU/Linux
 
 Developed by: Chen Jiang
 ============================================================================
 */
#ifndef __STACK_PEG__
#define __STACK_PEG__

#include "utils.h"

// The upperbound solution length = size of the matrix * 4 moves = maximum possible number of pegs * 4 moves
#define STACK_SIZE (SIZE*SIZE*SIZE*SIZE*4)

// Stack as an arrray
extern node_t* stack[STACK_SIZE];

// Variable marking the top of the stack
extern int stack_top_idx;

// Needs to be called before using it for the first time
void initialize_stack(void);

void stack_push(node_t* n); 

void stack_pop(void);

node_t* stack_top(void);

int is_stack_empty(void);

void print_stack(void);

void free_stack(void);

#endif
