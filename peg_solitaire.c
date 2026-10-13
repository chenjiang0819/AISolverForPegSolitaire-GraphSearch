/*
 ============================================================================
 Name        : peg-solitaire.c
 Author      : Maurits van der Schee
 Description : Console version of the game "peg-solitaire" for GNU/Linux
 
 Developed by: Chen Jiang
 ============================================================================
 */


#include "src/utils.h"
#include "src/ai.h"
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

void setBufferedInput(bool enable) {
	if (!isatty(STDIN_FILENO)) return;
	static bool enabled = true;
	static struct termios old;
	struct termios new;

	if (enable && !enabled) {
		// restore the former settings
		tcsetattr(STDIN_FILENO,TCSANOW,&old);
		// set the new state
		enabled = true;
	} else if (!enable && enabled) {
		// get the terminal settings for standard input
		if (tcgetattr(STDIN_FILENO,&new)!=0) return;
		// we want to keep the old setting to restore them at the end
		old = new;
		// disable canonical mode (buffered i/o) and local echo
		new.c_lflag &=(~ICANON & ~ECHO);
		// set the new settings immediately
		tcsetattr(STDIN_FILENO,TCSANOW,&new);
		// set the new state
		enabled = false;
	}
}


void signal_callback_handler(int signum) {
	printf("         TERMINATED         \n");
	setBufferedInput(true);
	printf("\033[?25h\033[0m");
	exit(signum);
}

void print_usage(void){
    printf("To run the AI solver, <level> and <budget> are integers, play_solution is optional. \n");
    printf("\tUSAGE: ./pegsol <level> AI <budget> play_solution\n");
    printf("\t\tor, to play with the keyboard: \n");
    printf("\tUSAGE: ./pegsol level\n");
}

int main(int argc, char *argv[]) {
	/**
	 * Parsing command line options
	 */

    if (argc<2 || argc>6) { print_usage();return EXIT_FAILURE; }
    char *end;errno=0;long level=strtol(argv[1],&end,10);
    if (errno || !*argv[1] || *end || level<0 || level>8) { print_usage();return EXIT_FAILURE; }
    int layout=(int)level;
    state_t board_alloc;
    state_t *board=&board_alloc;
    ai_run=argc>2;
    if (ai_run && strcmp(argv[2],"AI")) {print_usage();return EXIT_FAILURE;}
    budget=1000000;
    if (argc>3) {
        errno=0;long requested=strtol(argv[3],&end,10);
        if (errno || !*argv[3] || *end || requested<1 || requested>INT_MAX) { print_usage();return EXIT_FAILURE; }
        budget=(int)requested;
    }
    show_solution=false;
    if (argc==5 && !strcmp(argv[4],"play_solution")) show_solution=true;
    else if (argc==6 && !strcmp(argv[4],"play") && !strcmp(argv[5],"solution")) show_solution=true;
    else if (argc>4) { print_usage();return EXIT_FAILURE; }

	// reset, hide cursor and clear screen
	printf("\033[0m\033[?25l\033[2J");

	// force stop
	// register signal handler for when ctrl-c is pressed
	signal(SIGINT, signal_callback_handler);

	// initialize board
	initialize(board,layout);
	memcpy(&solution[0],board,sizeof(*board));
	drawBoard(board);
	setBufferedInput(false);

	//AI ALGORITHM
	if( ai_run ){ 
		generated_nodes = 0;
		expanded_nodes = 0;
		solution_size = 0;

		//time
		clock_t start = clock();

		// AI ALGORITHM CALL
		find_solution( board );

		clock_t end = clock();
     	double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

		if( show_solution ) {
			play_solution();
		}

		printf("SOLUTION:                               \n");
		print_solution( );
		printf("STATS: \n");
		printf("\tExpanded nodes: %d\n\tGenerated nodes: %d\n", expanded_nodes, generated_nodes);
		printf("\tSolution Length: %d\n", solution_size);
		printf("\tNumber of Pegs Left: %d\n", num_pegs( &(solution[solution_size]) ) );
		printf("\tExpanded/seconds: %.0f\n", cpu_time_used>0 ? expanded_nodes/cpu_time_used : 0.0 );
		printf("\tTime (seconds): %f\n", cpu_time_used );

		setBufferedInput(true);
		printf("\033[?25h\033[0m");
		return EXIT_SUCCESS;
	}else{

		
		int8_t moves = 0;
		int c;
		bool success,move;
		while (true) {
			c=getchar();
            if (c==EOF) break;
			move = (*board).selected;
			switch(c) {
				case 97:	// 'a' key
				case 104:	// 'h' key
				case 68:	// left arrow
					success = moveLeft(board);  break;
				case 100:	// 'd' key
				case 108:	// 'l' key
				case 67:	// right arrow
					success = moveRight(board); break;
				case 119:	// 'w' key
				case 107:	// 'k' key
				case 65:	// up arrow
					success = moveUp(board);    break;
				case 115:	// 's' key
				case 106:	// 'j' key
				case 66:	// down arrow
					success = moveDown(board);  break;
				case 10:	// enter key
				case 13:	// enter key
					success = select_peg(board);
					move    = false;            break;
				default: success = false;
			}
			if (success) {
				if (move) {
					moves++;
					memcpy(&solution[moves],board,sizeof(*board));
				}
				drawBoard(board);
				if (won(board)) {
					printf("          YOU WON           \n");
					break;
				}
				if (gameEndedForHuman(board)) {
					printf("         GAME OVER          \n");
					break;
				}
			}
			if (c=='q') {
				printf("        QUIT? (y/n)         \n");
				c=getchar();
				if (c=='y'){
					break;
				}
				drawBoard(board);
			}
			if (c=='r') {
				printf("       RESTART? (y/n)       \n");
				c=getchar();
				if (c=='y'){
					initialize(board,layout);
					moves=0;
					memcpy(&solution[moves],board,sizeof(*board));
				}
				drawBoard(board);
			}
			if (c=='u') {
				printf("        UNDO? (y/n)         \n");
				c=getchar();
				if (c=='y' && moves){
					moves--;
					memcpy(board,&solution[moves],sizeof(*board));
				}
				drawBoard(board);
			}
		}
		setBufferedInput(true);
		printf("\033[?25h\033[0m");

		return EXIT_SUCCESS;
	}
}
