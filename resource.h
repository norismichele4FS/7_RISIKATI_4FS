//{{NO_DEPENDENCIES}}
// File di inclusione generato con Microsoft Visual C++.
// Utilizzato da 7_RISIKO.rc

// Next default values for new objects
// 
#ifdef APSTUDIO_INVOKED
#ifndef APSTUDIO_READONLY_SYMBOLS
#define _APS_NEXT_RESOURCE_VALUE        102
#define _APS_NEXT_COMMAND_VALUE         40001
#define _APS_NEXT_CONTROL_VALUE         1001
#define _APS_NEXT_SYMED_VALUE           101
#endif
#endif

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