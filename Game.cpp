/*********************************************************************
 * Program Filename: Game.cpp
 * Author: Spencer Moss
 * Date: January 11th, 2015
 * Description: The Tic-Tac-Toe Game class that provides main game
 *              functionality.
 ********************************************************************/

#include <iostream>
#include "Game.h"
#define TABLE_SIZE 3
#define BLANK_SYMBOL '*'

/*********************************************************************
 * Function: Game()
 * Description: Constructor for the Game class.
 * Parameters: None
 * Pre-Conditions: None
 * Post-Conditions: None
 ********************************************************************/
Game::Game() {
    this->state = PLAYING;
}

/*********************************************************************
 * Function: init()
 * Description: Initializes a game of Tic Tac Toe.
 * Parameters: None
 * Pre-Conditions: An instance of the Game class.
 * Post-Conditions: Each index of the board[][] 2D array must have
 *                  a '*' character in it.
 ********************************************************************/
void Game::init() {
    for(int row = 0; row < TABLE_SIZE; row++) {
        for(int col = 0; col < TABLE_SIZE; col++) {
            this->board[row][col] = BLANK_SYMBOL;
        }
    }
}

/*********************************************************************
 * Function: print_game()
 * Description: Print's an ASCII representation of this Game's 
 *              board[][] member 2D array.
 * Pre-Conditions: An instance of the Board class.
 * Post-Conditions: Output has printed to stdout.
 ********************************************************************/
void Game::print_game() {
    using namespace std;
    for(int row = 0; row < TABLE_SIZE; row++) {
        for(int col = 0; col < TABLE_SIZE; col++) {
            cout << this->board[row][col];
            if(col != TABLE_SIZE-1) {
                cout << "|"; // divide tic tac toe boxes
            } else if(row != TABLE_SIZE-1) {
                cout << endl;
                cout << std::string((TABLE_SIZE*2)-1,'-') << endl; 
            } else {
                cout << endl << endl;
            }
        }
    }
}


bool Game::has_player_won(Player p, int row, int col) {
    // Rows
    bool current_row = (this->board[row-1][0] == 
                        this->board[row-1][1] == 
                        this->board[row-1][2]);
    bool current_col = (this->board[0][col-1] ==
                        this->board[1][col-1] ==
                        this->board[2][col-1]);
    bool diagonal_1 =  (this->board[0][0] ==
                        this->board[1][1] ==
                        this->board[2][2]);
    bool diagonal_2 =  (this->board[0][2] ==
                        this->board[1][1] ==
                        this->board[2][0]);
   if(current_row || current_col || diagonal_1 || diagonal_2) {
        std::cout << "Player \'" << p.get_symbol() << "\' has won!";
        this->state = WIN;
        return true;
    }
    return false; 
}

bool Game::is_draw() {
    /*
     * Check entire board for a '*' character.
     * If none are present, the board is full;
     * the game has been played out. A draw 
     * may only occur when the board is full.
     */
    for(int row = 0; row < TABLE_SIZE; row++) {
        for(int col = 0; col < TABLE_SIZE; col++) {
            if(this->board[row][col] == BLANK_SYMBOL) {
                return false;
            }
        }
    }
    this->state = DRAW;
    return true;
}

game_state_t Game::get_state() {
    return this->state;
}

bool Game::is_legal_move(int row, int col) {
    using namespace std;
    if((row < 1 || row > 3) || (col < 1 || col > 3)) {
        cout << "ERROR: Please ensure your row and col values are "
                "between 1 and " << TABLE_SIZE << "." << endl;
        return false;
    }
    else if(this->board[row-1][col-1] != '*') {
        cout << "ERROR: This space is already occupied. Please provide "
                "another space to play." << endl;
        return false;
    }
    else {
        return true;
    }
}

bool Game::make_move(Player p, int row, int col) {
    if(this->is_legal_move(row,col)) {
        std::cout << "(" << row << "," << col << ")" << std::endl;
        this->board[row-1][col-1] = p.get_symbol();
        return true;
    }
    return false;
}
