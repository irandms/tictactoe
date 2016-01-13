#include <iostream>
#include "game_state.h"
#include "Player.h"
#include "Game.h"

int main() {
    using namespace std;

    // Testing Player class and it's methods.
    Player test_player_1('Q');
    cout << "The test_player_1 symbol is " << test_player_1.get_symbol();
    cout << ". Expected Q." << endl;

    Player test_player_2('&');
    cout << "The test_player_2 symbol is " << test_player_2.get_symbol();
    cout << ". Expected &." << endl;
    
    // Testing Game class and it's methods.
    Game test_game;
    test_game.init();
    test_game.print_game();

    cout << "Testing a valid move at 2,3." << endl;
    test_game.make_move(test_player_1,2,3);
    test_game.print_game();

    cout << "Testing a valid move at 1,1." << endl;
    test_game.make_move(test_player_2,1,1);
    test_game.print_game();

    cout << "Testing a valid move at 1,2." << endl;
    test_game.make_move(test_player_1,1,2);
    test_game.print_game(); 

    cout << "Testing an invalid move at 0,4; out of bounds." << endl;
    test_game.make_move(test_player_2,0,4);
    test_game.print_game();

    cout << "Testing an invalid move at 1,70; out of bounds." << endl;
    test_game.make_move(test_player_2,1,70);
    test_game.print_game();

    cout << "Testing an invalid move at 1,2; already played." << endl;
    test_game.make_move(test_player_1,1,2);
    test_game.print_game();

    cout << "Testing an invalid move at 2,3; already played." << endl;
    test_game.make_move(test_player_2,2,3);
    test_game.print_game();

    return 0;
}
