#include <Windows.h>
#include <TGUI/TGUI.hpp>
#include "..\ListaObiektowGui.h"

int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	// Create the window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Window");
	
	tgui::Gui gui(window);
	gui.setGlobalFont("resource\\arial.ttf");
	
	tgui::ListaObiektowGui::Ptr o(gui,"MojaKontrolka");
	o->load("widgets\\Black.conf");
	//o->setSize(470,350);
	o->addElement("Pierwszy");
	o->addElement("drugi");
	o->addElement("trzeci");
	o->addElement("czwarty");
	/*o->addElement("piaty");
	o->addElement("szosty");*/

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

// test 1 
// kontrolka obiektu
/*tgui::Grid::Ptr siatka(gui, "Siatka");
tgui::KontrolkaObiektu::Ptr kontrolka1(gui, "Moja Kontrolka");
tgui::KontrolkaObiektu::Ptr kontrolka2(*siatka, "Moja Kontrolka2");
tgui::KontrolkaObiektu::Ptr kontrolka3(*siatka, "Moja Kontrolka3");

kontrolka1->load("widgets\\Black.conf");
kontrolka2->load("widgets\\Black.conf");
kontrolka3->load("widgets\\Black.conf");

kontrolka1->setBackgroundTexture(&tlo_);
kontrolka2->setBackgroundTexture(&tlo_);
kontrolka3->setBackgroundTexture(&tlo_);

kontrolka1->setSize(500, 200);

siatka->addWidget(kontrolka1, 0, 0, tgui::Borders(2, 2, 2, 2));
siatka->addWidget(kontrolka2, 1, 0, tgui::Borders(2, 2, 2, 2));
siatka->addWidget(kontrolka3, 2, 0, tgui::Borders(2, 2, 2, 2));
gui.loadWidgetsFromFile("resource\\test.wdg");*/

// koniec test 1