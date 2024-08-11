#include <iostream>
#include <curses.h>
#include <cstring>

using namespace std;

class Game {
  public:
	  int board[4][4] = {
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0}
		};

    void insertRandomNumberOntoBoard() {
      // get random seed
      int randomNumberSeed = rand();

      // 3/10 chance of inserting a 4
      int value;
      if (randomNumberSeed % 10 <= 2) {
        value = 4;
      } else {
        value = 2;
      }

      // compute position
      int starterSquare = randomNumberSeed % 16;
      int yPosition = starterSquare / 4;
      int xPosition = starterSquare % 4;

      // make sure the square has no previously assigned value
      if (this->board[yPosition][xPosition] == 0) {
        this->board[yPosition][xPosition] = value;
        return;
      }

      return this -> insertRandomNumberOntoBoard();

    };

    void render(int cycles) {
      // render the game state to the terminal

      for (int y = 0; y < 4; y++) {
        string line = "";
        for (int x = 0; x < 4; x++) {
          int currentSquare = this->board[y][x];
          line = line + to_string(currentSquare) + " ";
        }
        mvprintw(y, 0, line.c_str());
      }


      string lineNumberOfMoves = "Number of moves: " + to_string(cycles);
      mvprintw(5, 0, lineNumberOfMoves.c_str());
    };

    void moveLeftWithinRow(int currentRow, int currentColumn) {
      if (currentColumn <= 0) {
        return;
      }

      int nextColumn = currentColumn - 1;

      int currentSquare = this->board[currentRow][currentColumn];
      int nextSquare = this->board[currentRow][nextColumn];

      if (currentSquare == 0) {
        return moveLeftWithinRow(currentRow, nextColumn);
      }

      // assign the current square to the next square if the next square is a zero
      if (nextSquare == 0) {
        this -> board[currentRow][nextColumn] = currentSquare;
        this -> board[currentRow][currentColumn] = 0;
        return moveLeftWithinRow(currentRow, nextColumn);
      }

      // combine the current square with the next square if they match
      else if (nextSquare == currentSquare) {
        this -> board[currentRow][nextColumn] = currentSquare + nextSquare;
        this -> board[currentRow][currentColumn] = 0;
        nextColumn = nextColumn - 1;
      }

      return moveLeftWithinRow(currentRow, nextColumn);

    }

    void moveLeft() {
      
      for (int currentRow = 0; currentRow < 4; currentRow ++) {
        this -> moveLeftWithinRow(currentRow, 3);
      }

    };

    void moveDown() {

      for (int x = 0; x < 4; x++) {
        // for column in the game, move everything all the way down recursively
        for (int y = 0; y < 4; y++) {
          int currentSquare = this->board[y][x];
        }
      }

    };

    void moveRightWithinRow(int currentRow, int currentColumn) {
      if (currentColumn >= 3) {
        return;
      }

      int nextColumn = currentColumn + 1;

      int currentSquare = this->board[currentRow][currentColumn];
      int nextSquare = this->board[currentRow][nextColumn];

      if (currentSquare == 0) {
        return moveRightWithinRow(currentRow, nextColumn);
      }

      // assign the current square to the next square if the next square is a zero
      if (nextSquare == 0) {
        this -> board[currentRow][nextColumn] = currentSquare;
        this -> board[currentRow][currentColumn] = 0;
        return moveRightWithinRow(currentRow, nextColumn);
      }

      // combine the current square with the next square if they match
      else if (nextSquare == currentSquare) {
        this -> board[currentRow][nextColumn] = currentSquare + nextSquare;
        this -> board[currentRow][currentColumn] = 0;
        nextColumn = nextColumn + 1;
      }

      return moveRightWithinRow(currentRow, nextColumn);

    }

    void moveRight() {

      for (int currentRow = 0; currentRow < 4; currentRow ++) {
        this -> moveRightWithinRow(currentRow, 0);
      }


    };

    void moveUp() {

      for (int x = 0; x < 4; x++) {
        // for column in the game, move everything all the way down recursively
        for (int y = 0; y < 4; y++) {
          int currentSquare = this->board[y][x];
        }
      }

    };
};

int main() {
  // initialize the 2048 game state
	Game game;
  game.insertRandomNumberOntoBoard();


  // initialize I/O library
  initscr();
  noecho();// do not display the user's output

  // main game loop (handles user input of keys)
  char input;
  int cycles = 0;
  while(1)
    {

      game.render(cycles);

      // check if valid moves are available

      // wait indefinitely for input
      timeout(-1);
      input = getch();

      // update the game state based on input
      switch(input) {
        case 'a':
          game.moveLeft();
          break;
        case 's':
          game.moveDown();
          break;
        case 'd':
          game.moveRight();
          break;
        case 'w': 
          game.moveUp();
          break;
        case 'e': // end the game
          break;
        default:
          continue;
      }
      
      // attempt to insert random 2 or 4
      game.insertRandomNumberOntoBoard();

      cycles = cycles + 1;

      refresh(); // Refresh to show changes
    }

  // end the I/O library constructed window
  endwin();

	return 0;
}
