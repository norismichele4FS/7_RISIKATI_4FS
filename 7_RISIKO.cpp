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


using namespace std;
using namespace sf;

//TO DO LIST

/*
	1. controllare prototipi funzioni + coincidenza con dichiarazioni
	2. forse creare classe logic per suddividere le funzioni in modo piu' ordinato --> non urgente
	3. creare modo per disporre carri armati
	3. creare logica di attacco e difesa
*/

bool sonoConfinanti(vector<pair<string, string>>&, string, string);
int winner(Player&, vector<Player>&, vector<Territorio>); // -1 = nessuno, 0 = giocatore 1, 1 = giocatore 2, ecc.
vector<string> getConquistaContinenti(Player&);
int getNumTerritori(Player&, int);
Vector2u getMousePos(RenderWindow&, Sprite&, Image&);
bool isTerritorioAmico(vector<Territorio>, vector<Player>, int, int);
void initGiocatori(vector<Player>&, default_random_engine);
void initTerritori(vector<Player>&, vector<Territorio>&, int);

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
	shuffle(territori.begin(), territori.end(), engine);
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

	Image mappa_modificata;
	Texture mappa_originale;
	Texture tankTexture;
	if (!mappa_originale.loadFromFile("mappa_originale.png")) {}
	if (!mappa_modificata.loadFromFile("mappa_modificata.png")) {}
	if (!tankTexture.loadFromFile("duck.png")) {}
	Sprite sprite_mappa_originale(mappa_originale);
	Sprite sprite_tank(tankTexture);

	int territorioSelezionato = -1;
	string windowOutput = "";
	string windowTerritorioAmico = "nessuno";
	string windowTerritorioNemico = "nessuno";

	Color temp;

	initGiocatori(giocatori, engine);
	int turnoGiocatore = rand() % giocatori.size();
	initTerritori(giocatori, territori, turnoGiocatore);


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
		map_window.getSize().x / 3.0f,
		map_window.getSize().y * imageWindowsRatio
	);

	ImVec2 outputPanelSize = ImVec2(
		map_window.getSize().x / 3.0f,
		map_window.getSize().y * imageWindowsRatio
	);

	ImVec2 infoPanelSize = ImVec2(
		map_window.getSize().x / 3.0f,
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
					map_window.getSize().x / 3.0f,
					map_window.getSize().y * imageWindowsRatio
				);

				outputPanelSize = ImVec2(
					map_window.getSize().x / 3.0f,
					map_window.getSize().y * imageWindowsRatio
				);

				infoPanelSize = ImVec2(
					map_window.getSize().x / 3.0f,
					map_window.getSize().y * imageWindowsRatio
				);

				scaleX = (map_window.getSize().x - playerPanelSize.x) / original_map_x;
				scaleY = (map_window.getSize().y - inputPanelSize.y) / original_map_y;
				finalScale = min(scaleX, scaleY);
				sprite_mappa_originale.setScale({ finalScale, finalScale });// Apply scale to sprite

				view = View(FloatRect({ 0.f, 0.f }, { static_cast<float>(map_window.getSize().x), static_cast<float>(map_window.getSize().y) }));
			}

			if (event->is<Event::MouseButtonPressed>()) {
				if (Mouse::isButtonPressed(Mouse::Button::Right))
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

		ImGui::SFML::Update(map_window, deltaClock.restart());

		// Finestra giocatori (lato destro)
		ImGui::SetNextWindowPos(ImVec2(map_window.getSize().x - playerPanelSize.x, 0));
		ImGui::SetNextWindowSize(playerPanelSize);
		ImGui::Begin("Giocatori", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
		for (int i = 0; i < giocatori.size(); i++) {
			ImGui::Separator();
			ImGui::TextWrapped("Giocatore numero %d", i + 1);
			ImGui::TextWrapped("Nome: %s", giocatori[i].getName().c_str());
			ImGui::TextWrapped("Id giocatore: %s", to_string(giocatori[i].getIdGiocatore()).c_str());
			ImGui::TextWrapped("Id abbattitore: %s", to_string(giocatori[i].getIdAbbattitore()).c_str());
			ImGui::TextWrapped("Colore: %s", giocatori[i].getColore().c_str());
			ImGui::TextWrapped("Numero Armate da schierare: %d", giocatori[i].getNumArmate());
			ImGui::TextWrapped("Obiettivo: %s", giocatori[i].getObbiettivo().c_str());
			for (int j = 0; j < giocatori[i].getTerritori().size(); j++) {
				ImGui::TextWrapped("Territorio %d: %s", j + 1, giocatori[i].getTerritori()[j].getId().c_str());
			}
		}
		ImGui::End();


		// Finestra output (basso a sinistra)
		ImGui::SetNextWindowPos(ImVec2(0, map_window.getSize().y - inputPanelSize.y), ImGuiCond_Always);
		ImGui::SetNextWindowSize(outputPanelSize, ImGuiCond_Always);
		ImGui::Begin("Output", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
		ImGui::Separator();


		// To fix the error, create a writable buffer to hold the string content of `windowOutput`  
		// and pass it to `ImGui::InputTextMultiline`.  
		std::vector<char> writableBuffer(windowOutput.begin(), windowOutput.end());
		writableBuffer.push_back('\0'); // Ensure null-termination  
		ImGui::InputTextMultiline("##hidden_label", writableBuffer.data(), writableBuffer.size(), ImVec2(0, 0), ImGuiInputTextFlags_ReadOnly);
		//ImGui::TextWrapped(windowOutput.c_str());


		ImGui::Separator();
		ImGui::TextWrapped("Turno di %s", giocatori[turnoGiocatore].getName().c_str());
		ImGui::Separator();
		ImGui::End();

		// Finestra input (basso a destra)
		ImGui::SetNextWindowPos(ImVec2(map_window.getSize().x / 3.0f, map_window.getSize().y - inputPanelSize.y), ImGuiCond_Always);
		ImGui::SetNextWindowSize(inputPanelSize, ImGuiCond_Always);
		ImGui::Begin("Scheda di input e comandi", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

		if (territorioSelezionato != -1) {

			if (isTerritorioAmico(territori, giocatori, territorioSelezionato, turnoGiocatore)) {
				windowTerritorioAmico = territori[territorioSelezionato].getId();
			}
			else {
				windowTerritorioNemico = territori[territorioSelezionato].getId();
			}

			if (ImGui::Button("Attacco")) {
				// Attacco action
			}
			ImGui::SameLine();
			if (ImGui::Button("+")) {
				//problema durante altri turni possono modificare armate di altri giocatori
				if (isTerritorioAmico(territori, giocatori, territorioSelezionato, turnoGiocatore)) {
					if (!giocatori[turnoGiocatore].replaceNumArmate(1, territori[territorioSelezionato])) { ImGui::TextWrapped("Impossibile schierare ulteriori armate"); }
				}
				else {
					windowOutput = "Non puoi modificare le armate di un territorio nemico!";
				}
			}
			ImGui::SameLine();
			if (ImGui::Button("-")) {
				if (isTerritorioAmico(territori, giocatori, territorioSelezionato, turnoGiocatore)) {
					if (!giocatori[turnoGiocatore].replaceNumArmate(-1, territori[territorioSelezionato])) { ImGui::TextWrapped("Impossibile rimuovere ulteriori armate"); }
				}
				else {
					windowOutput = "Non puoi modificare le armate di un territorio nemico!";
				}
			}
		}
		else {
			ImGui::TextWrapped("Nessun territorio selezionato");
		}

		ImGui::SameLine();
		if (ImGui::Button("passo turno")) {
			if (turnoGiocatore < giocatori.size() - 1) {
				turnoGiocatore++;
			}
			else {
				turnoGiocatore = 0;
			};
		}

		ImGui::TextWrapped("Territorio amico selezionato = %s", windowTerritorioAmico.c_str());
		ImGui::TextWrapped("Territorio nemico selezionato = %s", windowTerritorioNemico.c_str());
		ImGui::End();

		ImGui::SetNextWindowPos(ImVec2(map_window.getSize().x / 3.0f * 2.0f, map_window.getSize().y - inputPanelSize.y), ImGuiCond_Always);
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
			ImGui::TextWrapped(to_string(territori[territorioSelezionato].getNumArmate()).c_str());
			ImGui::Separator();
			ImGui::TextWrapped(to_string(territori[territorioSelezionato].getIdConquistatore()).c_str());
			ImGui::Separator();
		}
		else { ImGui::TextWrapped("Nessun territorio selezionato"); }
		ImGui::End();

		map_window.clear();// Clear screen


		map_window.setView(view);//importa la view per evitare deformazioni durante il resize della finestra

		map_window.draw(sprite_mappa_originale);// Draw the sprite

		//map_window.setView(map_window.getDefaultView());
		float mapWidth = map_window.getSize().x - playerPanelSize.x;
		float mapHeight = map_window.getSize().y - inputPanelSize.y;

		Font font("arial.ttf");
		for (Territorio territory : territori) {
			// Setta colore in base al giocatore
			if (giocatori[territory.getIdConquistatore()].getColore() == "rosso") {
				sprite_tank.setColor(Color(255, 0, 0, 255));
			}
			else if (giocatori[territory.getIdConquistatore()].getColore() == "blu") {
				sprite_tank.setColor(Color(0, 0, 255, 255));
			}
			else if (giocatori[territory.getIdConquistatore()].getColore() == "giallo") {
				sprite_tank.setColor(Color(255, 255, 0, 255));
			}
			else if (giocatori[territory.getIdConquistatore()].getColore() == "verde") {
				sprite_tank.setColor(Color(0, 255, 0, 255));
			}
			else if (giocatori[territory.getIdConquistatore()].getColore() == "nero") {
				sprite_tank.setColor(Color(41, 49, 51, 255));
			}
			else if (giocatori[territory.getIdConquistatore()].getColore() == "viola") {
				sprite_tank.setColor(Color(128, 0, 128, 255));
			}
			//sprite_tank.setScale({ 0.04f, 0.04f }); // scala se troppo grande
			sprite_tank.setScale({ finalScale * 0.05f, finalScale * 0.05f });
			sprite_tank.setPosition(
				{ territory.getPosizione().x * sprite_mappa_originale.getGlobalBounds().size.x - (float)sprite_tank.getGlobalBounds().size.x / 2.f, territory.getPosizione().y * sprite_mappa_originale.getGlobalBounds().size.y - (float)sprite_tank.getGlobalBounds().size.y / 2.f }
			);
			map_window.draw(sprite_tank);
			// Testo con numero armate
			Text armyText(font);
			armyText.setString(std::to_string(territory.getNumArmate()));
			//armyText.setCharacterSize(15);
			armyText.setScale({ finalScale * 0.7f,  finalScale * 0.7f });
			armyText.setFillColor(sf::Color::White);
			//armyText.setOutlineColor(sf::Color::Black);
			armyText.setOutlineThickness(2);

			// Centra il testo sopra il carro
			armyText.setPosition({
				sprite_tank.getPosition().x + sprite_tank.getGlobalBounds().size.x / 2.f - armyText.getGlobalBounds().size.x / 2.f ,
				sprite_tank.getPosition().y + sprite_tank.getGlobalBounds().size.y / 2.f - armyText.getGlobalBounds().size.y / 2.f });


			map_window.draw(armyText);
		}

		ImGui::SFML::Render(map_window); // Render ImGui
		map_window.display();// Update the window
	}

	ImGui::SFML::Shutdown(); // Cleanup ImGui
	return 0;
}

bool isTerritorioAmico(vector<Territorio> territori, vector<Player> giocatori, int territorioSelezionato, int turnoGiocatore) {
	///poi usa il vettore perche' quando inizializzi il gioco il caso id = -1 non si presenta
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
	shuffle(coloriGiocatori.begin(), coloriGiocatori.end(), engine);
	shuffle(obbiettivi.begin(), obbiettivi.end(), engine);

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
			giocatori[i].replaceNumArmate(1, territori[territoriAssegnati]);
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

