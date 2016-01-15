#include <iostream>
#include <limits>
#include "Player.h"
#include "Game.h"

using namespace std;

char get_user_input();
Game prompt_for_board_size();
bool prompt_yes_or_no();
void prompt_for_ai(Player& p1, Player& p2);
bool make_ai_move(Game& g, Player p);
bool make_player_move(Game& g, Player p);

int main() {
    Player player_1('X');
    Player player_2('O');
    int turn_counter = 1;
    bool move_made = false;
    bool user_wants_to_play_again = true;
    
    cout << "Welcome to Tic-Tac-Toe!" << endl; 
    Game tic_tac_toe = prompt_for_board_size();    
    prompt_for_ai(player_1, player_2);    
    tic_tac_toe.print_game();

    while(tic_tac_toe.get_state() == Game::PLAYING) {
        if(turn_counter % 2) {
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
            "space to play in the form x y." << endl;
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
 
        if(tic_tac_toe.get_state() != Game::PLAYING) {
            cout << "Game over! Play again? [y/n]" << endl;
            user_wants_to_play_again = prompt_yes_or_no();
            if(user_wants_to_play_again) {
                cout << "Restarting game!" << endl;
                tic_tac_toe.init();
                turn_counter = 1;
                move_made = false;
                player_1.set_ai(false);
                player_2.set_ai(false);
                prompt_for_ai(player_1, player_2);
                tic_tac_toe.print_game();
            } else {
                cout << "Goodbye, thanks for playing!" << endl;
                return 0;
            }
        }
    }
    return 0;
}

char get_user_input() {
    char user_input;
    while(!(cin >> user_input)) {
        cout << "Invalid input. Please try again." << endl;
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin >> user_input;
    }
    return user_input;
}

Game prompt_for_board_size() {
    int desired_size;
    cout << "What size board would you like? [2/3/4/5]" << endl;
    while(!(cin >> desired_size) || desired_size < 2 || desired_size > 5) {
        cout << "Invalid input. Please try again." << endl;
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin >> desired_size; 
    }
    return Game(desired_size);
}

bool prompt_yes_or_no() {
    while(true) {
        char user_input = get_user_input();
        switch(user_input) {
            case 'y':
                return true;
            case 'n':
                return false;
            default:
                cout << "Invalid input. Please type y or n." << endl;
        }
    }
}
                

void prompt_for_ai(Player& p1, Player& p2) {
    char user_input_turn_char;

    cout << "Would you like to play with AI enabled? [y/n]" << endl;
    bool ai_enabled = prompt_yes_or_no();
    
    if(ai_enabled) {
        cout << "Would the human like to play 1st or 2nd?" << endl; 
        cout << "1 for first, 2 for second." << endl;
        user_input_turn_char = get_user_input();
        switch(user_input_turn_char) {
            case '1':
                p2.set_ai(true);
                cout << "AI Enabled!" << endl;
                break;
            case '2':
                p1.set_ai(true);
                cout << "AI Enabled!" << endl;
                break;
            case 's':
                p1.set_ai(true);
                p2.set_ai(true);
                cout << "AI vs AI enabled!" << endl;
                break;
            default:
                cout << "Invalid input. Please type 1 or 2." << endl;
                break;
        }
    }
}

bool make_ai_move(Game& g, Player p) {
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
