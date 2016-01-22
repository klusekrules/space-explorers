#include <Windows.h>
#include <TGUI/TGUI.hpp>

int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	// Create the window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Window");
	
	tgui::Panel::Ptr m_panel = std::make_shared<tgui::Panel>();
	tgui::Label::Ptr nazwa_ = std::make_shared<tgui::Label>();
	m_panel->add(nazwa_, "NazwaObiektu");
	nazwa_->setSize({ "{ ( &.w - &.h - 20 ) * 0.715 , ( &.h - 11 ) * 0.15 }" });
	m_panel->setSize(410, 110);

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
