#ifndef GAME_H
#define GAME_H

#include "Player.h"

class Game {
   public:

        enum game_state_t { PLAYING, GAME_OVER };

        Game(int size);
        ~Game();
        void init();
        void print_game();
        bool has_player_won(Player p, int row, int col);
        bool is_draw();
        int get_state();
        int get_board_size();
        char get_char_at(int row, int col);
        bool is_legal_move(int row, int col);
        bool make_move(Player p, int row, int col); 
        bool all_equal(char p, char a, char b, char c);
    private:
        char** board;
        int board_size;
        game_state_t state;
 
};

#endif
