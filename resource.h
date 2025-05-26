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

void resetOutput() {
	windowOutputError = "nessun errore";
	windowOutputMessage = "";
	windowOutputDadiA = "";
	windowOutputDadiD = "";
}

void resetTurno() {
	cartaTerritorio = true;
	trasferimento = true;
	string windowTerritorioAmico1 = "nessuno";
	string windowTerritorioAmico2 = "nessuno";
	string windowTerritorioNemico = "nessuno";
}