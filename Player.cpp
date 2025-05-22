#include "Player.h"

Player::Player(string name, int idGiocatore, int numArmate, string colore, string obbiettivo) : name(name), idGiocatore(idGiocatore), numArmate(numArmate), colore(colore), obbiettivo(obbiettivo), carte{ 0, 0, 0, 0 }, idAbbattitore(-1) {}

string Player::getName() { return name; }

int Player::getNumArmate() { return numArmate; }

bool Player::replaceNumArmate(int num, Territorio& territorio) {
	if (numArmate - num >= 0)
	{
		numArmate = numArmate + num;
		if (territorio.offsNumArmate(num)) {
			return true;
		}
		else {
			return false;
		} //aggiungo o tolgo le armate al territorio
	}
	else { return false; }
}

void Player::setIdAbbattitore(int idAbbattitore) { this->idAbbattitore = idAbbattitore; }

void Player::setObbiettivo(string obbiettivo) { this->obbiettivo = obbiettivo; }

void Player::addCarta() {

}

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

vector<Territorio> Player::getTerritori()
{
	return inventarioTerritori;
}

void Player::addTerritorio(Territorio& territorio)
{
	bool found = false;
	for (int i = 0; i < inventarioTerritori.size(); i++)
	{
		if (inventarioTerritori[i].getId() == territorio.getId())
		{
			found = true;
			break;
		}
	}
	if (!found) {
		inventarioTerritori.push_back(territorio); territorio.setIdConquistatore(idGiocatore);
	}
}

void Player::removeTerritorio(Territorio& territorio)
{
	for (int i = 0; i < inventarioTerritori.size(); i++)
	{
		if (inventarioTerritori.at(i).getId() == territorio.getId())
		{
			inventarioTerritori.erase(inventarioTerritori.begin() + i);
			territorio.setIdConquistatore(-1);
			break;
		}
	}
}