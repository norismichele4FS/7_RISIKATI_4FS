#include "Territorio.h"

Territorio::Territorio(string id, string idContinente, int puntiControllo, Color colore) {
	this->id = id;
	this->idContinente = idContinente;
	this->idGiocatore = 0;
	this->numArmate = 0;
	this->puntiControllo = puntiControllo;
	this->colore = colore;
}

string Territorio::getId() {
	return id;
}
string Territorio::getIdContinente() {
	return idContinente;
}
int Territorio::getNumArmate() {
	return numArmate;
}
int Territorio::getIdGiocatore() {
	return idGiocatore;
}
int Territorio::getPuntiControllo() {
	return puntiControllo;
}
Color Territorio::getColore() {
	return colore;
}

void Territorio::setNumArmate(int numArmate) {
	this->numArmate = numArmate;
}
void Territorio::setIdGiocatore(int idGiocatore) {
	this->idGiocatore = idGiocatore;
}

Territorio::~Territorio() {
	// Destructor
}
