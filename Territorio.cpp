#include "Territorio.h"

Territorio::Territorio(string id, string idContinente, int puntiControllo, Color colore, Vector2f posizione) :
	id(id), idContinente(idContinente), numArmate(0), idConquistatore(-1), puntiControllo(puntiControllo), colore(colore), posizione(posizione) {
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
int Territorio::getPuntiControllo() {
	return puntiControllo;
}
Color Territorio::getColore() {
	return colore;
}
bool Territorio::offsNumArmate(int num) { if (numArmate + num >= 0) { numArmate = numArmate + num; return true; } else { return false; } }

void Territorio::setNumArmate(int numArmate) {
	this->numArmate = numArmate;
}

int Territorio::getIdConquistatore() {
	return idConquistatore;
}

void Territorio::setIdConquistatore(int idGiocatore) {
	this->idConquistatore = idGiocatore;
}

Vector2f Territorio::getPosizione() {
	return posizione;
}

