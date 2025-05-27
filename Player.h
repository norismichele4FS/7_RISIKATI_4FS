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
	array<int, 4> carte;
	vector<Territorio> inventarioTerritori; // vettore di territori posseduti dal giocatore corrente
	int faseGioco; // 0 = schieramento iniziale , 1 = schieramento, 2 = attacco o spostamento, 3 = fine turno

public:
	Player(string, int, int, string, string);
	string getName();
	int getNumArmate();
	bool placeNumArmate(int, Territorio&);
	void setIdAbbattitore(int);
	void setObbiettivo(string);
	void addCarta(array<int, 4>&);
	void addTerritorio(Territorio&);
	void removeTerritorio(Territorio&);
	vector<Territorio>& getTerritori();
	bool removeCarte(int, int, int, int);
	array<int, 4> getCarte();
	int getIdGiocatore();
	string getObbiettivo();
	string getColore();
	int getIdAbbattitore();
	void offsNumArmate(int);
	int getFaseGioco();
	void setFaseGioco(int);
};

