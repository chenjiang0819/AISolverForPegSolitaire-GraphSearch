/*
 ============================================================================
 Name        : peg-solitaire.c
 Author      : Maurits van der Schee
 Description : Console version of the game "peg-solitaire" for GNU/Linux
 
 Developed by: Chen Jiang
 ============================================================================
 */
#include <time.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

#include "ai.h"
#include "utils.h"
#include "hashtable.h"
#include "stack.h"


void copy_state(state_t* dst, state_t* src){
	//Copy field
	memcpy( dst->field, src->field, SIZE*SIZE*sizeof(int8_t) );
	dst->cursor = src->cursor;
	dst->selected = src->selected;
}

/**
 * Saves the path up to the node as the best solution found so far
*/
void save_solution(node_t* solution_node ){
	node_t* n = solution_node;
	while( n->parent != NULL ){
		copy_state( &(solution[n->depth]), &(n->state) );
		solution_moves[n->depth-1] = n->move;
		n = n->parent;
	}
	solution_size = solution_node->depth;
}

//create and initialise the node
node_t* create_init_node(state_t* init_state ){
	node_t * new_n = (node_t *) malloc(sizeof(node_t));
	new_n->parent = NULL;	
	new_n->next_free = NULL;
	new_n->depth = 0;
	copy_state(&(new_n->state), init_state);
	return new_n;
}

/**
 * Apply an action to node n and return a new node resulting from executing the action
*/
node_t* applyAction(node_t* n, position_s* selected_peg, move_t action ){
    node_t* new_node = create_init_node(&(n -> state));
	//FILL IN MISSING CODE
    //calculate the depth of the new node
    new_node -> depth =  n -> depth + 1;
    //copy the board state from old node to the new node
    copy_state(&(new_node->state), &(n->state));
    //move the cursor on the selected peg
	new_node -> state.cursor.x = selected_peg -> x;
	new_node -> state.cursor.y = selected_peg -> y;
    //we assigned the direction of the movement
    new_node -> move = action;
    //execute the movement
    execute_move_t(&(new_node->state), selected_peg, action);
    // point to its parent
    new_node -> parent = n;
    //return the new node
	return new_node;
}

/**
 * Find a solution path as per algorithm description in the handout
 */

int do_action(int* remain_Pegs, move_t move_to, node_t* n, HashTable* table, position_s* selected_peg){
	// check that if the movement is available
	if(can_apply(&(n -> state), selected_peg, move_to)){
		//if available, execute the action and generate a node
		node_t* new_node = applyAction(n, selected_peg, move_to);
		generated_nodes ++;
		//if AI won the game, return true
		if(won(&(new_node -> state)) == 1){
			//save the solution
			save_solution(new_node);
			*remain_Pegs = num_pegs(&(new_node -> state));
			//for freeing all nodes in once, I still put the result in the stack
			stack_push(new_node);
			return 1;
		}else{
			//we check whether the current board is in the Hash table from 4 directions  
			if(ht_contains(table, new_node -> state.field) == HT_FOUND){
				//if the board is in the Hash table ,we discard it.
				free(new_node);
				return 0;
			}
			rotateBoard(&(new_node -> state));
			if(ht_contains(table, new_node -> state.field) == HT_FOUND){
				//if the board is in the Hash table ,we discard it.
				free(new_node);
				return 0;
			}
			rotateBoard(&(new_node -> state));
			if(ht_contains(table, new_node -> state.field) == HT_FOUND){
				//if the board is in the Hash table ,we discard it.
				free(new_node);
				return 0;
			}
			rotateBoard(&(new_node -> state));
			if(ht_contains(table, new_node -> state.field) == HT_FOUND){
				//if the board is in the Hash table ,we discard it.
				free(new_node);
				return 0;
			}
			rotateBoard(&(new_node -> state));
			//if it is not in the Hash table, we put it in the Hash table and push it in the stack
			ht_insert(table, new_node -> state.field, new_node -> state.field);
			stack_push(new_node);
			return 0;
		}
	}
}

void find_solution(state_t* init_state){
    move_t move_to;
	HashTable table;
	position_s selected_peg;
	// Choose initial capacity of PRIME NUMBER 
	// Specify the size of the keys and values you want to store once 
	ht_setup(&table, sizeof(int8_t) * SIZE * SIZE, sizeof(int8_t) * SIZE * SIZE, 16769023);
	// Initialize Stack
	initialize_stack();
	//Add the initial node
	node_t* n = create_init_node(init_state);
	//FILL IN THE GRAPH ALGORITHM
	//push the first node in the stack
	stack_push(n);
	//set the number of the remaining pegs as the original value 
	int remain_Pegs = num_pegs(&(n -> state));
	// if the stack is not empty
	while(is_stack_empty() != 1){
		//get the last node from stack
		n = stack_top();
		stack_pop();
		expanded_nodes++;
		//if the node has a better solution, we keep the solution, even it is not converged
		if(num_pegs(&(n -> state)) < remain_Pegs){
			save_solution(n);
			remain_Pegs = num_pegs(&(n -> state));
		}
		//scan the board of the node
		for (int x=0;x<SIZE;x++) {
			for (int y=0;y<SIZE;y++) {
				// when we find a peg on the board
				if(n -> state.field[x][y] == 'o'){	
					//deliver the position of the current peg 
					selected_peg.x = x;
					selected_peg.y = y;
					//try to move the peg to the left
					move_to = left;
					//if AI won the game, we free memory and return  
					if(do_action(&remain_Pegs, move_to, n, &table, &selected_peg) ==1){
						free_memory(&table);	
						return;
					}
					//try to move the peg to the right
					move_to = right;
					//if AI won the game, we free memory and return  					
					if(do_action(&remain_Pegs, move_to, n, &table, &selected_peg) ==1){
						free_memory(&table);	
						return;
					}
					//try to move the peg to the upward
					move_to = up;
					//if AI won the game, we free memory and return  					
					if(do_action(&remain_Pegs, move_to, n, &table, &selected_peg) ==1){
						free_memory(&table);	
						return;
					}
					//try to move the peg to the downward 
					move_to = down;
					//if AI won the game, we free memory and return  					
					if(do_action(&remain_Pegs, move_to, n, &table, &selected_peg) ==1){
						free_memory(&table);	
						return;
					}
				}
			}
		}
		//monitor if the number of the expanded nodes has reached the budget
		if(expanded_nodes >= budget){
			free_memory(&table);	
			return;
		}
	}
}

//free all used memories
void free_memory(HashTable* table){
	//free the memories used by Hash table
	ht_destroy(table);
	//free the memories used by nodes
	free_stack();
}
