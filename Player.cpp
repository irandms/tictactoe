/********************************************************************
 * Program Filename: Player.cpp
 * Author: Spencer Moss
 * Date: January 10th, 2015
 * Description: The Player class that provides a player's symbol,
 *              and a flag to set them as AI.
 *******************************************************************/
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
