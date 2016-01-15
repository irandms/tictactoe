/*********************************************************************
 * Program Filename: Game.cpp
 * Author: Spencer Moss
 * Date: January 11th, 2015
 * Description: The Tic-Tac-Toe Game class that provides main game
 *              functionality.
 ********************************************************************/
#include <iostream>
#include "Game.h"
#include "Player.h"
#define BLANK_SYMBOL '*'

/*********************************************************************
 * Function: Game()
 * Description: Constructor for the Game class.
 * Parameters: 
 * Pre-Conditions: None
 * Post-Conditions: None
 ********************************************************************/
Game::Game(int size) {
    board = new char*[size];
    board_size = size;
    // Allow a 2D char array to be initialized with user input.
    // Treat char** as char*[], then make char* s members of the board.
    for(int i = 0; i < board_size; i++) {
        char *array_row = new char[board_size];
        board[i] = array_row;
    }
    init();
}

/*********************************************************************
 * Functiion: ~Game()
 * Description: Destructor for the Game class.
 * Parameters: None.
 * Pre-conditions: The Game object exists.
 * Post-conditions: The Game object will no longer exist in memory,
 *                  and the memory allocated for the board is freed.
 ********************************************************************/
Game::~Game() {
    //Free the memory we alloc with new using delete.
    for(int i = 0; i < board_size; i++) {
        char *array_row = board[i];
        delete array_row;
    }
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
    for(int row = 0; row < board_size; row++) {
        for(int col = 0; col < board_size; col++) {
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
    for(int row = 0; row < board_size; row++) {
        for(int col = 0; col < board_size; col++) {
            cout << board[row][col];
            if(col != board_size-1) {
                cout << "|"; // divide tic tac toe boxes
            } else if(row != board_size-1) {
                cout << endl;
                cout << std::string((board_size*2)-1,'-') << endl; 
            } else {
                cout << endl << endl;
            }
        }
    }
}

/********************************************************************
 * Function: has_player_won
 * Description: Checks if a given player has won the game of
 *              Tic-Tac-Toe, given the location of their last move.
 * Parameters: A Player object, the Player who last moved.
 *             The Row and Column they last played in, as integers.
 * Pre-Conditions: The Player object passed was the last Player to 
 *                 use make_move on the Game. Row and Col are the
 *                 location of that last play.
 * Post-Conditions: The game is either won, and the state is changed
 *                  to GAME_OVER, or the game continues.
 *******************************************************************/
bool Game::has_player_won(Player p, int row, int col) {
    using namespace std;
    char player_symbol = p.get_symbol();
    bool row_victory = true;
    bool col_victory = true; 
    bool diag_victory = true;
    bool other_diag_victory = true;
    /*
     * Loop through the length of the board once, checking 
     * all possible plays. Row and Col are -1 because the values
     * passed are "human" values, and start at 1, not 0, as the 
     * array does.
     */ 
    for(int i = 0; i < board_size; i++) {
        if(board[row-1][i] != player_symbol) {              
            row_victory = false;
        }
        if(board[i][col-1] != player_symbol) {
            col_victory = false;
        }
        if(board[i][i] != player_symbol) {
            diag_victory = false;
        }
        if(board[i][board_size-1-i] != player_symbol) {
            other_diag_victory = false;
        }  
    }
    // If any of the above conditions were not proven false, then
    // one of these must be True, meaning the Player won.
    if(row_victory || col_victory || diag_victory || other_diag_victory) {
        cout << "Player '" << p.get_symbol() << "' has won!" << endl;
        state = GAME_OVER;
        return true;
    }
    return false; 
}

/********************************************************************
 * Function: is_draw
 * Description: is_draw returns a true or false statement that 
 *              corresponds with whether or not the game is over, 
 *              and has resulted in a draw.
 * Parameters: None
 * Pre-Conditions: The Game's state is PLAYING and a Player has not
 *                 won.
 * Post-Conditions: The Game's state is GAME_OVER if returns True.
 *                  Otherwise, nothing about the Game has changed.
 *******************************************************************/
bool Game::is_draw() {
    /*
     * Check entire board for a '*' character.
     * If none are present, the board is full;
     * the game has been played out. A draw 
     * may only occur when the board is full.
     */
    for(int row = 0; row < board_size; row++) {
        for(int col = 0; col < board_size; col++) {
            if(board[row][col] == BLANK_SYMBOL) {
                return false;
            }
        }
    }
    std::cout << "The game is a draw!" << std::endl;
    state = GAME_OVER;
    return true;
}

/********************************************************************
 * Function: get_state
 * Description: Returns the state member variable of a Game object.
 * Parameters: None
 * Pre-Conditions: a Game object exists.
 * Post-Conditions: a Game object exists. state is unchanged.
 *******************************************************************/
int Game::get_state() {
    return state;
}

/********************************************************************
 * Function: get_board_size
 * Description: Returns the board_size member var of a Game object.
 * Parameters: None
 * Pre-Conditions: a Game object exists.
 * Post-Conditions: a Game object exists. board_size is unchanged.
 *******************************************************************/
int Game::get_board_size() {
    return board_size;
}

/********************************************************************
 * Function: get_state
 * Description: Returns the state member variable of a Game object.
 * Parameters: None
 * Pre-Conditions: a Game object exists.
 * Post-Conditions: a Game object exists. state is unchanged.
 *******************************************************************/
char Game::get_char_at(int row, int col) {
    return board[row-1][col-1];
}

/********************************************************************
 * Function: is_legal_move
 * Description: Sanitizes input; ensures that the passed row and col
 *              are valid, playable coordinates; verifies that row
 *              and col are within the array bounds of board, and 
 *              that the space row and col represent is not already
 *              played.
 * Parameters: Row and Column as integers to be played on the board.
 * Pre-Conditions: The Game is currently in play.
 * Post-Conditions: The values of row and col must be within the 
 *                  bounds of the board 2D array, and the space 
 *                  must not have the BLANK_SYMBOL char within it.
 *******************************************************************/
bool Game::is_legal_move(int row, int col) {
    using namespace std;
    if((row < 1 || row > board_size) || (col < 1 || col > board_size)) {
        cout << "ERROR: Please ensure your row and col values are "
                "between 1 and " << board_size << "." << endl;
        return false;
    }
    else if(board[row-1][col-1] != BLANK_SYMBOL) {
        cout << "ERROR: This space is already occupied. Please provide "
                "another space to play." << endl;
        return false;
    }
    else {
        return true;                    // safe!
    }
}

/********************************************************************
 * Function: make_move
 * Description: Makes a move on the board member variable by placing
 *              a user's symbol into an 'empty' location.
 * Parameters: the Player making the move, and a location (row & col)
 * Pre-Conditions: The Game is currently in play.
 * Post-Conditions: One, and only one location on the board should
 *                  have it's char changed from EMPTY_SYMBOL to
 *                  the Player p's symbol.
 *******************************************************************/
bool Game::make_move(Player p, int row, int col) {
    if(is_legal_move(row,col)) {
        std::cout << "Player '" << p.get_symbol() << "' plays  ";
        std::cout << "(" << row << "," << col << ")" << std::endl;
        board[row-1][col-1] = p.get_symbol();
        return true;
    }
    return false;
}
