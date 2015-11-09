#include <Windows.h>
#include <TGUI/TGUI.hpp>

int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	// Create the window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Window");
	
	tgui::Gui gui(window);
	gui.setFont("resource\\arial.ttf");
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			// Pass the event to all the widgets (if there would be widgets)
			gui.handleEvent(event);
		}

		window.clear(sf::Color(255, 255, 255, 255));

		// Draw all created widgets
		gui.draw();

		window.display();
	}

	return EXIT_SUCCESS;
}
