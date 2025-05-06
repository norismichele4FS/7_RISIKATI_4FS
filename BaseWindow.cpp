#include "BaseWindow.h"

void BaseWindow::start_window() {

	// Load a sprite to display
	const Texture mappa_originale("mappa_originale.png");
	Sprite sprite_mappa_originale(mappa_originale);

	const Image mappa_modificata("mappa_modificata.png");

	///Color prova;

	// Create the main window
	RenderWindow map_window(VideoMode({ mappa_originale.getSize().x, mappa_originale.getSize().y }), "RISIKO", Style::Titlebar | Style::Resize | Style::Close);
	// Start the game loop
	while (map_window.isOpen())
	{
		// Process events
		while (const optional event = map_window.pollEvent())
		{
			// Close window: exit
			if (event->is<Event::Closed>()) {
				map_window.close();
			}

			///if (event->is<Event::MouseWheelScrolled>()) {
				///prova = mappa_modificata.getPixel({ (unsigned int)Mouse::getPosition().x - map_window.getPosition().x - 8, (unsigned int)Mouse::getPosition().y - map_window.getPosition().y - 31 });
				///cout << to_string(prova.r) + " " + to_string(prova.g) + " " + to_string(prova.b) + "( " + to_string(Mouse::getPosition().x - map_window.getPosition().x - 8) + " , " + to_string(Mouse::getPosition().y - map_window.getPosition().y - 31) + " )" << endl;
				///Sleep(1000);
			///}
		}

		// Clear screen
		map_window.clear();

		// Draw the sprite
		map_window.draw(sprite_mappa_originale);

		// Update the window
		map_window.display();
	}
}

