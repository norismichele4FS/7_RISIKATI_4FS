#pragma once

// Variabili globali per le finestre di imgui
string windowOutputMessage = "";
string windowOutputError = "nessun errore";
string windowOutputDadiA = "";
string windowOutputDadiD = "";
string windowTerritorioAmico1 = "nessuno";
string windowTerritorioAmico2 = "nessuno";
string windowTerritorioNemico = "nessuno";

bool trasferimento = true;
bool cartaTerritorio = true;
bool onetime = true;
bool statusSchieramento = true;
bool statusCarte = false;
bool statusAttacco_Spostamento = false;
bool statusPassoTurno = false;

int territorioSelezionato = -1;
int numArmateSpostamento = 1;
array<int, 4> carteDisponibili = { 14, 14, 14, 2 }; //numero di carte per simbolo disponibili - 14 per i 3 simboli e 2 per il jolly (fan, cav, can, jol)
static const char* items[]{ "Fante","Cavallo","Cannone", "Jolly" };
static int selectedItem[3] = { 0, 0, 0 };
int sommaCarte[4] = { 0, 0, 0, 0 }; // per il calcolo delle carte da utilizzare per lo schieramento

Font font("arial.ttf");
Image icon;
Image mappa_modificata;
Texture mappa_originale;
Texture tankTexture;
vector<Sprite> sprite_tanks;
Color tempColor;
Clock deltaClock;
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

void resetOutput() {
	windowOutputError = "nessun errore";
	windowOutputMessage = "";
	windowOutputDadiA = "";
	windowOutputDadiD = "";
}

void resetTurno() {
	cartaTerritorio = true;
	trasferimento = true;
	windowTerritorioAmico1 = "nessuno";
	windowTerritorioAmico2 = "nessuno";
	windowTerritorioNemico = "nessuno";
}