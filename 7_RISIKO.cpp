#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <ranges>
#include <algorithm> // per shuffle
#include <random>    // per default_random_engine
#include <chrono>    // per seed del random engine

#include <windows.h>
#include <sal.h> // Include SAL annotations header
#include <SFML/Window/WindowHandle.hpp>

#include "imgui.h"
#include "imgui-SFML.h"

#include "Territorio.h"
#include "Player.h"
#include "resource.h"


using namespace std;
using namespace sf;

//TO DO LIST

/*
	1. controllare prototipi funzioni + coincidenza con dichiarazioni
	2. forse creare classe logic per suddividere le funzioni in modo piu' ordinato --> non urgente
*/

bool sonoConfinanti(vector<pair<string, string>>&, string, string);
int winner(Player&, vector<Player>&, vector<Territorio>); // -1 = nessuno, 0 = giocatore 1, 1 = giocatore 2, ecc.
vector<string> getConquistaContinenti(Player&);
int getNumTerritori(Player&, int);
Vector2u getMousePos(RenderWindow&, Sprite&, Image&);
bool isTerritorioAmico(vector<Territorio>, vector<Player>, int, int);
void initGiocatori(vector<Player>&, default_random_engine);
void initTerritori(vector<Player>&, vector<Territorio>&, int);
bool Attacco(vector<Territorio>&, vector<Player>&, array<int, 4>&);
bool Sposta(int, vector<Territorio>&);
void calcoloArmate(Player& giocatore);

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	srand(static_cast<unsigned int>(time(0)));
	size_t seed = chrono::system_clock::now().time_since_epoch().count();
	default_random_engine engine(static_cast<unsigned int>(seed));
	vector<Territorio> territori = {
		// Territori del continente america del sud
		Territorio("venezuela","america del sud", 3, Color(67,169,176,255), {0.177163f , 0.571429f}),
		Territorio("peru", "america del sud", 3, Color(117,189,181,255), {0.075247f , 0.668722f}),
		Territorio("brasile", "america del sud", 4, Color(140,196,195,255), {0.222883f , 0.698869f}),
		Territorio("argentina", "america del sud", 2, Color(8,186,196,255), {0.113346f , 0.870161f}),

		// Territori del continente africa
		Territorio("africa del nord","africa", 6, Color(202,153,78,255), {0.422906f , 0.672833f}),
		Territorio("egitto", "africa", 4, Color(159,112,46,255), {0.479103f , 0.624872f}),
		Territorio("congo", "africa", 3, Color(205,175,88,255), {0.482913f , 0.779719f}),
		Territorio("africa orientale", "africa", 5, Color(135,80,50,255), {0.527680f , 0.755053f}),
		Territorio("africa del sud", "africa", 3, Color(159,96,44,255), {0.498152f , 0.887975f}),
		Territorio("madagascar", "africa", 2, Color(205,174,100,255), {0.586734f , 0.823570f}),

		// Territori del continente europa
		Territorio("europa occidentale","europa", 4, Color(171,111,144,255), {0.394331f , 0.431655f}),
		Territorio("europa settentrionale", "europa", 5, Color(134,114,152,255), {0.499105f , 0.360397f}),
		Territorio("europa meridionale", "europa", 6, Color(140,69,124,255), {0.505772f , 0.468654f}),
		Territorio("ucraina", "europa", 6, Color(101,78,122,255), {0.552444f , 0.323398f}),
		Territorio("gran bretagna", "europa", 4, Color(127,90,135,255), {0.395283f , 0.356286f}),
		Territorio("scandinavia", "europa", 4, Color(162,123,154,255), {0.503867f , 0.219253f}),
		Territorio("islanda", "europa", 3, Color(179,105,137,255), {0.438145f , 0.179514f}),

		// Territori del continente america del nord
		Territorio("america centrale","america del nord", 3, Color(239,147,33,255), {0.083819f , 0.482357f}),
		Territorio("stati uniti orientali", "america del nord", 4, Color(245,172,78,255), {0.176211f , 0.385063f}),
		Territorio("stati uniti occidentali", "america del nord", 4, Color(173,105,50,255), {0.134301f , 0.357657f}),
		Territorio("alberta", "america del nord", 4, Color(232,190,131,255), {0.099059f , 0.268585f}),
		Territorio("ontario", "america del nord", 6, Color(229,135,42,255), {0.190498f , 0.285029f}),
		Territorio("quebec", "america del nord", 3, Color(244,191,79,255), {0.254315f , 0.360397f}),
		Territorio("alaska", "america del nord", 3, Color(214,173,96,255), {0.109536f , 0.127441f}),
		Territorio("territori del nord ovest", "america del nord", 4, Color(215,156,104,255), {0.191451f , 0.226105f}),
		Territorio("groenlandia", "america del nord", 4, Color(224,65,43,255), {0.358136f , 0.157588f}),

		// Territori del continente oceania
		Territorio("australia occidentale","oceania", 3, Color(237,58,150,255), {0.812474f , 0.863309f}),
		Territorio("australia orientale", "oceania", 3, Color(245,177,208,255), {0.888673f , 0.920863f}),
		Territorio("nuova guinea", "oceania", 3, Color(168,33,141,255), {0.949633f , 0.741350f}),
		Territorio("indonesia", "oceania", 2, Color(235,121,173,255), {0.844859f , 0.645427f}),

		// Territori del continente asia - colori da sistemare 
		Territorio("giappone","asia", 2, Color(69,181,78,255), {0.893436f , 0.265844f}),
		Territorio("kamchatka", "asia", 5, Color(186,210,52,255), {0.794377f , 0.232956f}),
		Territorio("jacuzia", "asia", 3, Color(117,163,85,255), {0.720083f , 0.119219f}),
		Territorio("siberia", "asia", 5, Color(57,99,50,255), {0.662933f , 0.228845f}),
		Territorio("urali", "asia", 4, Color(176,213,126,255), {0.638168f , 0.322028f}),
		Territorio("afghanistan", "asia", 4, Color(134,167,82,255), {0.667696f , 0.424803f}),
		Territorio("medio oriente", "asia", 6, Color(63,111,53,255), {0.620071f , 0.627612f}),
		Territorio("india", "asia", 3, Color(168,207,68,255), {0.725797f , 0.619390f}),
		Territorio("siam", "asia", 3, Color(100,146,83,255), {0.821999f , 0.553614f}),
		Territorio("cina", "asia", 7, Color(51,140,37,255), {0.823904f , 0.427544f}),
		Territorio("mongolia", "asia", 5, Color(75,140,64,255), {0.738180f , 0.343953f}),
		Territorio("cita", "asia", 4, Color(145,173,61,255), {0.703890f , 0.261733f})
	};
	std::shuffle(territori.begin(), territori.end(), engine);
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
	vector<Player> giocatori;
	array<int, 4> carteDisponibili = { 14, 14, 14, 2 }; //numero di carte per simbolo disponibili - 14 per i 3 simboli e 2 per il jolly (fan, cav, can, jol)
	int territorioSelezionato = -1;
	int numArmateSpostamento = 1;
	static const char* items[]{ "Fante","Cavallo","Cannone", "Jolly" };
	static int selectedItem[3] = { 0, 0, 0 };
	int sommaCarte[4] = { 0, 0, 0, 0 }; // per il calcolo delle carte da utilizzare per lo schieramento

	Font font("arial.ttf");
	Image mappa_modificata;
	Texture mappa_originale;
	Texture tankTexture;
	if (!mappa_originale.loadFromFile("mappa_originale.png")) {}
	if (!mappa_modificata.loadFromFile("mappa_modificata.png")) {}
	if (!tankTexture.loadFromFile("tank.png")) {}
	Sprite sprite_mappa_originale(mappa_originale);

	vector<Sprite> sprite_tanks;
	for (int i = 0; i < territori.size(); i++) {
		sprite_tanks.push_back(Sprite(tankTexture));
	}

	Color temp;

	initGiocatori(giocatori, engine);
	int turnoGiocatore = rand() % giocatori.size();
	initTerritori(giocatori, territori, turnoGiocatore);
	int turnoIniziale = turnoGiocatore; // Salva il turno iniziale per il reset del turno


	// Crea lo sprite della mappa originale

	float imageWindowsRatio = 0.25f;
	float scaleRatioY = (float)mappa_originale.getSize().y / mappa_originale.getSize().x;
	unsigned int originalWidth = 1400;

	unsigned int original_map_x = mappa_originale.getSize().x;
	unsigned int original_map_y = mappa_originale.getSize().y;

	// Crea la finestra
	RenderWindow map_window(VideoMode({ originalWidth, (unsigned int)(originalWidth * scaleRatioY) }), "RISIKO", Style::Titlebar | Style::Resize | Style::Close);

	View view = View(FloatRect({ 0.f, 0.f }, { static_cast<float>(map_window.getSize().x), static_cast<float>(map_window.getSize().y) }));

	VideoMode desktop = VideoMode::getDesktopMode();
	// Center the window on the screen
	map_window.setPosition({ (int)(desktop.size.x - map_window.getSize().x) / 2, 0 });

	// Get native window handle
	HWND hwnd = (HWND)map_window.getNativeHandle();
	// Bring window to front
	SetForegroundWindow(hwnd);
	SetFocus(hwnd);
	SetActiveWindow(hwnd);

	ImVec2 playerPanelSize = ImVec2(
		map_window.getSize().x * imageWindowsRatio,
		map_window.getSize().y * (1.0f - imageWindowsRatio)
	);

	ImVec2 inputPanelSize = ImVec2(
		(map_window.getSize().x - playerPanelSize.x) / 2.0f,
		map_window.getSize().y * imageWindowsRatio
	);

	ImVec2 outputPanelSize = ImVec2(
		(map_window.getSize().x - playerPanelSize.x) / 2.0f,
		map_window.getSize().y * imageWindowsRatio
	);

	ImVec2 infoPanelSize = ImVec2(
		playerPanelSize.x,
		map_window.getSize().y * imageWindowsRatio
	);

	// Compute scale to fit the available area 
	float scaleX = (map_window.getSize().x - playerPanelSize.x) / original_map_x;
	float scaleY = (map_window.getSize().y - inputPanelSize.y) / original_map_y;
	float finalScale = min(scaleX, scaleY);
	sprite_mappa_originale.setScale({ finalScale, finalScale });// Apply scale to sprite

	if (!ImGui::SFML::Init(map_window)) {
		//throw Exception("Errore durante l'inizializzazione di ImGui::SFML");
	}

	ImGuiStyle& style = ImGui::GetStyle();
	// Disabilita evidenziazione al click e hover sulla finestra
	style.Colors[ImGuiCol_TitleBg] = style.Colors[ImGuiCol_TitleBgActive];

	Clock deltaClock;

	while (map_window.isOpen())
	{
		while (const auto event = map_window.pollEvent())
		{
			ImGui::SFML::ProcessEvent(map_window, *event);
			// Close window: exit
			if (event->is<Event::Closed>()) {
				map_window.close();
			}

			// Resize window
			if (event->is<Event::Resized>()) {
				// Resize the view to the new size of the window keeping the aspect ratio
				map_window.setSize({ (unsigned int)map_window.getSize().x, (unsigned int)(map_window.getSize().x * scaleRatioY) });

				playerPanelSize = ImVec2(
					map_window.getSize().x * imageWindowsRatio,
					map_window.getSize().y * (1.0f - imageWindowsRatio)
				);

				inputPanelSize = ImVec2(
					(map_window.getSize().x - playerPanelSize.x) / 2.0f,
					map_window.getSize().y * imageWindowsRatio
				);

				outputPanelSize = ImVec2(
					(map_window.getSize().x - playerPanelSize.x) / 2.0f,
					map_window.getSize().y * imageWindowsRatio
				);

				infoPanelSize = ImVec2(
					playerPanelSize.x,
					map_window.getSize().y * imageWindowsRatio
				);

				scaleX = (map_window.getSize().x - playerPanelSize.x) / original_map_x;
				scaleY = (map_window.getSize().y - inputPanelSize.y) / original_map_y;
				finalScale = min(scaleX, scaleY);
				sprite_mappa_originale.setScale({ finalScale, finalScale });// Apply scale to sprite

				view = View(FloatRect({ 0.f, 0.f }, { static_cast<float>(map_window.getSize().x), static_cast<float>(map_window.getSize().y) }));
			}

			if (event->is<Event::MouseButtonPressed>()) {
				if (Mouse::isButtonPressed(Mouse::Button::Left))
				{

					//funzione di calcolo delle coordinate per modificare posizione carri armati nel vettore territori
					//windowOutput = to_string((float)Mouse::getPosition(map_window).x / sprite_mappa_originale.getGlobalBounds().size.x) + "f , " + to_string((float)Mouse::getPosition(map_window).y / sprite_mappa_originale.getGlobalBounds().size.y) + "f";

					temp = mappa_modificata.getPixel(getMousePos(map_window, sprite_mappa_originale, mappa_modificata));
					for (int i = 0; i < territori.size(); i++) {
						if (temp == territori[i].getColore()) {
							territorioSelezionato = i;
						}
					}
				}
			}

		}


		///creazione game loop a fasi di gioco per giocatore

		if (winner(giocatori[turnoGiocatore], giocatori, territori) == -1) {
			switch (giocatori[turnoGiocatore].getFaseGioco()) {

			case 0:
				windowOutputMessage = "Schierare tutte le armate iniziali";
				if (giocatori[turnoGiocatore].getNumArmate() == 0) {
					if (turnoGiocatore < giocatori.size() - 1) {
						turnoGiocatore++;
					}
					else {
						turnoGiocatore = 0;
					};
					if (turnoGiocatore == turnoIniziale) {
						for (int i = 0; i < giocatori.size(); i++) {
							giocatori[i].setFaseGioco(2); // tutti alla fase di attacco o spostamento
						}
						resetOutput();
					}
				}
				break;

			case 1: // schieramento

				windowOutputMessage = "Utilizzare combo carte e poi schierare tutte le armate";
				if (onetime) {
					statusAttacco_Spostamento = false;
					statusSchieramento = true;
					statusCarte = true;
					calcoloArmate(giocatori[turnoGiocatore]);
					onetime = false;
				}

				if (giocatori[turnoGiocatore].getNumArmate() == 0) {
					giocatori[turnoGiocatore].setFaseGioco(2); // passa alla fase di attacco o spostamento
					onetime = true;
					resetOutput();
				}

				break;

			case 2: // attacco o spostamento
				windowOutputMessage = "Attacca o esegui max 1 spostamento";
				if (onetime) {
					statusAttacco_Spostamento = true;
					statusSchieramento = false;
					statusCarte = false;
					onetime = false;
				}
				break;

			case 3: // fine turno

				giocatori[turnoGiocatore].setFaseGioco(1); // torna alla fase di schieramento
				if (turnoGiocatore < giocatori.size() - 1) {
					turnoGiocatore++;
				}
				else {
					turnoGiocatore = 0;
				};
				resetOutput();
				resetTurno();
				onetime = true;
				break;
			}
		}
		else {
			statusAttacco_Spostamento = false;
			statusCarte = false;
			statusSchieramento = false;
			windowOutputMessage = "!!! Il giocatore " + giocatori[turnoGiocatore].getName() + " ha vinto !!!";
			windowOutputError = "!!! Il giocatore " + giocatori[turnoGiocatore].getName() + " ha vinto !!!";
			windowOutputDadiA = "!!! Il giocatore " + giocatori[turnoGiocatore].getName() + " ha vinto !!!";
			windowOutputDadiD = "!!! Il giocatore " + giocatori[turnoGiocatore].getName() + " ha vinto !!!";
		}


		// set output territori selezionati
		if (territorioSelezionato != -1) {

			if (isTerritorioAmico(territori, giocatori, territorioSelezionato, turnoGiocatore)) {
				if (territori[territorioSelezionato].getId() != windowTerritorioAmico1) {
					windowTerritorioAmico2 = windowTerritorioAmico1;
					windowTerritorioAmico1 = territori[territorioSelezionato].getId();
				}
			}
			else {
				windowTerritorioNemico = territori[territorioSelezionato].getId();
			}
		}

		ImGui::SFML::Update(map_window, deltaClock.restart());

		//------------------------------------------------------------------------------------------------------------------------------------------

		// Finestra giocatori (lato destro)
		ImGui::SetNextWindowPos(ImVec2(map_window.getSize().x - playerPanelSize.x, 0));
		ImGui::SetNextWindowSize(playerPanelSize);
		ImGui::Begin("Giocatori", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
		for (int i = 0; i < giocatori.size(); i++) {
			if (i != 0) {
				ImGui::Separator();
				ImGui::NewLine();
			}
			ImGui::TextWrapped("Nome: %s", giocatori[i].getName().c_str());
			ImGui::TextWrapped("Id giocatore: %s", to_string(giocatori[i].getIdGiocatore()).c_str());
			ImGui::TextWrapped("Colore: %s", giocatori[i].getColore().c_str());
			ImGui::TextWrapped("Fanti: %s", to_string(giocatori[i].getCarte()[0]).c_str());
			ImGui::TextWrapped("Cavalli: %s", to_string(giocatori[i].getCarte()[1]).c_str());
			ImGui::TextWrapped("Cannoni: %s", to_string(giocatori[i].getCarte()[2]).c_str());
			ImGui::TextWrapped("Jolly: %s", to_string(giocatori[i].getCarte()[3]).c_str());
			ImGui::TextWrapped("Obiettivo: %s", giocatori[i].getObbiettivo().c_str());
		}
		ImGui::End();

		//------------------------------------------------------------------------------------------------------------------------------------------

		// Finestra output (basso a sinistra)
		ImGui::SetNextWindowPos(ImVec2(0, map_window.getSize().y - inputPanelSize.y), ImGuiCond_Always);
		ImGui::SetNextWindowSize(outputPanelSize, ImGuiCond_Always);
		ImGui::Begin("Output", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
		ImGui::TextWrapped("Output: %s", windowOutputMessage.c_str());
		ImGui::Separator();
		ImGui::TextWrapped("Errori: %s", windowOutputError.c_str());
		ImGui::Separator();
		ImGui::TextWrapped("Dadi attaccante: %s", windowOutputDadiA.c_str());
		ImGui::TextWrapped("Dadi difensore: %s", windowOutputDadiD.c_str());
		ImGui::Separator();
		ImGui::TextWrapped(("Turno di: " + giocatori[turnoGiocatore].getName() + " -> (" + giocatori[turnoGiocatore].getColore() + ")").c_str());
		ImGui::Separator();
		ImGui::End();

		//------------------------------------------------------------------------------------------------------------------------------------------

		// Finestra input (basso a destra)
		ImGui::SetNextWindowPos(ImVec2((map_window.getSize().x - playerPanelSize.x) / 2.0f, map_window.getSize().y - inputPanelSize.y), ImGuiCond_Always);
		ImGui::SetNextWindowSize(inputPanelSize, ImGuiCond_Always);
		ImGui::Begin("Scheda di input e comandi", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

		if (statusAttacco_Spostamento) {
			if (ImGui::Button("Attacco")) {
				resetOutput();
				if (windowTerritorioAmico1 != "nessuno" && windowTerritorioNemico != "nessuno") {
					if (sonoConfinanti(confiniTerritori, windowTerritorioAmico1, windowTerritorioNemico)) {
						if (Attacco(territori, giocatori, carteDisponibili)) {
							windowOutputMessage = "Attacco riuscito!";
						}
						else {
							windowOutputMessage = "Attacco fallito!";
						}
					}
					else {
						windowOutputError = "territori non confinanti!!!";
					}
				}
				else {
					windowOutputError = "territori selezionati insufficienti!!!";
				}
			}
			ImGui::SameLine();
			ImGui::TextWrapped((windowTerritorioAmico1 + "  --> ").c_str());
			ImGui::SameLine();
			ImGui::TextWrapped(windowTerritorioNemico.c_str());
			ImGui::Separator();
		}

		if (statusCarte) {

			ImGui::SetNextItemWidth(100.f);
			ImGui::Combo("Carta 1", &selectedItem[0], items, IM_ARRAYSIZE(items));
			ImGui::SameLine();

			ImGui::SetNextItemWidth(100.f);
			ImGui::Combo("Carta 2", &selectedItem[1], items, IM_ARRAYSIZE(items));
			ImGui::SameLine();

			ImGui::SetNextItemWidth(100.f);
			ImGui::Combo("Carta 3", &selectedItem[2], items, IM_ARRAYSIZE(items));


			for (int i = 0; i < giocatori[turnoGiocatore].getCarte().size(); i++) {
				sommaCarte[i] = 0; // Inizializza il conteggio delle carte
			}

			for (int i = 0; i < giocatori[turnoGiocatore].getCarte().size(); i++) {
				sommaCarte[selectedItem[i]]++; // Inizializza il conteggio delle carte
			}

			if (ImGui::Button("Schiera combo")) {
				resetOutput();
				if (giocatori[turnoGiocatore].removeCarte(sommaCarte[0], sommaCarte[1], sommaCarte[2], sommaCarte[3])) {
					if (sommaCarte[2] == 3) {
						giocatori[turnoGiocatore].offsNumArmate(4);
					}
					else if (sommaCarte[0] == 3) {
						giocatori[turnoGiocatore].offsNumArmate(6);
					}
					else if (sommaCarte[1] == 3) {
						giocatori[turnoGiocatore].offsNumArmate(8);
					}
					else if (sommaCarte[0] == 1 && sommaCarte[1] == 1 && sommaCarte[2] == 1) {
						giocatori[turnoGiocatore].offsNumArmate(10);
					}
					else if (sommaCarte[3] == 1 && (sommaCarte[0] == 2 || sommaCarte[1] == 2 || sommaCarte[2] == 2)) {
						giocatori[turnoGiocatore].offsNumArmate(12);
					}
				}
				else {
					windowOutputError = "Non hai abbastanza carte per schierare questa combo!!!";
				}
			}
			ImGui::Separator();

		}

		if (statusSchieramento) {
			if (ImGui::Button("+")) {
				resetOutput();
				//problema durante altri turni possono modificare armate di altri giocatori
				if (isTerritorioAmico(territori, giocatori, territorioSelezionato, turnoGiocatore)) {
					if (!giocatori[turnoGiocatore].placeNumArmate(1, territori[territorioSelezionato])) {
						windowOutputError = "Impossibile schierare altre armate!!!";
					}
				}
				else {
					windowOutputError = "Non puoi modificare le armate di un territorio nemico!!!";
				}
			}
			ImGui::SameLine();
			ImGui::TextWrapped(("Territori da schierare: " + to_string(giocatori[turnoGiocatore].getNumArmate())).c_str());
			ImGui::Separator();
		}

		if (trasferimento && statusAttacco_Spostamento) {
			ImGui::SetNextItemWidth(100.f);
			ImGui::InputInt("(Inserisci un numero)  -- ", &numArmateSpostamento);
			ImGui::SameLine();
			if (ImGui::Button("Sposta")) {
				resetOutput();
				if (windowTerritorioAmico1 != "nessuno" && windowTerritorioAmico2 != "nessuno") {
					if (windowTerritorioAmico1 != windowTerritorioAmico2) {
						if (sonoConfinanti(confiniTerritori, windowTerritorioAmico1, windowTerritorioAmico2)) {
							Sposta(numArmateSpostamento, territori);
						}
						else {
							windowOutputError = "territori non confinanti!!!";
						}
					}
					else {
						windowOutputError = "Territori selezionati identici!!!";
					}
				}
				else {
					windowOutputError = "territori selezionati insufficienti!!!";
				}
			}
			ImGui::TextWrapped((windowTerritorioAmico2 + "  --> ").c_str());
			ImGui::SameLine();
			ImGui::TextWrapped(windowTerritorioAmico1.c_str());
			ImGui::Separator();
		}

		if (ImGui::Button("passo turno")) {
			giocatori[turnoGiocatore].setFaseGioco(3);
		}

		ImGui::End();

		//------------------------------------------------------------------------------------------------------------------------------------------

		ImGui::SetNextWindowPos(ImVec2((map_window.getSize().x - playerPanelSize.x), map_window.getSize().y - inputPanelSize.y), ImGuiCond_Always);
		ImGui::SetNextWindowSize(outputPanelSize, ImGuiCond_Always);
		ImGui::Begin("Info varie", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
		if (territorioSelezionato != -1) {
			ImGui::Separator();
			ImGui::TextWrapped(territori[territorioSelezionato].getId().c_str());
			ImGui::Separator();
			ImGui::TextWrapped(territori[territorioSelezionato].getIdContinente().c_str());
			ImGui::Separator();
			ImGui::TextWrapped(to_string(territori[territorioSelezionato].getPuntiControllo()).c_str());
			ImGui::Separator();
		}
		else { ImGui::TextWrapped("Nessun territorio selezionato"); }
		ImGui::End();

		//------------------------------------------------------------------------------------------------------------------------------------------


		map_window.clear();// Clear screen
		map_window.setView(view);//importa la view per evitare deformazioni durante il resize della finestra
		map_window.draw(sprite_mappa_originale);
		ImGui::SFML::Render(map_window); // Render ImGui

		for (int i = 0; i < sprite_tanks.size(); i++) {

			// Setta colore in base al giocatore
			if (giocatori[territori[i].getIdConquistatore()].getColore() == "rosso") {
				sprite_tanks[i].setColor(Color(255, 0, 0, 255));
			}
			else if (giocatori[territori[i].getIdConquistatore()].getColore() == "blu") {
				sprite_tanks[i].setColor(Color(0, 0, 255, 255));
			}
			else if (giocatori[territori[i].getIdConquistatore()].getColore() == "giallo") {
				sprite_tanks[i].setColor(Color(255, 255, 0, 255));
			}
			else if (giocatori[territori[i].getIdConquistatore()].getColore() == "verde") {
				sprite_tanks[i].setColor(Color(0, 255, 0, 255));
			}
			else if (giocatori[territori[i].getIdConquistatore()].getColore() == "nero") {
				sprite_tanks[i].setColor(Color(41, 49, 51, 255));
			}
			else if (giocatori[territori[i].getIdConquistatore()].getColore() == "viola") {
				sprite_tanks[i].setColor(Color(128, 0, 128, 255));
			}

			// Imposta la scala dello sprite in base alla scala della mappa
			sprite_tanks[i].setScale({ finalScale * 0.055f, finalScale * 0.055f });

			// Imposta l'origine al centro dello sprite
			sprite_tanks[i].setOrigin({ sprite_tanks[i].getLocalBounds().size.x / 2.f, sprite_tanks[i].getLocalBounds().size.y / 2.f });

			// Imposta la posizione dello sprite in base alla grandezza della mappa
			sprite_tanks[i].setPosition(
				{ territori[i].getPosizione().x * sprite_mappa_originale.getGlobalBounds().size.x, territori[i].getPosizione().y * sprite_mappa_originale.getGlobalBounds().size.y }
			);

			map_window.draw(sprite_tanks[i]);

			// Conmfigura il testo delle armate sullo sprite del carro
			Text armyText(font);
			armyText.setString(to_string(territori[i].getNumArmate()));
			//armyText.setCharacterSize(15);
			armyText.setScale({ finalScale * 0.7f,  finalScale * 0.7f });
			armyText.setFillColor(Color::White);
			//armyText.setOutlineColor(sf::Color::Black);
			armyText.setOutlineThickness(2);
			armyText.setOrigin({ armyText.getLocalBounds().size.x / 2.f, armyText.getLocalBounds().size.y / 2.f });

			// Centra il testo sopra il carro
			armyText.setPosition({ sprite_tanks[i].getPosition().x ,sprite_tanks[i].getPosition().y });

			map_window.draw(armyText);
		}

		map_window.display();// Update the window
	}

	ImGui::SFML::Shutdown(); // Cleanup ImGui
	return 0;
}

bool isTerritorioAmico(vector<Territorio> territori, vector<Player> giocatori, int territorioSelezionato, int turnoGiocatore) {
	return (territori[territorioSelezionato].getIdConquistatore() == giocatori[turnoGiocatore].getIdGiocatore());
}

Vector2u getMousePos(RenderWindow& map_window, Sprite& sprite_mappa_originale, Image& mappa_modificata) {
	// Get mouse position in the window
	Vector2i mousePosWindow = Mouse::getPosition(map_window);

	// Get sprite position and scale
	Vector2f spritePos = sprite_mappa_originale.getPosition();  // Usually (0,0)
	Vector2f spriteScale = sprite_mappa_originale.getScale();

	// Calculate mouse position relative to the sprite top-left
	float relativeX = (mousePosWindow.x - spritePos.x) / spriteScale.x;
	float relativeY = (mousePosWindow.y - spritePos.y) / spriteScale.y;

	// Clamp to image boundaries
	relativeX = clamp(relativeX, 0.f, (float)mappa_modificata.getSize().x - 1);
	relativeY = clamp(relativeY, 0.f, (float)mappa_modificata.getSize().y - 1);

	return Vector2u((unsigned int)relativeX, (unsigned int)relativeY);
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

vector<string> getConquistaContinenti(Player& giocatore) {
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

int getNumTerritori(Player& giocatore, int nArmateMinime) {
	int tempNumArmate = 0;
	for (int i = 0; i < giocatore.getTerritori().size(); i++)
	{
		if (giocatore.getTerritori()[i].getNumArmate() >= nArmateMinime) {
			tempNumArmate++;
		}
	}
	return tempNumArmate;
}

void initGiocatori(vector<Player>& giocatori, default_random_engine engine)
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

int checkObbiettivoColore(Player& giocatore, string colore, vector<Player>& giocatori, vector<Territorio> territori) {
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

int winner(Player& giocatore, vector<Player>& giocatori, vector<Territorio> territori)
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

void initTerritori(vector<Player>& giocatori, vector<Territorio>& territori, int turnoGiocatore) {
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

bool Attacco(vector<Territorio>& territori, vector<Player>& giocatori, array<int, 4>& carteDisponibili) {

	int attaccante = -1;
	int difensore = -1;
	int attaccantePlayer = -1;
	int difensorePlayer = -1;

	for (int i = 0; i < territori.size(); i++) {

		if (territori[i].getId() == windowTerritorioAmico1)
		{
			attaccante = i;
		}
		else if (territori[i].getId() == windowTerritorioNemico)
		{
			difensore = i;
		}
	}

	for (int i = 0; i < giocatori.size(); i++) {

		if (giocatori[i].getIdGiocatore() == territori[attaccante].getIdConquistatore())
		{
			attaccantePlayer = i;
		}
		else if (giocatori[i].getIdGiocatore() == territori[difensore].getIdConquistatore())
		{
			difensorePlayer = i;
		}
	}

	if (territori[attaccante].getNumArmate() <= 1) {
		windowOutputError = "Non hai abbastanza truppe per attaccare!!!";
		return false;
	}

	// Numero dadi
	int dadiAttacco = min(3, territori[attaccante].getNumArmate() - 1);
	int dadiDifesa = min(2, territori[difensore].getNumArmate());

	// Genera dadi
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(1, 6);

	// Crea i dadi per attacco e difesa
	vector<int> dadiA, dadiD;
	for (int i = 0; i < dadiAttacco; ++i) dadiA.push_back(dis(gen));
	for (int i = 0; i < dadiDifesa; ++i) dadiD.push_back(dis(gen));

	// Ordina i dadi in ordine decrescente
	sort(dadiA.begin(), dadiA.end(), greater<>());
	sort(dadiD.begin(), dadiD.end(), greater<>());

	// output dei dadi
	for (int i = 0; i < dadiA.size(); ++i) {
		windowOutputDadiA += to_string(dadiA[i]) + " ";
	}
	for (int i = 0; i < dadiD.size(); ++i) {
		windowOutputDadiD += to_string(dadiD[i]) + " ";
	}

	// Confronto dadi e rimozione armate
	for (int i = 0; i < min(dadiA.size(), dadiD.size()); ++i) {
		if (dadiA[i] > dadiD[i]) {
			territori[difensore].offsNumArmate(-1);
		}
		else {
			territori[attaccante].offsNumArmate(-1);
		}
	}

	// Controlla se il territorio è stato conquistato
	if (territori[difensore].getNumArmate() <= 0) {
		giocatori[difensorePlayer].removeTerritorio(territori[difensore]);
		giocatori[attaccantePlayer].addTerritorio(territori[difensore]);
		windowTerritorioNemico = "nessuno";
		territori[difensore].setNumArmate(dadiAttacco); // si spostano truppe nel territorio conquistato
		territori[attaccante].offsNumArmate(-dadiAttacco);
		windowOutputMessage = "Territorio conquistato!";

		if (cartaTerritorio) {
			giocatori[attaccantePlayer].addCarta(carteDisponibili);
			cartaTerritorio = false; // reset carta territorio dopo l'attacco
		}

		if (giocatori[difensorePlayer].getTerritori().size() == 0) {
			// Se il difensore non ha più territori, viene eliminato dal gioco
			giocatori[difensorePlayer].setIdAbbattitore(giocatori[attaccantePlayer].getIdGiocatore());
			windowOutputMessage += " Il giocatore " + giocatori[difensorePlayer].getName() + " è stato eliminato!";
			// Rimuovi il giocatore
			giocatori.erase(giocatori.begin() + difensorePlayer);
			return true;
		}
	}

	return false;
}

bool Sposta(int numArmateSpostamento, vector<Territorio>& territori) {
	if (numArmateSpostamento > 0) {
		int amico1 = -1;
		int amico2 = -1;

		for (int i = 0; i < territori.size(); i++) {
			if (territori[i].getId() == windowTerritorioAmico1)
			{
				amico1 = i;
			}
			else if (territori[i].getId() == windowTerritorioAmico2)
			{
				amico2 = i;
			}
		}

		if (territori[amico2].getNumArmate() > numArmateSpostamento) {
			territori[amico2].offsNumArmate(-numArmateSpostamento);
			territori[amico1].offsNumArmate(numArmateSpostamento);
			windowOutputMessage = "Spostamento riuscito!";
			trasferimento = false; // disabilita il trasferimento dopo lo spostamento
			return true;

		}
		else {
			windowOutputError = "Numero di armate da spostare superiore a quelle presenti!!!";
			return false;
		}

	}
	else {
		windowOutputError = "Numero di armate da spostare non valido!!!";
		return false;
	}
}

void calcoloArmate(Player& giocatore) {
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