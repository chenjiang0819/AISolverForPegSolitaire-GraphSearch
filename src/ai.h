/*
 ============================================================================
 Name        : peg-solitaire.c
 Author      : Maurits van der Schee
 Description : Console version of the game "peg-solitaire" for GNU/Linux
 
 Developed by: Chen Jiang
 ============================================================================
 */
#ifndef __AI__
#define __AI__

#include <stdint.h>
#include <unistd.h>
#include "utils.h"
#include "hashtable.h"

void find_solution( state_t* init_state );
//free all used memories
void free_memory(HashTable* table);
//after find the pegs on the board, we check and execute actions 
int do_action(int* remain_Pegs, move_t move_to, node_t* n, HashTable* table, position_s* selected_peg);
#endif
