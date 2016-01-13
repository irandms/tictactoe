#include "Player.h"

Player::Player(char symbol) {
    this->symbol = symbol;
}

char Player::get_symbol() {
    return symbol;
}
