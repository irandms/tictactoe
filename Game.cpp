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
    init();
}

/*********************************************************************
 * Function: init()
 * Description: Initializes a game of Tic Tac Toe.
 * Parameters: None
 * Pre-Conditions: An instance of the Game class.
 * Post-Conditions: Each index of the board[][] 2D array must have
 *                  a '*' character in it.
 *                  Additionally, the state enum will be set to 
 *                  PLAYING.
 ********************************************************************/
void Game::init() {
    for(int row = 0; row < TABLE_SIZE; row++) {
        for(int col = 0; col < TABLE_SIZE; col++) {
            board[row][col] = BLANK_SYMBOL;
        }
    }
    state = PLAYING;
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
            cout << board[row][col];
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
    char player_symbol = p.get_symbol();
    bool current_row = all_equal(player_symbol,
                                 board[row-1][0], 
                                 board[row-1][1], 
                                 board[row-1][2]);
    bool current_col = all_equal(player_symbol,
                                 board[0][col-1],
                                 board[1][col-1],
                                 board[2][col-1]);
    bool diagonal_1 =  all_equal(player_symbol,
                                 board[0][0],
                                 board[1][1],
                                 board[2][2]);
    bool diagonal_2 =  all_equal(player_symbol,
                                 board[0][2],
                                 board[1][1],
                                 board[2][0]);
    if(current_row || current_col || diagonal_1 || diagonal_2) {
        std::cout << "Player '" << p.get_symbol() << "' has won!";
        std::cout << std::endl;
        state = GAME_OVER;
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
            if(board[row][col] == BLANK_SYMBOL) {
                return false;
            }
        }
    }
    std::cout << "The game is a draw!" << std::endl;
    state = GAME_OVER;
    return true;
}

int Game::get_state() {
    return state;
}

char Game::get_char_at(int row, int col) {
    return board[row-1][col-1];
}

bool Game::is_legal_move(int row, int col) {
    using namespace std;
    if((row < 1 || row > 3) || (col < 1 || col > 3)) {
        cout << "ERROR: Please ensure your row and col values are "
                "between 1 and " << TABLE_SIZE << "." << endl;
        return false;
    }
    else if(board[row-1][col-1] != BLANK_SYMBOL) {
        cout << "ERROR: This space is already occupied. Please provide "
                "another space to play." << endl;
        return false;
    }
    else {
        return true;
    }
}

bool Game::make_move(Player p, int row, int col) {
    if(is_legal_move(row,col)) {
        std::cout << "(" << row << "," << col << ")" << std::endl;
        board[row-1][col-1] = p.get_symbol();
        return true;
    }
    return false;
}

bool Game::all_equal(char p, char a, char b, char c) {
    return (p == a && a == b && b == c);
}
