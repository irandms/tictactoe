#include <iostream>
#include "game_state.h"
#include "Player.h"
#include "Game.h"

int main() {
    using namespace std;
    Player player_1('X');
    Player player_2('O');
    Game tic_tac_toe;
    
    cout << tic_tac_toe.get_state() << endl;
    cout << game_state_t::PLAYING << endl;
    cout << "Welcome to Tic-Tac-Toe!" << endl; 
    
    if(tic_tac_toe.get_state() == game_state_t::PLAYING) {
        cout << "hi";
    }    

    return 0;
}
