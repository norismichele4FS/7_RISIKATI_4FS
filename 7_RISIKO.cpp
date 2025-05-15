#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include "Territorio.h"
#include "Player.h"

using namespace std;
using namespace sf;

bool sonoConfinanti(vector<pair<string, string>>&, string, string);
void initGiocatori(vector<Player>&);
int winner(Player& giocatore); // -1 = nessuno, 0 = giocatore 1, 1 = giocatore 2, ecc.

int main()
{
	Territorio territori[42] = {
		// Territori del continente america del sud
		Territorio("venezuela","america del sud", 3, Color(67,169,176,255)),
		Territorio("peru", "america del sud", 3, Color(117,189,181,255)),
		Territorio("brasile", "america del sud", 4, Color(140,196,195,255)),
		Territorio("argentina", "america del sud", 2, Color(8,186,196,255)),

		// Territori del continente africa
		Territorio("africa del nord","africa", 6, Color(202,153,78,255)),
		Territorio("egitto", "africa", 4, Color(159,112,46,255)),
		Territorio("congo", "africa", 3, Color(205,175,88,255)),
		Territorio("africa orientale", "africa", 5, Color(135,80,50,255)),
		Territorio("africa del sud", "africa", 3, Color(159,96,44,255)),
		Territorio("madagascar", "africa", 2, Color(205,174,100,255)),

		// Territori del continente europa
		Territorio("europa occidentale","europa", 4, Color(171,111,144,255)),
		Territorio("europa settentrionale", "europa", 5, Color(134,114,152,255)),
		Territorio("europa meridionale", "europa", 6, Color(140,69,124,255)),
		Territorio("ucraina", "europa", 6, Color(101,78,122,255)),
		Territorio("gran bretagna", "europa", 4, Color(127,90,135,255)),
		Territorio("scandinavia", "europa", 4, Color(162,123,154,255)),
		Territorio("islanda", "europa", 3, Color(179,105,137,255)),

		// Territori del continente america del nord
		Territorio("america centrale","america del nord", 3, Color(239,147,33,255)),
		Territorio("stati uniti orientali", "america del nord", 4, Color(245,172,78,255)),
		Territorio("stati uniti occidentali", "america del nord", 4, Color(173,105,50,255)),
		Territorio("alberta", "america del nord", 4, Color(232,190,131,255)),
		Territorio("ontario", "america del nord", 6, Color(229,135,42,255)),
		Territorio("quebec", "america del nord", 3, Color(244,191,79,255)),
		Territorio("alaska", "america del nord", 3, Color(214,173,96,255)),
		Territorio("territori del nord ovest", "america del nord", 4, Color(215,156,104,255)),
		Territorio("groenlandia", "america del nord", 4, Color(224,65,43,255)),

		// Territori del continente oceania
		Territorio("australia occidentale","oceania", 3, Color(237,58,150,255)),
		Territorio("australia orientale", "oceania", 3, Color(245,177,208,255)),
		Territorio("nuova guinea", "oceania", 3, Color(168,33,141,255)),
		Territorio("indonesia", "oceania", 2, Color(235,121,173,255)),

		// Territori del continente asia - colori da sistemare 
		Territorio("giappone","asia", 2, Color(69,181,78,255)),
		Territorio("kamchatka", "asia", 5, Color(186,210,52,255)),
		Territorio("jacuzia", "asia", 3, Color(117,163,85,255)),
		Territorio("siberia", "asia", 5, Color(57,99,50,255)),
		Territorio("urali", "asia", 4, Color(176,213,126,255)),
		Territorio("afghanistan", "asia", 4, Color(134,167,82,255)),
		Territorio("medio oriente", "asia", 6, Color(63,111,53,255)),
		Territorio("india", "asia", 3, Color(168,207,68,255)),
		Territorio("siam", "asia", 3, Color(100,146,83,255)),
		Territorio("cina", "asia", 7, Color(51,140,37,255)),
		Territorio("mongolia", "asia", 5, Color(75,140,64,255)),
		Territorio("cita", "asia", 4, Color(145,173,61,255))
	};
	vector<pair<string, string>> confiniTerritori = {
		// Territori del continente america del sud
		{"venezuela", "peru"},
		{"venezuela", "brasile"},
		{"peru", "brasile"},
		{"peru", "argentina"},
		{"brasile", "argentina"},
		// Territori del continente africa
		{"africa del nord","egitto"},
		{"africa del nord","congo"},
		{"africa del nord","africa orientale"},
		{"congo","africa orientale"},
		{"congo","africa del sud"},
		{"africa orientale","madagascar"},
		{"africa orientale","africa del sud"},
		{"madagascar","africa del sud"},
		{"egitto","africa orientale"},
		// Territori del continente europa
		{"europa occidentale","europa settentrionale"},
		{"europa occidentale","europa meridionale"},
		{"europa occidentale","gran bretagna"},
		{"europa settentrionale","europa meridionale"},
		{"europa settentrionale","scandinavia"},
		{"europa settentrionale","ucraina"},
		{"europa settentrionale","gran bretagna"},
		{"europa meridionale","ucraina"},
		{"gran bretagna","scandinavia"},
		{"scandinavia","islanda"},
		{"islanda","gran bretagna"},
		{"scandinavia","ucraina"},
		// Territori del continente america del nord
		{"america centrale","stati uniti orientali"},
		{"america centrale","stati uniti occidentali"},
		{"stati uniti orientali","stati uniti occidentali"},
		{"stati uniti orientali","ontario"},
		{"stati uniti orientali","quebec"},
		{"stati uniti occidentali","alberta"},
		{"alberta","ontario"},
		{"ontario","quebec"},
		{"quebec","groenlandia"},
		{"groenlandia","territori del nord ovest"},
		{"territori del nord ovest","alaska"},
		{"territori del nord ovest","alberta"},
		{"alberta","alaska"},
		{"ontario","groenlandia"},
		{"ontario","territori del nord ovest"},
		{"ontario","stati uniti occidentali"},
		// Territori del continente oceania
		{"australia occidentale","australia orientale"},
		{"australia occidentale","nuova guinea"},
		{"australia orientale","nuova guinea"},
		{"nuova guinea","indonesia"},
		{"australia occidentale","indonesia"},
		// Territori del continente asia
		{"cina","mongolia"},
		{"cina","siberia"},
		{"cina","urali"},
		{"cina","afghanistan"},
		{"cina","medio oriente"},
		{"cina","india"},
		{"cina","siam"},
		{"siam","india"},
		{"india","medio oriente"},
		{"medio oriente","afghanistan"},
		{"afghanistan","urali"},
		{"siberia","urali"},
		{"siberia","jacuzia"},
		{"siberia","cita"},
		{"siberia","mongolia"},
		{"jacuzia","kamchatka"},
		{"jacuzia","cita"},
		{"cita","mongolia"},
		{"mongolia","kamchatka"},
		{"kamchatka","giappone"},
		{"kamchatka","cita"},
		{"mongolia","giappone"},
		// Territori intercontinentali
		{"groenlandia","islanda"},
		{"alaska","kamchatka"},
		{"america centrale","venezuela"},
		{"brasile","africa del nord"},
		{"africa del nord","europa occidentale"},
		{"africa del nord","europa meridionale"},
		{"egitto","europa meridionale"},
		{"egitto","medio oriente"},
		{"europa meridionale","medio oriente"},
		{"siam","indonesia"},
		{"ucraina","medio oriente"},
		{"ucraina","afghanistan"},
		{"ucraina","urali"}
	};
	string obbiettivi[16] = {
		"Conquistare l’Europa, l’America del Sud e un terzo continente a scelta.",
		"Conquistare l’Asia e l’America del Sud.",
		"Conquistare l’America del Nord e l’Africa.",
		"Conquistare l’America del Nord e l’Oceania.",
		"Conquistare l’Europa e l’Oceania.",
		"Conquistare l’Asia e l’Africa.",
		"Conquistare l’America del Nord e l’America del Sud.",
		"Conquistare l’Europa e l’America del Nord.",
		"Distruggere tutte le armate del giocatore di colore rosso. (Se il giocatore bersaglio viene eliminato da un altro, l’obiettivo si trasforma in \"conquistare 24 territori a tua scelta\")",
		"Distruggere tutte le armate del giocatore di colore blu. (Se il giocatore bersaglio viene eliminato da un altro, l’obiettivo si trasforma in \"conquistare 24 territori a tua scelta\")",
		"Distruggere tutte le armate del giocatore di colore giallo. (Se il giocatore bersaglio viene eliminato da un altro, l’obiettivo si trasforma in \"conquistare 24 territori a tua scelta\")",
		"Distruggere tutte le armate del giocatore di colore verde. (Se il giocatore bersaglio viene eliminato da un altro, l’obiettivo si trasforma in \"conquistare 24 territori a tua scelta\")",
		"Distruggere tutte le armate del giocatore di colore nero. (Se il giocatore bersaglio viene eliminato da un altro, l’obiettivo si trasforma in \"conquistare 24 territori a tua scelta\")",
		"Distruggere tutte le armate del giocatore di colore viola. (Se il giocatore bersaglio viene eliminato da un altro, l’obiettivo si trasforma in \"conquistare 24 territori a tua scelta\")",
		"Conquistare 24 territori a tua scelta.",
		"Conquistare 18 territori con almeno due armate ciascuno."
	};
	Texture mappa_originale;
	Image mappa_modificata;
	Color temp;
	vector<Player> giocatori;

	try {
		if (!mappa_originale.loadFromFile("mappa_originale.png")) {
			throw runtime_error("Errore nel caricamento della mappa originale");
		}

		if (!mappa_modificata.loadFromFile("mappa_modificata.png")) {
			throw runtime_error("Errore nel caricamento della mappa modificata");
		}
	}
	catch (const exception& e) {
		cerr << e.what() << endl;
		return -1;
	}
	initGiocatori(giocatori);

	// Crea lo sprite della mappa originale
	Sprite sprite_mappa_originale(mappa_originale);
	// Crea la finestra
	RenderWindow map_window(VideoMode({ mappa_originale.getSize().x, mappa_originale.getSize().y }), "RISIKO", Style::Titlebar | Style::Resize | Style::Close);

	string temp1 = " ", temp2;

	while (map_window.isOpen())
	{
		while (const optional event = map_window.pollEvent())
		{
			// Close window: exit
			if (event->is<Event::Closed>()) {
				map_window.close();
			}

			// Resize window
			if (event->is<Event::Resized>()) {
				// Resize the view to the new size of the window
				map_window.setSize({ (unsigned int)map_window.getSize().x, (unsigned int)(mappa_modificata.getSize().y * map_window.getSize().x / (double)mappa_modificata.getSize().x) });
			}

			if (event->is<Event::MouseButtonPressed>()) {
				if (Mouse::isButtonPressed(Mouse::Button::Left))
				{
					temp = mappa_modificata.getPixel({ (unsigned int)((Mouse::getPosition().x - map_window.getPosition().x - 8) * ((double)mappa_modificata.getSize().x / map_window.getSize().x)), (unsigned int)((Mouse::getPosition().y - map_window.getPosition().y - 31) * ((double)mappa_modificata.getSize().y / map_window.getSize().y)) });
					//cout << "( " + to_string(Mouse::getPosition().x - map_window.getPosition().x - 8) + " , " + to_string(Mouse::getPosition().y - map_window.getPosition().y - 31) + " )" << endl;
					for (Territorio terri : territori) {
						if (temp == terri.getColore()) {
							//cout << "Territorio: " + territorio.getId() + " - Giocatore: " + to_string(territorio.getIdGiocatore()) + " - Armate: " + to_string(territorio.getNumArmate()) << endl;
							temp1 = temp2;
							temp2 = terri.getId();
							cout << temp1 << "/" << temp2 << endl;
							if (sonoConfinanti(confiniTerritori, temp1, temp2)) { cout << "confinantee" << endl; };
						}
					}
				}
			}
		}

		// Clear screen
		map_window.clear();

		// Draw the sprite
		map_window.draw(sprite_mappa_originale);

		// Update the window
		map_window.display();
	}


}

bool sonoConfinanti(vector<pair<string, string>>& confiniTerritori, string a, string b) {
	for (auto& coppia : confiniTerritori) {
		if ((coppia.first == a && coppia.second == b) ||
			(coppia.first == b && coppia.second == a)) {
			return true;
		}
	}
	return false;
}


