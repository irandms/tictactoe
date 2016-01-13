#include <iostream>
#include "game_state.h"
#include "Player.h"
#include "Game.h"

int main() {
    using namespace std;
    Player player_1('X');
    Player player_2('O');
    Game tic_tac_toe;
    
    cout << tic_tac_toe.state;
    cout << "Welcome to Tic-Tac-Toe!" << endl;
    

    return 0;
}
