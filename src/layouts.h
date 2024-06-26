/*
 ============================================================================
 Name        : peg-solitaire.c
 Author      : Maurits van der Schee
 Description : Console version of the game "peg-solitaire" for GNU/Linux
 
 Developed by: Chen Jiang
 ============================================================================
 */
#ifndef __LAYOUTS__
#define __LAYOUTS__

#define NUM_LAYOUTS 9
int8_t configuration[NUM_LAYOUTS][SIZE][SIZE*2] = {{
            "                  ",
            "                  ",
            "                  ",
            "      o o . o     ",
            "                  ",
            "                  ",
            "                  ",
            "                  ",
            "                  "
        },{
            "                  ",
            "                  ",
            "                  ",
            "      o o .       ",
            "        o         ",
            "        o         ",
            "                  ",
            "                  ",
            "                  "
        },{
            "                  ",
            "                  ",
            "          o       ",
            "      . o o       ",
            "        o o o     ",
            "        o         ",
            "                  ",
            "                  ",
            "                  "
        },{
            "o o o . . .       ",
            "o o o . . .       ",
            ". o o . . .       ",
            "      o o o       ",
            "      o o o       ",
            "      o o o       ",
            "                  ",
            "                  ",
            "                  "
        },{
            "                  ",
            "      o o o       ",
            "      o o o       ",
            "  o o o o o o o   ",
            "  o o o . o o o   ",
            "  o o o o o o o   ",
            "      o o o       ",
            "      o o o       ",
            "                  "
        },{
            "                  ",
            "      o o o       ",
            "    o o o o o     ",
            "  o o o . o o o   ",
            "  o o o o o o o   ",
            "  o o o o o o o   ",
            "    o o o o o     ",
            "      o o o       ",
            "                  "
        },{
            "      o o o       ",
            "      o o o       ",
            "      o o o       ",
            "o o o o o o o o o ",
            "o o o o . o o o o ",
            "o o o o o o o o o ",
            "      o o o       ",
            "      o o o       ",
            "      o o o       "
        },{
            "      o o o       ",
            "      o o o       ",
            "      o o o       ",
            "  o o o o o o o o ",
            "  o o o . o o o o ",
            "  o o o o o o o o ",
            "      o o o       ",
            "      o o o       ",
            "                  "
        },{
            "        o         ",
            "      o o o       ",
            "    o o o o o     ",
            "  o o o o o o o   ",
            "o o o o . o o o o ",
            "  o o o o o o o   ",
            "    o o o o o     ",
            "      o o o       ",
            "        o         "
        }};

    #endif
