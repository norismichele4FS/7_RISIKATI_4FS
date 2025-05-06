#include "BaseWindow.h"

void BaseWindow::start_window() {

	// Load a sprite to display
	const Texture mappa("mappa_originale.png");
	Sprite sprite_mappa(mappa);

	// Create the main window
	RenderWindow map_window(VideoMode({ 600, 600 }), "RISIKO");
	// Start the game loop
	while (map_window.isOpen())
	{
		// Process events
		while (const optional event = map_window.pollEvent())
		{
			// Close window: exit
			if (event->is<Event::Closed>())
				map_window.close();
		}

		// Clear screen
		map_window.clear();

		// Draw the sprite
		map_window.draw(sprite_mappa);

		// Update the window
		map_window.display();
	}
}

