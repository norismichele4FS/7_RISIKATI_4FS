# **Risiko C++/SFML**

**Risiko** è una versione digitale del celebre gioco da tavolo, sviluppata in **C++** utilizzando la libreria grafica **SFML** e l’interfaccia utente **ImGui**.
Il progetto è pensato per essere facilmente **estendibile** e **manutenibile**, con una chiara **separazione tra logica di gioco e interfaccia grafica**.

---
**Struttura del Codice**

File Principali

* **`7_RISIKO.cpp`**
  Contiene il punto di ingresso dell’applicazione, la gestione della finestra, il ciclo principale del gioco, la logica di rendering e l’integrazione con ImGui.
  Qui vengono inizializzati i giocatori, i territori, le texture e vengono gestiti gli eventi di input.

* **`Player.h` / `Player.cpp`**
  Definisce la classe `Player`, che rappresenta ciascun giocatore.
  Ogni giocatore ha:

  * nome
  * colore
  * obiettivo
  * carte
  * territori posseduti
  * numero di armate
  * stato del turno

* **`Territorio.h` / `Territorio.cpp`**
  Definisce la classe `Territorio`, che rappresenta ogni territorio sulla mappa.
  Ogni territorio ha:

  * un identificativo
  * continente di appartenenza
  * numero di armate
  * colore
  * posizione sulla mappa
  * riferimento al giocatore che lo controlla

* **`resource.h`**
  File contenente le risorse del gioco (icone, immagini, ecc.).

---

Logica di Gioco

La logica è gestita principalmente tramite funzioni globali in `7_RISIKO.cpp`, tra cui:

* **Gestione dei turni**
  Il turno attivo è controllato dalla variabile `turnoGiocatore` e dallo stato `faseGioco` di ciascun giocatore.

* **Gestione territori e armate**
  Funzioni come:

  * `initTerritori`
  * `calcoloArmate`
  * `Attacco`
  * `Sposta`
    gestiscono l’assegnazione dei territori, il calcolo delle armate, l’attacco e lo spostamento delle truppe.

* **Gestione delle carte**
  Ogni giocatore può accumulare carte e utilizzarle per ottenere armate extra.

* **Verifica delle condizioni di vittoria**
  La funzione `winner()` controlla se un giocatore ha raggiunto il proprio obiettivo segreto.

* **Gestione della mappa e dei confini**
  I confini tra territori sono rappresentati da una lista di coppie, utile per verificare validità di attacchi e spostamenti.

---

Interfaccia Grafica

* **SFML**: usata per visualizzare la mappa e i carri armati (sprite).
* **ImGui**: utilizzata per pannelli laterali e inferiori che mostrano:

  * informazioni sui giocatori
  * input di gioco
  * stato e messaggi

---

Organizzazione delle Variabili

* Le **variabili di stato di gioco** (giocatori, territori, carte, turno, ecc.) sono gestite come **variabili globali o locali** nel `main`.
* Le **variabili grafiche** (finestre, sprite, font, ecc.) sono gestite nel ciclo principale del gioco.

---

Come Compilare

1. Assicurati di avere installato:

   * un compilatore compatibile con **C++14**
   * la libreria **SFML**
2. Clona il repository del progetto.
3. Compila il progetto con **Visual Studio** o da **terminale**, includendo le dipendenze di **SFML** e **ImGui-SFML**.
4. Esegui il file eseguibile generato.

---

Come Giocare

* All’avvio, inserisci il **numero di giocatori** e i **loro nomi**.
* Ogni giocatore, a turno:

  * schiera armate
  * attacca
  * sposta truppe
    secondo le regole classiche di **Risiko**.
* L’interfaccia mostra:

  * mappa
  * territori
  * armate
  * informazioni di gioco
* Vince chi **raggiunge per primo il proprio obiettivo segreto**.


