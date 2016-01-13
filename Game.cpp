#include <iostream>
#include "Game.h"
#define TABLE_SIZE 3
#define BLANK_SYMBOL '*'

Game::Game() {
    this->state = PLAYING;
}

void Game::init() {
    for(int row = 0; row < TABLE_SIZE; row++) {
        for(int col = 0; col < TABLE_SIZE; col++) {
            this->board[row][col] = BLANK_SYMBOL;
        }
    }
}

void Game::print_game() {
    using namespace std;
    for(int row = 0; row < TABLE_SIZE; row++) {
        for(int col = 0; col < TABLE_SIZE; col++) {
            cout << this->board[row][col];
            if(col != TABLE_SIZE-1) {
                cout << "|"; // divide 
            } else if(row != TABLE_SIZE-1) {
                cout << endl;
                cout << std::string((TABLE_SIZE*2)-1,'-') << endl;
            } else {
                cout << endl << endl;
            }
        }
    }
}


void Game::check_state() {
    if(true);    
}

game_state_t Game::get_state() {
    return this->state;
}

bool Game::can_move(int row, int col) {
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

void Game::make_move(Player p, int row, int col) {
    if(this->can_move(row,col)) {
        this->board[row-1][col-1] = p.get_symbol();
    }
}
