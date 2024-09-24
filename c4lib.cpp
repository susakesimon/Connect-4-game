#include "c4lib.h"
#include <iostream>
using namespace std;

// Prototype internal helper functions
/**
 * @brief returns the smallest y coordinate that is BLANK in 
 *        column x or -1 if no location is BLANK
 */
int findYValue(BoardValue** board, int ydim, int x);


// ------------------------------------------------------------
// Global variabes - the ONLY we allow in this program

// converts integer player value: 0 or 1 to appropriate enum
enum BoardValue playerToValue[2] = {RED, YELLOW};

// ----------------------------------------------------------------------


// Helper function 
int findYValue(BoardValue** board, int ydim, int x)
{
  // You complete
	for(int i=0; i<ydim; i++){
		if(board[i][x] == BLANK){
		// board[i] allocateBoard(ydim, xdim);
			return i;
		}
	}
	return -1;
}

BoardValue** allocateBoard(int ydim, int xdim)
{
  // You complete
	// allocating the memory for the board
	BoardValue** scores =  new BoardValue*[ydim];
	for(int i=0; i<ydim; i++){
		// making the x axis
		// scores is the board
		scores[i] = new BoardValue[xdim];
	}
	// make the values null
	for(int i=0; i<ydim; i++){
		for(int j=0; j<xdim; j++){
			scores[i][j] = BLANK;
		}
	}

	return scores;
}
void deallocateBoard(BoardValue** board, int ydim)
{
  // You complete
	for(int i=0; i<ydim; i++){
		delete [] board[i];
	}
	delete [] board;
}

void printBoard(BoardValue** board, int ydim, int xdim)
{
  // Complete - Do not alter
  const char* boardToString[] = { "\U000026ab", "\U0001F534", "\U0001F7E1" }; 
                                  //  "⚫",          "🔴",         "🟡"}
  for(int y = ydim-1; y >= 0; y--){
    for(int x = 0; x < xdim; x++) {
      cout << boardToString[(int)board[y][x]] << " ";
    }
    cout << endl;
  }
  cout << endl;
}

bool getNextHumanInput(
  BoardValue** board, 
  int ydim, int xdim, 
  int *y, int *x,
  int currentPlayer)
{
  // You complete
	// get a value then place it in x column
	int col;
	cin >> col;
	if(col>=xdim || col < 0){
		// make sure it is in bounds
		return true;
	}
	int rowValue = findYValue(board, ydim, col);
	if(rowValue == -1){
		// -1 is what happens when out of bounds
		return true;
	}

	// put the piece on the board
	board[rowValue][col] = playerToValue[currentPlayer];
	*x = col;
	*y = rowValue; 
	return false;

}

bool hasWon(
  BoardValue** board,
  int ydim, int xdim,
  int sy, int sx,
  int currentPlayer)
{
  // Keep, modify, or delete these as you desire
  const int NDIRS = 4;
  const int xDirDelta[NDIRS] = { 0, +1, -1, +1};
  const int yDirDelta[NDIRS] = {+1,  0, +1, +1};
  // You complete
	for (int i=0; i<ydim; i++){
		int direction = 0;
		for(int j=0; j < xdim; j++){
			// check if in a row 
			// horizontally
			if(board[i][j] == playerToValue[currentPlayer]){
				direction ++;
				if(direction==4){
					return true;
				}
			}
			else{
				// reset the count for in a row
				direction =0;
			}
		}
	}
	for(int i=0; i < xdim; i++){
		// if in row vertically
		int direction = 0;
		for (int j=0; j< ydim; j++){
			if(board[j][i] == playerToValue[currentPlayer]){
				direction ++;
				if (direction == 4){
					return true;
				}
			}
			else{
				// reset count
				direction = 0;
			}

		}
	}
	// check from top left to bottom right
	for(int i=0; i<xdim; i++){
		int xValue = i;
		int yValue = ydim -1;
		int direction = 0;
		// finish
		while (xValue<xdim && yValue < ydim && yValue >= 0 && xValue >=0){
			if(board[yValue][xValue] == playerToValue[currentPlayer]){
				direction++;
				if(direction == 4){
				return true;
				}
			}
			else{
				direction =0;
			}
			xValue++;
			yValue--;
		}

	}
	// check from top right to bottom left
	for(int i=0; i<xdim; i++){
		int xValue = i;
		int yValue = ydim -1;
		int direction = 0;
		// finish
		while (xValue<xdim && yValue < ydim && xValue >= 0 && yValue >= 0){
			if(board[yValue][xValue] == playerToValue[currentPlayer]){
				direction++;
				if(direction == 4){
					return true;
				}
			}
			else{
				direction = 0;
			}
			xValue--;
			yValue--;
			
		}
	}
	// from bottom left to top right
	for(int i=0; i<xdim; i++){
		int xValue = i;
		int yValue =0; 
		int direction =0;

		while(xValue<xdim && yValue<ydim && xValue >= 0 && yValue>= 0){
			if(board[yValue][xValue] == playerToValue[currentPlayer]){
				direction++;
				if(direction == 4){
					return true;
				}
			}
			else{
				direction=0;
			}
			xValue--;
			yValue++;

		}
	}
	// from right to left from the bottom left
	for(int i=0; i<xdim; i++){
		int xValue = i;
		int yValue =0; 
		int direction =0;
		while(xValue<xdim && yValue<ydim && xValue >= 0 && yValue>= 0){
			if(board[yValue][xValue] == playerToValue[currentPlayer]){
				direction++;
				if(direction == 4){
					return true;
				}
			}
			else{
				direction = 0;
			}
			xValue++;
			yValue++;
		}

	}
	return false;


}

bool isDraw(
  BoardValue** board,
  int ydim, int xdim)
{
  // You complete
	for(int i=0; i<xdim; i++){
		// find any blank spots
		if (board[ydim-1][i] == BLANK){
			return false;
		}
	}
	return true;

}



bool getUserAIInput(
  BoardValue** board, 
  int ydim, int xdim, 
  int *y, int *x,
  int currentPlayer)
{
  // You complete
  // Check if the current player can win
	// bool flag = false;
	// flag = isDraw(board**, ydim, xdim);
	// flag = hasWon (BoardValue** board, ydim, xdim, &y, &x, currentPlayer);
	// if(flag){
	// 	return true;
	// }

	for(int i=0; i<xdim; i++){
		// checking the row
		int rowValue = findYValue(board, ydim, i);
		if(rowValue != -1){
			board[rowValue][i] = playerToValue[currentPlayer];
			if(hasWon(board, ydim, xdim, rowValue, i, currentPlayer)){
				*x = i;
				*y = rowValue;
				return false;
			}
			board[rowValue][i] = BLANK;
		}
	}

  // Check if we need to block 
  //  We can greedily play the first blocking location since
  //  if they can win in multiple ways it does not matter which
  //  we choose.
	for(int i=0; i<xdim; i++){
		int rowValue = findYValue(board, ydim, i);
		int nextP1 = currentPlayer -1;
		if(rowValue!= -1){
			board[rowValue][i] = playerToValue[nextP1];
			// finish
			if(hasWon(board, ydim, xdim, rowValue, i, nextP1)){
				*x= i;
				*y=rowValue;
				board[rowValue][i] = playerToValue[currentPlayer];//put our color there
				return false;
			}
			board[rowValue][i] = BLANK;
		}
	}


  // Add any other logic for how to choose a location to play
  // if neither case above occurs
	for(int i=0; i<xdim; i++){
		int rowValue = findYValue(board, ydim, i);
		if(rowValue != -1){
			*y=rowValue;
			*x=i;
			board[rowValue][i] = playerToValue[currentPlayer];
			return false;
		}
	}
	return true;

  
}

// Complete - Do not alter
bool getRandomAIInput(
  BoardValue** board, 
  int ydim, int xdim, 
  int *y, int *x,
  int currentPlayer)
{
  // Allocate variable size array (we don't know xdim when we compile)
  int* possible = new int[xdim];
  int numX = 0;
  bool error = true;
  // find all the possible columns with a BLANK
  for(int i = 0; i < xdim; i++){
    if(board[ydim-1][i] == BLANK){
      possible[numX++] = i;
    }
  }
  // If at least 1 column has a BLANK
  if(numX != 0){
    // Choose one column
    *x = possible[rand()%numX];
    *y = findYValue(board, ydim, *x);
    board[*y][*x] = playerToValue[currentPlayer];
    error = false;  
  }
  delete [] possible;
  return error;
}
