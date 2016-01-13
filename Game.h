#ifndef GAME_H
#define GAME_H

#include "game_state.h"
#include "Player.h"

class Game {
    private:
        char board[][4];
        game_state_t state;
    public:
        Game();
        void init();
        void print_game();
        void check_state();
        game_state_t get_state();
        bool can_move(int row, int col);
        void make_move(Player p, int row, int col); 
};

#endif
