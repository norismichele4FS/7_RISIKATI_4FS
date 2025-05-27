#pragma once
#include <windows.h>
#include <vector>
#include <array>
#include <random>
#include "Player.h"
#include "Territorio.h"

using namespace std;

class GameLogic
{
public:
	GameLogic();
	bool sonoConfinanti(vector<pair<string, string>>&, string, string);
	int winner(Player&, vector<Player>&, vector<Territorio>); // -1 = nessuno, 0 = giocatore 1, 1 = giocatore 2, ecc.
	vector<string> getConquistaContinenti(Player&);
	int getNumTerritori(Player&, int, vector<Territorio>);
	bool isTerritorioAmico(vector<Territorio>, vector<Player>, int, int);
	void initGiocatori(vector<Player>&, default_random_engine);
	int checkObbiettivoColore(Player&, string, vector<Player>&, vector<Territorio>);
	void initTerritori(vector<Player>&, vector<Territorio>&, int);
	void calcoloArmate(Player&);
};

