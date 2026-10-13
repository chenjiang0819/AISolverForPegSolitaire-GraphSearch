#include "../src/ai.h"
#include "../src/stack.h"
#include <assert.h>

static void replay(void) {
    for (int i=1;i<=solution_size;i++) {
        state_t before=solution[i-1];
        position_s peg=solution[i].cursor;
        switch(solution_moves[i-1]) {
        case left: peg.x+=2; break; case right: peg.x-=2; break;
        case up: peg.y+=2; break; case down: peg.y-=2; break;
        }
        assert(can_apply(&before,&peg,solution_moves[i-1]));
        execute_move_t(&before,&peg,solution_moves[i-1]);
        assert(!memcmp(before.field,solution[i].field,sizeof(before.field)));
    }
}

int main(void) {
    state_t board={0}; memset(board.field,' ',sizeof(board.field));
    assert(!won(&board)); board.field[4][4]='o'; assert(won(&board));
    position_s invalid={-1,0}; assert(!can_apply(&board,&invalid,left));
    invalid.x=SIZE; assert(!can_apply(&board,&invalid,right));
    position_s selected={4,4}; assert(!can_apply(&board,&selected,(move_t)99));
    state_t before=board; execute_move_t(&board,&selected,left);
    assert(!memcmp(&board,&before,sizeof(board)));
    board.cursor.x=2; board.cursor.y=6; before=board;
    for(int i=0;i<4;i++) rotateBoard(&board);
    assert(!memcmp(&board,&before,sizeof(board)));
    budget=100;
    for(int repeat=0;repeat<3;repeat++) {
        initialize(&board,0); find_solution(&board); replay();
        assert(num_pegs(&solution[solution_size])==1);
        assert(expanded_nodes<=budget);
    }
    memset(board.field,' ',sizeof(board.field)); board.field[0][0]='o';board.field[8][8]='o';
    find_solution(&board); assert(solution_size==0); assert(expanded_nodes==1);
    board.field[8][8]=' '; find_solution(&board); assert(won(&solution[0]));
    initialize(&board,4);budget=1;find_solution(&board);assert(expanded_nodes==1);
    initialize_stack();
    for(int i=0;i<STACK_SIZE;i++) { node_t *n=calloc(1,sizeof(*n));assert(n);stack_push(n); }
    free_stack(); assert(is_stack_empty());
    for(int i=0;i<STACK_SIZE;i++) assert(!stack[i]);
    HashTable table;assert(ht_setup(&table,sizeof(int),sizeof(int),8)==HT_SUCCESS);
    for(int i=0;i<100;i++)assert(ht_insert(&table,&i,&i)!=HT_ERROR);
    for(int i=0;i<100;i++)assert(*(int*)ht_lookup(&table,&i)==i);
    assert(ht_destroy(&table)==HT_SUCCESS);
    puts("Core transitions, replay, bounded/repeated search, ownership, and hash growth passed.");
    return 0;
}
