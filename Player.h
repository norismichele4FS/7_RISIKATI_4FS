#pragma once
#include <iostream>
#include <array>
using namespace std;

class Player
{
private:
	string name;
	int idGiocatore;
	int numArmate;
	array<int, 4> carte; // 0 = n cavalli, 1 = n cannoni, 2 = n fanti, 3 = n jolly
	string obbiettivo;
	string colore;
	int idAbbattitore; // id del giocatore che ha abbattuto il giocatore corrente
public:
	Player(string, int, int, string, string);
	string getName();
	int getNumArmate();
	void setNumArmate(int);
	void setIdAbbattitore(int);
	void setObbiettivo(string);
	void addCarta();
	void removeCarte(int, int, int, int);
	array<int, 4> getCarte();
	int getIdGiocatore();
	string getObbiettivo();
	string getColore();
	int getIdAbbattitore();
};

