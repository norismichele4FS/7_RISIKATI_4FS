#include "Player.h"

Player::Player(string name, int idGiocatore, int numArmate, string colore, string obbiettivo) : name(name), idGiocatore(idGiocatore), numArmate(numArmate), colore(colore), obbiettivo(obbiettivo), carte{ 0, 0, 0, 0 }, idAbbattitore(-1) {}

string Player::getName() { return name; }

int Player::getNumArmate() { return numArmate; }

void Player::setNumArmate(int numArmate) { numArmate = numArmate; }

void Player::setIdAbbattitore(int idAbbattitore) { idAbbattitore = idAbbattitore; }

void Player::setObbiettivo(string obbiettivo) { obbiettivo = obbiettivo; }

void Player::addCarta() {}

void Player::removeCarte(int nCav, int nCan, int nFan, int nJol) {
	carte.at(0) -= nCav;
	carte.at(1) -= nCan;
	carte.at(2) -= nFan;
	carte.at(3) -= nJol;
}

int Player::getIdGiocatore()
{
	return idGiocatore;
}

array<int, 4> Player::getCarte()
{
	return carte;
}

string Player::getObbiettivo()
{
	return obbiettivo;
}

string Player::getColore()
{
	return colore;
}

int Player::getIdAbbattitore()
{
	return idAbbattitore;
}