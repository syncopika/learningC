#include <stdio.h>
#include <stdlib.h>
#include "triangle_routines.h"
#define NMOVES 36
#define BOARD_LENGTH 15

/* function prototypes */

/* Return the number of pegs on the board. */
int npegs(int board[]);

/* Return 1 if the move is valid on this board, otherwise return 0. */
int valid_move(int board[], int move[]);

/* Make this move on this board. */
void make_move(int board[], int move[]);

/* Unmake this move on this board. */
void unmake_move(int board[], int move[]);

/* 
 * Solve the game starting from this board.  Return 1 if the game can
 * be solved; otherwise return 0.  Do not permanently alter the board passed
 * in. Once a solution is found, print the boards making up the solution in
 * reverse order. 
 */
int solve(int board[]);

/* global variable */
int moves[NMOVES][3] = 
{
	{0, 1, 3},
	{3, 1, 0},
	{0, 2, 5},
	{5, 2, 0},
	{1, 3, 6},
	{6, 3, 1},
	{1, 4, 8},
	{8, 4, 1},
	{2, 4, 7},
	{7, 4, 2},
	{2, 5, 9},
	{9, 5, 2},
	{3, 4, 5},
	{5, 4, 3},
	{3, 6, 10},
	{10, 6, 3},
	{3, 7, 12},
	{12, 7, 3},
	{4, 7, 11},
	{11, 7, 4},
	{4, 8, 13},
	{13, 8, 4},
	{5, 8, 12},
	{12, 8, 5},
	{5, 9, 14},
	{14, 9, 5},
	{6, 7, 8},
	{8, 7, 6},
	{7, 8, 9},
	{9, 8, 7},
	{10, 11, 12},
	{12, 11, 10},
	{11, 12, 13},
	{13, 12, 11},
	{12, 13, 14},
	{14, 13, 12}
};

/* function implementations */
int npegs(int board[]){
	
	int i;
	int total = 0;
	
	for(i = 0; i < BOARD_LENGTH; i++){
		total += board[i]; /* 1 if peg, 0 if no peg */
	}
	
	return total;
}

/* iterate through the board. 
   
   for every index with a 1,
   find the possible moves in the moves array. i.e.
   if board[2] = 1, look for {2, 5, 9}, {2, 5, 7}.
   
   check - are those options valid? that is,
   for those arrays, is board[move[1]] a 1? (there is a peg to jump over)
   is board[move[2]] a 0? (an empty spot)
*/

int valid_move(int board[], int move[]){
	
	/* firstPeg, secondPeg, and thirdPeg = 1 if there is a peg, 0 if no peg */
	int firstPeg = board[move[0]];
	int secondPeg = board[move[1]];
	int thirdPeg = board[move[2]];
	
	int cond1 = (firstPeg == 1);
	int cond2 = (secondPeg == 1) && (thirdPeg == 0);
	
	if(cond1 && cond2){
		return 1;
	}else{
		return 0;
	}
}

void make_move(int board[], int move[]){
	
	/* take board[move[0]].
	   move it to board[move[2]].
	   make board[move[0]] = 0.
	   make board[move[1]] = 0.
	   board[move[2]] = 1.
	*/
	board[move[2]] = 1;
	board[move[0]] = 0;
	board[move[1]] = 0;
	
}

void unmake_move(int board[], int move[]){
	
	board[move[0]] = 1;
	board[move[1]] = 1;
	board[move[2]] = 0;
	
}

/* the recursive function */
int solve(int board[]){
	
	/* base case 
	
	   every time solve() is called, it will check the number of pegs
	*/
	if(npegs(board) == 1){
		return 1;
	}
	
	int j;
	for(j = 0; j < NMOVES; j++){
		/* 
			look for a valid move. doesn't matter where it is, just find a valid one.
			then see if after doing that move the board is still solvable.
		*/
		if(valid_move(board, moves[j])){
			/* do the move */
			make_move(board, moves[j]);
			/* recursion part
			
			first check if that move results in a solvable board
			if not, undo that move and keep looking for a move
			that does have a solvable board.
						   
			we can do this because this function returns an int!
			*/
			int solvable = solve(board); /* recursion */
			if(solvable == 1){
				unmake_move(board, moves[j]);
				triangle_print(board);
				return 1; /* the board is solvable, so end here */ 
			}else{
				unmake_move(board, moves[j]);
				continue;
			}
		}
	} 
	/* if this point is reached, no valid move was found */
	/*printf("no moves were found. not solvable. \n");*/
	return 0;
}


int main(int argc, char *argv[]){
	
	if(argc != 16){
		fprintf(stderr, "Not a proper board!");
		return 0;
	}
	
	int theBoard[15];
	int i;
	for(i = 1; i < argc; i++){
		theBoard[i - 1] = atoi(argv[i]);
	}
	
	/*
	for(i = 0; i < 15; i++){
		printf("element %d: %d \n", i, theBoard[i]);
	}*/
	
	int solved = solve(theBoard);
	
	if(solved == 1){
		printf("Solution is possible.");
	}else{
		printf("No solution is possible.");
	}
	
	return 0;
	
}

