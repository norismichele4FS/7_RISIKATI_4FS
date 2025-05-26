#include "GameLogic.h"

GameLogic::GameLogic() {}

vector<string> GameLogic::getConquistaContinenti(Player& giocatore) {
	int contEuropa = 7, contAmericaDelSud = 4, contAsia = 12, contAmericaDelNord = 9, contAfrica = 6, contOceania = 4; //conto territori mancanti alla conquista del continente
	vector<string> continentiConquistati;
	string tempIdContinente;

	for (int i = 0; i < giocatore.getTerritori().size(); i++)
	{
		tempIdContinente = giocatore.getTerritori()[i].getIdContinente();
		if (tempIdContinente == "europa")
		{
			contEuropa--;
			if (contEuropa == 0)
			{
				continentiConquistati.push_back(tempIdContinente);
			}
		}
		else if (tempIdContinente == "america del sud")
		{
			contAmericaDelSud--;
			if (contAmericaDelSud == 0)
			{
				continentiConquistati.push_back(tempIdContinente);
			}
		}
		else if (tempIdContinente == "asia")
		{
			contAsia--;
			if (contAsia == 0)
			{
				continentiConquistati.push_back(tempIdContinente);
			}
		}
		else if (tempIdContinente == "america del nord")
		{
			contAmericaDelNord--;
			if (contAmericaDelNord == 0)
			{
				continentiConquistati.push_back(tempIdContinente);
			}
		}
		else if (tempIdContinente == "africa")
		{
			contAfrica--;
			if (contAfrica == 0)
			{
				continentiConquistati.push_back(tempIdContinente);
			}
		}
		else if (tempIdContinente == "oceania")
		{
			contOceania--;
			if (contOceania == 0)
			{
				continentiConquistati.push_back(tempIdContinente);
			}
		}

	}
	return continentiConquistati;
}

bool GameLogic::isTerritorioAmico(vector<Territorio> territori, vector<Player> giocatori, int territorioSelezionato, int turnoGiocatore) {
	return (territori[territorioSelezionato].getIdConquistatore() == giocatori[turnoGiocatore].getIdGiocatore());
}

bool GameLogic::sonoConfinanti(vector<pair<string, string>>& confiniTerritori, string a, string b) {
	for (auto& coppia : confiniTerritori) {
		if ((coppia.first == a && coppia.second == b) ||
			(coppia.first == b && coppia.second == a)) {
			return true;
		}
	}
	return false;
}

int GameLogic::getNumTerritori(Player& giocatore, int nArmateMinime) {
	int tempNumArmate = 0;
	for (int i = 0; i < giocatore.getTerritori().size(); i++)
	{
		if (giocatore.getTerritori()[i].getNumArmate() >= nArmateMinime) {
			tempNumArmate++;
		}
	}
	return tempNumArmate;
}

void GameLogic::initGiocatori(vector<Player>& giocatori, default_random_engine engine)
{
	AllocConsole();

	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);
	freopen_s(&fp, "CONIN$", "r", stdin);

	int numGiocatori;
	string nomeGiocatore;
	int armateIniziali;
	vector <string> coloriGiocatori = { "rosso", "blu", "giallo", "verde", "nero", "viola" };
	vector <string> obbiettivi = {
		"Conquistare l’Europa, l’America del Sud e un terzo continente a scelta.",
		"Conquistare l’Asia e l’America del Sud.",
		"Conquistare l’America del Nord e l’Africa.",
		"Conquistare l’America del Nord e l’Oceania.",
		"Conquistare l’Europa e l’Oceania.",
		"Conquistare l’Asia e l’Africa.",
		"Conquistare l’America del Nord e l’America del Sud.",
		"Conquistare l’Europa e l’America del Nord.",
		"Distruggere tutte le armate del giocatore di colore rosso. (Se le armate non sono presenti nel gioco, se le armate sono possedute dal giocatore che ha l'obiettivo di distruggerle o se l'ultima armata viene distrutta da un altro giocatore, l'obiettivo diventa conquistare 24 territori.)",
		"Distruggere tutte le armate del giocatore di colore blu. (Se le armate non sono presenti nel gioco, se le armate sono possedute dal giocatore che ha l'obiettivo di distruggerle o se l'ultima armata viene distrutta da un altro giocatore, l'obiettivo diventa conquistare 24 territori.)",
		"Distruggere tutte le armate del giocatore di colore giallo. (Se le armate non sono presenti nel gioco, se le armate sono possedute dal giocatore che ha l'obiettivo di distruggerle o se l'ultima armata viene distrutta da un altro giocatore, l'obiettivo diventa conquistare 24 territori.)",
		"Distruggere tutte le armate del giocatore di colore verde. (Se le armate non sono presenti nel gioco, se le armate sono possedute dal giocatore che ha l'obiettivo di distruggerle o se l'ultima armata viene distrutta da un altro giocatore, l'obiettivo diventa conquistare 24 territori.)",
		"Distruggere tutte le armate del giocatore di colore nero. (Se le armate non sono presenti nel gioco, se le armate sono possedute dal giocatore che ha l'obiettivo di distruggerle o se l'ultima armata viene distrutta da un altro giocatore, l'obiettivo diventa conquistare 24 territori.)",
		"Distruggere tutte le armate del giocatore di colore viola. (Se le armate non sono presenti nel gioco, se le armate sono possedute dal giocatore che ha l'obiettivo di distruggerle o se l'ultima armata viene distrutta da un altro giocatore, l'obiettivo diventa conquistare 24 territori.)",
		"Conquistare 24 territori a tua scelta.",
		"Conquistare 18 territori con almeno due armate ciascuno."
	};
	std::shuffle(coloriGiocatori.begin(), coloriGiocatori.end(), engine);
	std::shuffle(obbiettivi.begin(), obbiettivi.end(), engine);

	do
	{

		cout << "inserire il numero di giocatori" << endl;
		cin >> numGiocatori;
		cin.ignore();
		if (numGiocatori < 3 || numGiocatori > 6)
		{
			cout << "numero di giocatori non valido (valido da 3 a 6)" << endl;
		}
	} while (numGiocatori < 3 || numGiocatori > 6);

	armateIniziali = 35 - (numGiocatori - 3) * 5; // calcolo armate iniziali in base al numero di giocatori

	for (int i = 0; i < numGiocatori; i++)
	{
		cout << "inserire il nome del giocatore " << i + 1 << endl;
		getline(cin, nomeGiocatore);
		giocatori.push_back(Player(nomeGiocatore, i, armateIniziali, coloriGiocatori[i], obbiettivi[i])); //idGiocatore corrisponde anche alla posizione nell'array giocatori
	}

	HWND consoleWindow = GetConsoleWindow();
	if (consoleWindow)
	{
		ShowWindow(consoleWindow, SW_HIDE);
		FreeConsole();
	}
}

int GameLogic::checkObbiettivoColore(Player& giocatore, string colore, vector<Player>& giocatori, vector<Territorio> territori) {
	int idTarget = -1;
	for (Player& g : giocatori) {
		if (g.getColore() == colore) {
			idTarget = g.getIdGiocatore();
			break;
		}
	}
	if (idTarget != -1) {
		if (giocatori[idTarget].getIdGiocatore() != giocatore.getIdGiocatore() && giocatori[idTarget].getIdAbbattitore() == giocatore.getIdGiocatore()) {
			return -1;
		}
		else {
			giocatore.setObbiettivo("Conquistare 24 territori a tua scelta.");
			return winner(giocatore, giocatori, territori);
		}
	}
	else {
		return -1;
	}
}

int GameLogic::winner(Player& giocatore, vector<Player>& giocatori, vector<Territorio> territori)
{
	using namespace ranges;
	string obbiettivo = giocatore.getObbiettivo();

	if (obbiettivo == "Conquistare l’Europa, l’America del Sud e un terzo continente a scelta.")
	{
		if (contains(getConquistaContinenti(giocatore), "europa") &&
			contains(getConquistaContinenti(giocatore), "america del sud") &&
			(contains(getConquistaContinenti(giocatore), "asia") ||
				contains(getConquistaContinenti(giocatore), "america del nord") ||
				contains(getConquistaContinenti(giocatore), "africa") ||
				contains(getConquistaContinenti(giocatore), "oceania"))
			)
		{
			return giocatore.getIdGiocatore();
		}
		else
		{
			return -1;
		}
	}
	else if (obbiettivo == "Conquistare l’Asia e l’America del Sud.")
	{
		if (contains(getConquistaContinenti(giocatore), "asia") &&
			contains(getConquistaContinenti(giocatore), "america del sud"))
		{
			return giocatore.getIdGiocatore();
		}
		else
		{
			return -1;
		}
	}
	else if (obbiettivo == "Conquistare l’America del Nord e l’Africa.")
	{
		if (contains(getConquistaContinenti(giocatore), "america del nord") &&
			contains(getConquistaContinenti(giocatore), "africa"))
		{
			return giocatore.getIdGiocatore();
		}
		else
		{
			return -1;
		}

	}
	else if (obbiettivo == "Conquistare l’America del Nord e l’Oceania.")
	{
		if (contains(getConquistaContinenti(giocatore), "america del nord") &&
			contains(getConquistaContinenti(giocatore), "oceania"))
		{
			return giocatore.getIdGiocatore();
		}
		else
		{
			return -1;
		}
	}
	else if (obbiettivo == "Conquistare l’Europa e l’Oceania.")
	{
		if (contains(getConquistaContinenti(giocatore), "europa") &&
			contains(getConquistaContinenti(giocatore), "oceania"))
		{
			return giocatore.getIdGiocatore();
		}
		else
		{
			return -1;
		}
	}
	else if (obbiettivo == "Conquistare l’Asia e l’Africa.")
	{
		if (contains(getConquistaContinenti(giocatore), "asia") &&
			contains(getConquistaContinenti(giocatore), "africa"))
		{
			return giocatore.getIdGiocatore();
		}
		else
		{
			return -1;
		}
	}
	else if (obbiettivo == "Conquistare l’America del Nord e l’America del Sud.")
	{
		if (contains(getConquistaContinenti(giocatore), "america del nord") &&
			contains(getConquistaContinenti(giocatore), "america del sud"))
		{
			return giocatore.getIdGiocatore();
		}
		else
		{
			return -1;
		}
	}
	else if (obbiettivo == "Conquistare l’Europa e l’America del Nord.")
	{
		if (contains(getConquistaContinenti(giocatore), "europa") &&
			contains(getConquistaContinenti(giocatore), "america del nord"))
		{
			return giocatore.getIdGiocatore();
		}
		else
		{
			return -1;
		}
	}
	else if (obbiettivo == "Conquistare l’America del Nord e l’America del Sud.")
	{
		if (contains(getConquistaContinenti(giocatore), "america del nord") &&
			contains(getConquistaContinenti(giocatore), "america del sud"))
		{
			return giocatore.getIdGiocatore();
		}
		else
		{
			return -1;
		}
	}
	else if (obbiettivo == "Conquistare l’Europa e l’America del Nord.")
	{
		if (contains(getConquistaContinenti(giocatore), "europa") &&
			contains(getConquistaContinenti(giocatore), "america del nord"))
		{
			return giocatore.getIdGiocatore();
		}
		else
		{
			return -1;
		}
	}
	else if (obbiettivo == "Distruggere tutte le armate del giocatore di colore rosso. (Se le armate non sono presenti nel gioco, se le armate sono possedute dal giocatore che ha l'obiettivo di distruggerle o se l'ultima armata viene distrutta da un altro giocatore, l'obiettivo diventa conquistare 24 territori.)")
	{
		return checkObbiettivoColore(giocatore, "rosso", giocatori, territori);
	}
	else if (obbiettivo == "Distruggere tutte le armate del giocatore di colore blu. (Se le armate non sono presenti nel gioco, se le armate sono possedute dal giocatore che ha l'obiettivo di distruggerle o se l'ultima armata viene distrutta da un altro giocatore, l'obiettivo diventa conquistare 24 territori.)")
	{
		return checkObbiettivoColore(giocatore, "blu", giocatori, territori);
	}
	else if (obbiettivo == "Distruggere tutte le armate del giocatore di colore giallo. (Se le armate non sono presenti nel gioco, se le armate sono possedute dal giocatore che ha l'obiettivo di distruggerle o se l'ultima armata viene distrutta da un altro giocatore, l'obiettivo diventa conquistare 24 territori.)")
	{
		return checkObbiettivoColore(giocatore, "giallo", giocatori, territori);
	}
	else if (obbiettivo == "Distruggere tutte le armate del giocatore di colore verde. (Se le armate non sono presenti nel gioco, se le armate sono possedute dal giocatore che ha l'obiettivo di distruggerle o se l'ultima armata viene distrutta da un altro giocatore, l'obiettivo diventa conquistare 24 territori.)")
	{
		return checkObbiettivoColore(giocatore, "verde", giocatori, territori);
	}
	else if (obbiettivo == "Distruggere tutte le armate del giocatore di colore nero. (Se le armate non sono presenti nel gioco, se le armate sono possedute dal giocatore che ha l'obiettivo di distruggerle o se l'ultima armata viene distrutta da un altro giocatore, l'obiettivo diventa conquistare 24 territori.)")
	{
		return checkObbiettivoColore(giocatore, "nero", giocatori, territori);
	}
	else if (obbiettivo == "Distruggere tutte le armate del giocatore di colore viola. (Se le armate non sono presenti nel gioco, se le armate sono possedute dal giocatore che ha l'obiettivo di distruggerle o se l'ultima armata viene distrutta da un altro giocatore, l'obiettivo diventa conquistare 24 territori.)")
	{
		return checkObbiettivoColore(giocatore, "viola", giocatori, territori);
	}
	else if (obbiettivo == "Conquistare 24 territori a tua scelta.")
	{
		if (getNumTerritori(giocatore, 1) >= 24)
		{
			return giocatore.getIdGiocatore();
		}
		else
		{
			return -1;
		}
	}
	else if (obbiettivo == "Conquistare 18 territori con almeno due armate ciascuno.")
	{
		if (getNumTerritori(giocatore, 2) >= 18)
		{
			return giocatore.getIdGiocatore();
		}
		else
		{
			return -1;
		}
	}
	else
	{
		return -1;
	}
}

void GameLogic::initTerritori(vector<Player>& giocatori, vector<Territorio>& territori, int turnoGiocatore) {
	int territoriAssegnati = 0;
	int i = turnoGiocatore;

	while (territoriAssegnati < territori.size()) {

		if (territoriAssegnati < territori.size()) {
			giocatori[i].addTerritorio(territori[territoriAssegnati]);
			giocatori[i].placeNumArmate(1, territori[territoriAssegnati]);
			territoriAssegnati++;
		}
		else {
			break;
		}

		if (i == giocatori.size() - 1) {
			i = 0;
		}
		else {
			i++;
		}
	}
}

void GameLogic::calcoloArmate(Player& giocatore) {
	giocatore.offsNumArmate((int)floor(giocatore.getTerritori().size() / 3));
	vector<string> continentiConquistati = getConquistaContinenti(giocatore);
	for (string continente : continentiConquistati) {
		if (continente == "europa") {
			giocatore.offsNumArmate(5);
		}
		else if (continente == "america del sud") {
			giocatore.offsNumArmate(2);
		}
		else if (continente == "asia") {
			giocatore.offsNumArmate(7);
		}
		else if (continente == "america del nord") {
			giocatore.offsNumArmate(5);
		}
		else if (continente == "africa") {
			giocatore.offsNumArmate(3);
		}
		else if (continente == "oceania") {
			giocatore.offsNumArmate(2);
		}
	}
}