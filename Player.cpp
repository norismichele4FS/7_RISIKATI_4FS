#include "Player.h"

Player::Player(string name) : name(name), numArmate(0), carte{ 0, 0, 0, 0 } {}

string Player::getName() { return name; }

int Player::getNumArmate() { return numArmate; }

void Player::setNumArmate(int numArmate) { numArmate = numArmate; }

void Player::addCarta() {}

void Player::removeCarte(int nCav, int nCan, int nFan, int nJol) {
	carte.at(0) -= nCav;
	carte.at(1) -= nCan;
	carte.at(2) -= nFan;
	carte.at(3) -= nJol;
}

array<int, 4> Player::getCarte()
{
	return carte;
}
