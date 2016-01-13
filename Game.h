#ifndef GAME_H
#define GAME_H

#include "game_state.h"
#include "Player.h"

class Game {
    private:
        char board[][5];
        game_state_t state;
    public:
        Game();
        void init();
        void print_game();
        bool has_player_won(Player p, int row, int col);
        bool is_draw();
        game_state_t get_state();
        bool is_legal_move(int row, int col);
        bool make_move(Player p, int row, int col); 
};

#endif
