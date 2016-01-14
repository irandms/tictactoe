#ifndef PLAYER_H
#define PLAYER_H

class Player {
    private:
        char symbol;
        bool ai;
    public:
        Player(char symbol);
        char get_symbol();
        bool get_ai();
        void set_ai(bool set_val);
};

#endif
