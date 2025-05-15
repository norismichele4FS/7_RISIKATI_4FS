#pragma once
#include <iostream>
#include <array>
using namespace std;

class Player
{
private:
	string name;
	int numArmate;
	array<int, 4> carte; // 0 = n cavalli, 1 = n cannoni, 2 = n fanti, 3 = n jolly
	string obbiettivo;
public:
	Player(string, int);
	string getName();
	int getNumArmate();
	void setNumArmate(int);
	void addCarta();
	void removeCarte(int, int, int, int);
	array<int, 4> getCarte();
	string getObbiettivo();
};

