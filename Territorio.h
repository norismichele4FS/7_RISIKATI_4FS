#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Territorio
{
private:
	string id;
	string idContinente;
	int puntiControllo;
	Color colore;

	// 0 = nessun giocatore, 1 = giocatore 1, 2 = giocatore 2, ecc.
	int idGiocatore;
	int numArmate;
public:
	Territorio(string id, string idContinente, int puntiControllo, Color colore);
	string getId();
	string getIdContinente();
	int getIdGiocatore();
	int getNumArmate();
	int getPuntiControllo();
	Color getColore();

	void setNumArmate(int numArmate);
	void setIdGiocatore(int idGiocatore);
	~Territorio();
};

