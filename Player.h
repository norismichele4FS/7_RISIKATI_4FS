#pragma once
#include <iostream>
#include <array>
#include <vector>
#include "Territorio.h"

using namespace std;

class Player
{
private:
	string name;
	string obbiettivo;
	string colore;
	int idGiocatore;
	int numArmate;
	int idAbbattitore; // id del giocatore che ha abbattuto il giocatore corrente
	array<int, 4> carte; // 0 = n cavalli, 1 = n cannoni, 2 = n fanti, 3 = n jolly
	vector<Territorio> inventarioTerritori; // vettore di territori posseduti dal giocatore corrente
public:
	Player(string, int, int, string, string);
	string getName();
	int getNumArmate();
	bool replaceNumArmate(int, Territorio&);
	void setIdAbbattitore(int);
	void setObbiettivo(string);
	void addCarta();
	void addTerritorio(Territorio&);
	void removeTerritorio(Territorio&);
	vector<Territorio> getTerritori();
	void removeCarte(int, int, int, int);
	array<int, 4> getCarte();
	int getIdGiocatore();
	string getObbiettivo();
	string getColore();
	int getIdAbbattitore();
};

