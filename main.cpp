#include <iostream>
#include <limits>
#include "game_state.h"
#include "Player.h"
#include "Game.h"

bool make_ai_move(Game& g, Player p);
bool make_player_move(Game& g, Player p);

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
    char user_prompt_for_ai = 'a';
    char user_prompt_for_turn_order = 'a';
    
    cout << "Welcome to Tic-Tac-Toe!" << endl; 
    tic_tac_toe.print_game();
    while(user_prompt_for_ai != 'n' && user_prompt_for_ai != 'y') {
        cout << "Would you like to play with AI enabled?" << endl;
        cout << "[y/n]" << endl;
        while(!(cin >> user_prompt_for_ai)) {
            cout << "Invalid input. Please try again." << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin >> user_prompt_for_ai;
        }    
        switch(user_prompt_for_ai) {
            case 'y':
                cout << "Would the human like to play 1st or 2nd?" << endl; 
                cout << "1 for first, 2 for second." << endl;
                while(!(cin >> user_prompt_for_turn_order)) {
                    cout << "Invalid input. Please try again." << endl;
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    cin >> user_prompt_for_turn_order;
                }
                switch(user_prompt_for_turn_order) {
                    case '1':
                        player_2.set_ai(true);
                        cout << "AI Enabled!" << endl;
                        break;
                    case '2':
                        player_1.set_ai(true);
                        cout << "AI Enabled!" << endl;
                        break;
                    default:
                        cout << "Didn't understand that, try again." << endl;
                        break;
                }            
                break;
            case 'n':
                break;
            default:
                cout << "Didn't understand that, try again." << endl;
                break;
        }
    }

    while(tic_tac_toe.get_state() == Game::PLAYING) {
        if(turn_counter & 1) {
            cout << "Player 1 (" << player_1.get_symbol() << "), select a "
            "space to play in the form x y" << endl;
            if(player_1.get_ai()) {
                move_made = make_ai_move(tic_tac_toe, player_1);   
            } else {
                move_made = make_player_move(tic_tac_toe, player_1); 
            }
            tic_tac_toe.print_game();
        } else {
            cout << "Player 2 (" << player_2.get_symbol() << "), select a "
            "space to play in the form x,y." << endl;
            if(player_2.get_ai()) {
                move_made = make_ai_move(tic_tac_toe, player_2);   
            } else {
                move_made = make_player_move(tic_tac_toe, player_2); 
            }
            tic_tac_toe.print_game();
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
                cin >> user_prompt_for_quit;
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
                    break;
            }
        }
    }
    return 0;
}

bool make_ai_move(Game& g, Player p) {
    using namespace std;
    int cur_row;
    int cur_col;
    bool move_made = false;
    for(cur_row = 1; cur_row < 4; cur_row++) {
        for(cur_col = 1; cur_col < 4; cur_col++) {
            if(g.get_char_at(cur_row, cur_col) == '*') {
                move_made = g.make_move(p, cur_row, cur_col);
                break;
            }
        }
        if(move_made) {
            break;
        }
    }
    if(!g.has_player_won(p, cur_row, cur_col)) {
         g.is_draw();
    }
    return move_made;
}

bool make_player_move(Game& g, Player p) {
    using namespace std;
    int cur_row;
    int cur_col;
    bool move_made = false;
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
    move_made = g.make_move(p,cur_row, cur_col);   
    if(!g.has_player_won(p, cur_row, cur_col)) {
         g.is_draw();
    }
    return move_made;
}
