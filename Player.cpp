#include "Player.h"

Player::Player(string name, int idGiocatore, int numArmate, string colore, string obbiettivo) : name(name), idGiocatore(idGiocatore), numArmate(numArmate), colore(colore), obbiettivo(obbiettivo), carte{ 0, 0, 0, 0 }, idAbbattitore(-1), faseGioco(0) {}

string Player::getName() { return name; }

int Player::getNumArmate() { return numArmate; }

bool Player::placeNumArmate(int num, Territorio& territorio) {

	if (numArmate - num >= 0 && num >= 0)
	{
		numArmate = numArmate - num;
		if (territorio.offsNumArmate(num)) {
			return true;
		}
		else {
			return false;
		}
	}
	else { return false; }
}

void Player::setIdAbbattitore(int idAbbattitore) { this->idAbbattitore = idAbbattitore; }

void Player::setObbiettivo(string obbiettivo) { this->obbiettivo = obbiettivo; }

void Player::addCarta(array<int, 4>& carteDisponibili) {
	int temp; // Variabile temporanea per generare un numero casuale tra 0 e 3  

	do {
		temp = rand() % 4;
	} while (carteDisponibili[temp] <= 0); // Aggiunta di un controllo per garantire che temp sia sempre valido  

	if (temp >= 0 && temp < 4) {
		carteDisponibili[temp] -= 1; // Decrementa il numero di carte disponibili  
		carte[temp]++;
	}
}

bool Player::removeCarte(int nFan, int nCav, int nCan, int nJol) {
	if (carte.at(0) >= nFan && carte.at(1) >= nCav && carte.at(2) >= nCan && carte.at(3) >= nJol) {
		carte.at(0) -= nFan;
		carte.at(1) -= nCav;
		carte.at(2) -= nCan;
		carte.at(3) -= nJol;
		return true;
	}
	else {
		return false;
	}
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

void Player::offsNumArmate(int numArmate) { this->numArmate += numArmate; }

void Player::setFaseGioco(int faseGioco) { this->faseGioco = faseGioco; }

int Player::getFaseGioco() { return faseGioco; }

vector<Territorio>& Player::getTerritori()
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