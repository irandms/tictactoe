#include "Player.h"

Player::Player(char symbol) {
    this->symbol = symbol;
    this->ai = false;
}

char Player::get_symbol() {
    return symbol;
}

bool Player::get_ai() {
    return ai;
}

void Player::set_ai(bool set_val) {
    this->ai = set_val;
}
