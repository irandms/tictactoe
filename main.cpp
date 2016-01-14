#include <iostream>
#include <limits>
#include "game_state.h"
#include "Player.h"
#include "Game.h"

int main() {
    using namespace std;
    Player player_1('X');
    Player player_2('O');
    Game tic_tac_toe;
    int turn_counter = 1;
    int cur_row = -1;
    int cur_col = -1;
    bool move_made = false;
    char user_prompt_for_quit = 'a';
    
    cout << "Welcome to Tic-Tac-Toe!" << endl; 
    tic_tac_toe.print_game();

    while(tic_tac_toe.get_state() == Game::PLAYING) {
        if(turn_counter & 1) {
            cout << "Player 1 (" << player_1.get_symbol() << "), select a "
            "space to play in the form x y" << endl;
            /* Prevent the program from crashing upon invalid input.
             * we use the fail bit of cin to enter the while loop.
             *
             * cin.clear() clears that fail bit so that we may take
             * more user input
             *
             * cin.ignore() ignores the entire existing buffer.
             * using the numeric limit for the streamsize is safer/
             * better practice than simply ignoring the last 1000 or so
             * characters.
             * 
             * BUG: User must enter their 'fixed' combo of ints a second
             * time. Not familiar enough with C++ to understand why.
             */ 
            while(!(cin >> cur_row >> cur_col)) {
                cout << "Invalid input. Please try again." << endl;
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cin >> cur_row; 
                cin >> cur_col;
            }
            move_made = tic_tac_toe.make_move(player_1,cur_row, cur_col);
            tic_tac_toe.print_game();
            if(!tic_tac_toe.has_player_won(player_1, cur_row, cur_col)) {
                tic_tac_toe.is_draw();
            } 
        } else {
            cout << "Player 2 (" << player_2.get_symbol() << "), select a "
            "space to play in the form x,y." << endl;
            while(!(cin >> cur_row >> cur_col)) {
                cout << "Invalid input. Please try again." << endl;
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cin >> cur_row; 
                cin >> cur_col;
            }
            move_made = tic_tac_toe.make_move(player_2,cur_row, cur_col);
            tic_tac_toe.print_game();
            if(!tic_tac_toe.has_player_won(player_2, cur_row, cur_col)) {
                tic_tac_toe.is_draw();
            } 
        }

        if(move_made) {
            move_made = false;
            turn_counter++;
        }

        while(tic_tac_toe.get_state() != Game::PLAYING) {
            cout << "Game over! Play again? [y/n]" << endl;
            while(!(cin >> user_prompt_for_quit)) {
                cout << "Invalid input. Please try again." << endl;
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cin >> cur_row; 
                cin >> cur_col;
            }    
            switch(user_prompt_for_quit) {
                case 'y':
                    cout << "Restarting game!" << endl;
                    tic_tac_toe.init();
                    tic_tac_toe.print_game();
                    turn_counter = 1;
                    cur_row = -1;
                    cur_col = -1;
                    move_made = false;
                    break;
                case 'n':
                    cout << "Goodbye, thanks for playing!" << endl;
                    return 0;
                default:
                    cout << "Didn't understand that, try again." << endl;
            }
        }
    }
    return 0;
}
