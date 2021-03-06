/********************************************************************
 * Program Filename: main.cpp
 * Author: Spencer Moss
 * Date: January 13th, 2015
 *******************************************************************/
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

/********************************************************************
 * Function: The Main Function
 * Description: Creates 2 Player objects and a Game object, and then
 *              plays/simulates a game of Tic-Tac-Toe!
 *******************************************************************/
int main() {
    Player player_1('X');
    Player player_2('O');
    int turn_counter = 1;           // used to determine play order
    bool move_made = false;         // flag to prevent skipping turns
    bool user_wants_to_play_again = true;
    
    cout << "Welcome to Tic-Tac-Toe!" << endl; 
    Game tic_tac_toe = prompt_for_board_size();    
    prompt_for_ai(player_1, player_2);    
    tic_tac_toe.print_game();

    while(tic_tac_toe.get_state() == Game::PLAYING) {
        if(turn_counter % 2) {
            cout << "Player '" << player_1.get_symbol() << "', " 
            "select a space to play in the form x y" << endl;
            if(player_1.get_ai()) {
                move_made = make_ai_move(tic_tac_toe, player_1);   
            } else {
                move_made = make_player_move(tic_tac_toe, player_1); 
            }
            tic_tac_toe.print_game();
        } else {
            cout << "Player '" << player_2.get_symbol() << "', " 
            "select a space to play in the form x y." << endl;
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
 
        // Runs when game is over.
        if(tic_tac_toe.get_state() != Game::PLAYING) {
            cout << "Game over! Play again? [y/n]" << endl;
            user_wants_to_play_again = prompt_yes_or_no();
            if(user_wants_to_play_again) {
                cout << "Restarting game!" << endl;
                tic_tac_toe.init();
                turn_counter = 1;
                move_made = false;
                /*
                 * Since we want to ask the player if they want 
                 * to play with AI again, set both Player objs
                 * to ai = false to prevent AI vs AI games...
                 * ...or type 's' to play AI vs AI games!
                 */
                player_1.set_ai(false);
                player_2.set_ai(false);
                prompt_for_ai(player_1, player_2);
                tic_tac_toe.print_game();
            } else {
                cout << "Goodbye, thanks for playing!" << endl;
            }
        }
    }
    return 0;
}

/*********************************************************************
 * Function: get_user_input
 * Description: Helper function to safely grab characters from user
 *              input. If the user puts anything unsafe, it will
 *              complain until they provide a 'safe' value twice.
 * Pre-Conditions: User has access to stdin.
 * Post-Conditions: Output is a ~mostly~ safe char.
 ********************************************************************/
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

/*********************************************************************
 * Function: prompt_for_board_size
 * Description: Helper function that prompts for a size of Tic-Tac-
 *              Toe board to play, receives user input, and returns
 *              a Game object with a board of the desired size.
 * Pre-Conditions: User has access to stdin.
 * Post-Conditions: A Game object with a specified board size is
 *                  created according to user input.
 ********************************************************************/
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

/********************************************************************
 * Function: prompt_yes_or_no
 * Description: Generic helper that takes gets user input for a
 *              yes or no prompt. Returns True if user says y,
 *              returns False for n.
 * Pre-Condition: User has access to stdin.
 * Post-Condition: Returns True for Yes, False for No.
 *******************************************************************/
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
                
/*********************************************************************
 * Function: prompt_for_ai
 * Description: Displays a y/n prompt for enabling AI, along with
 *              which turn the player wants to take as human.
 *              Enables AI as desired. May use secret 's' case to
 *              play an AI vs AI game (not very exciting.)
 * Parameters: References to two Player objects, so that we may
 *             set their AI flags to True if desired.
 * Pre-Conditions: Neither Player object referenced should have
 *                 their AI flag set to True before this runs.
 * Post-Conditions: None, one, or all Player objects referenced
 *                  have their AI flags set as true.
 ********************************************************************/
void prompt_for_ai(Player& p1, Player& p2) {
    char user_input_turn_char;

    cout << "Would you like to play with AI enabled? [y/n]" << endl;
    bool ai_enabled = prompt_yes_or_no();
    bool input_is_valid = false;        // used due to lack of return
    
    if(ai_enabled) {
        while(!input_is_valid) {
            cout << "Would the human like to play 1st or 2nd?" << endl;
            cout << "1 for first, 2 for second." << endl;
            user_input_turn_char = get_user_input();
            switch(user_input_turn_char) {
                case '1':
                    p2.set_ai(true);
                    cout << "AI Enabled!" << endl;
                    input_is_valid = true;
                    break;
                case '2':
                    p1.set_ai(true);
                    cout << "AI Enabled!" << endl;
                    input_is_valid = true;
                    break;
                case 's':
                    p1.set_ai(true);
                    p2.set_ai(true);
                    cout << "AI vs AI enabled!" << endl;
                    input_is_valid = true;
                    break;
                default:
                    cout << "Invalid input. Please type 1 or 2." << endl;
                    break;
            }
        }
    }
}

/********************************************************************
 * Function: make_ai_move
 * Description: Helper function that calls make_move using a very...
 *              ... rudimentary AI.
 * Parameters: A Game reference, so that we may change the board
 *             using Game's make_move member function, and a Player 
 *             p who has their AI flag set as True.
 * Pre-Conditions: the Game's state is Playing, and the Player's 
 *                 AI flag is True.
 * Post-Conditions: The AI flag remains True.
 *******************************************************************/
bool make_ai_move(Game& g, Player p) {
    int cur_row;
    int cur_col;
    bool move_made = false;
    // Literally play first spot from left to right, top to bottom.
    for(cur_row = 1; cur_row <= g.get_board_size(); cur_row++) {
        for(cur_col = 1; cur_col <= g.get_board_size(); cur_col++) {
            if(g.get_char_at(cur_row, cur_col) == '*') {
                move_made = g.make_move(p, cur_row, cur_col);
                break;
            }
        }
        // prevents AI from playing all empty spaces...
        if(move_made) {
            break;
        }
    }
    if(!g.has_player_won(p, cur_row, cur_col)) {
         g.is_draw();
    }
    return move_made;
}

/********************************************************************
 * Function: make_player_move
 * Description: Allows a human player to make a move; takes in
 *              2 integers as input coordinates, passes them to
 *              make_move, which validates the coordinates as valid
 *              using is_legal_move.
 * Parameters: A Game reference, so that we may change the board
 *             using Game's make_move member function, and a Player 
 *             p who is making the move.
 * Pre-Conditions: the Game's state is Playing, and the Player's 
 *                 AI flag is False.
 * Post-Conditions: The AI flag remains False.
 *******************************************************************/
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
    /* 
     * Check for victory only if move was made.
     * Reduces unnecessary computation & prevents segfaults.
     * move_made will only be True if cur_col and cur_col are
     * safe and within board array bounds!
     */
    if(move_made) {
        if(!g.has_player_won(p, cur_row, cur_col)) {
            g.is_draw();
        }
    }
    return move_made;
}
