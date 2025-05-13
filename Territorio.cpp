#include "Territorio.h"

Territorio::Territorio(string id, string idContinente, int puntiControllo, Color colore) :
	id(id), idContinente(idContinente), idGiocatore(-1), numArmate(0), puntiControllo(puntiControllo), colore(colore) {
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
	numArmate = numArmate;
}
void Territorio::setIdGiocatore(int idGiocatore) {
	idGiocatore = idGiocatore;
}
