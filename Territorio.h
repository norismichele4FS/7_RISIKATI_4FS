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
	int numArmate;
	int idConquistatore; // id del giocatore che controlla il territorio
	Vector2f posizione;
	Color colore;
public:
	Territorio(string, string, int, Color, Vector2f);
	string getId();
	string getIdContinente();
	int getNumArmate();
	int getPuntiControllo();
	Color getColore();
	void setNumArmate(int);
	bool offsNumArmate(int);
	void setIdConquistatore(int);
	int getIdConquistatore();
	Vector2f getPosizione();
};

