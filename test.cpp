/********************************************************************
 * Program Filename: test.cpp
 * Author: Spencer Moss
 * Date: January 9th, 2015
 * Description: Rudimentary first steps at testing & validating 
 *              class functionality. 
 *******************************************************************/
#include <iostream>
#include "Player.h"
#include "Game.h"

int main() {
    using namespace std;
    bool move_made = false;

    // Testing Player class and it's methods.
    Player test_player_1('Q');
    cout << "The test_player_1 symbol is " << test_player_1.get_symbol();
    cout << ". Expected Q." << endl;

    Player test_player_2('&');
    cout << "The test_player_2 symbol is " << test_player_2.get_symbol();
    cout << ". Expected &." << endl;
    
    // Testing Game class and it's methods.
    Game test_game(3);
    cout << test_game.get_state() << endl;
    test_game.init();
    cout << test_game.get_state() << endl;
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

    cout << "Has the game ended? Expected: False." << endl;
    cout << (test_game.has_player_won(test_player_1,1,2) || test_game.is_draw()) << endl;
    
    cout << "Completing game using test_player_1" << endl;
    test_game.make_move(test_player_1,1,3);
    test_game.print_game();
    
    cout << "Has test_player_1 won yet? Expected: False." << endl;
    cout << (test_game.has_player_won(test_player_1,1,3) || test_game.is_draw()) << endl;

    test_game.make_move(test_player_1,3,3);
    test_game.print_game();
    
    cout << "Has test_player_1 won yet? Expected: True." << endl;
    cout << (test_game.has_player_won(test_player_1,3,3)) << endl;

    cout << "Resetting the game." << endl;
    test_game.init();
    test_game.print_game();
    
    cout << "Testing win with a Row of &'s." << endl;
    test_game.make_move(test_player_2,1,1);
    test_game.make_move(test_player_2,1,2);
    test_game.make_move(test_player_2,1,3);
    test_game.print_game();
    test_game.has_player_won(test_player_2,1,3);   

    cout << "Resetting the game." << endl;
    test_game.init();
    test_game.print_game();

    cout << "Testing win with a Col of &'s." << endl;
    test_game.make_move(test_player_2,1,1);
    test_game.make_move(test_player_2,2,1);
    test_game.make_move(test_player_2,3,1);
    test_game.print_game();
    test_game.has_player_won(test_player_2,3,1);   

    cout << "Resetting the game." << endl;
    test_game.init();
    test_game.print_game();

    cout << "Testing win with a diagonal of &'s." << endl;
    test_game.make_move(test_player_2,1,1);
    test_game.make_move(test_player_2,2,2);
    test_game.make_move(test_player_2,3,3);
    test_game.print_game();
    test_game.has_player_won(test_player_2,3,3);   

    cout << "Resetting the game." << endl;
    test_game.init();
    test_game.print_game();

    cout << "Testing win with a different diagonal of &'s." << endl;
    test_game.make_move(test_player_2,3,1);
    test_game.make_move(test_player_2,2,2);
    test_game.make_move(test_player_2,1,3);
    test_game.print_game();
    test_game.has_player_won(test_player_2,1,3);   
    cout << "State of game: " << test_game.get_state() << endl;
    cout << "Expected GAME_OVER(1): " << Game::GAME_OVER << endl;

    cout << "Resetting the game." << endl;
    test_game.init();
    test_game.print_game();
    cout << "State of game: " << test_game.get_state() << endl;
    cout << "Expected PLAYING(0): " << Game::PLAYING << endl;
   
    cout << "Testing a draw." << endl;
    test_game.make_move(test_player_1,1,1);
    test_game.make_move(test_player_1,1,2);
    test_game.make_move(test_player_2,1,3);
    test_game.make_move(test_player_2,2,1);
    test_game.make_move(test_player_2,2,2);
    cout << "State of game: " << test_game.get_state() << endl;
    cout << "Expected PLAYING(0): " << Game::PLAYING << endl;
    test_game.make_move(test_player_1,2,3);
    test_game.make_move(test_player_1,3,1);
    test_game.make_move(test_player_1,3,2);
    test_game.make_move(test_player_2,3,3);
    test_game.print_game();
    test_game.has_player_won(test_player_2,1,3);
    test_game.is_draw();
    cout << "State of game: " << test_game.get_state() << endl;
    cout << "Expected GAME_OVER(1): " << Game::GAME_OVER << endl;
  
    cout << "Printing enum values." << endl; 
    cout << "Playing: " << Game::PLAYING << endl;
    cout << "Game over: " << Game::GAME_OVER << endl;   

    

    return 0;
}
