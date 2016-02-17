#include <Windows.h>
#include <TGUI/TGUI.hpp>

int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	// Create the window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Window");
	
	tgui::Panel::Ptr m_panel_1 = std::make_shared<tgui::Panel>();
	tgui::Panel::Ptr m_panel_4 = std::make_shared<tgui::Panel>();
	tgui::Label::Ptr nazwa_1 = std::make_shared<tgui::Label>();
	

	nazwa_1->setAutoSize(true);
	nazwa_1->setTextSize(14);
	nazwa_1->setTextColor({ 255,255,255 });
	m_panel_1->add(nazwa_1, "Nazwa");
	nazwa_1->setPosition({ "w > &.w ? 0 : (&.w - w) / 2" }, { "h > &.h ? 0 : (&.h - h) / 2" });
	m_panel_1->setBackgroundColor(sf::Color::Transparent);
	
	tgui::Panel::Ptr m_panel_2 = tgui::Panel::copy(m_panel_1);
	tgui::Panel::Ptr m_panel_3 = tgui::Panel::copy(m_panel_1);
	tgui::Label::Ptr nazwa_2 = m_panel_2->get<tgui::Label>("Nazwa");
	tgui::Label::Ptr nazwa_3 = m_panel_3->get<tgui::Label>("Nazwa");

	m_panel_4->add(m_panel_1, "1");
	m_panel_4->add(m_panel_2, "2");
	m_panel_4->add(m_panel_3, "3");

	tgui::Gui gui(window);
	gui.setFont("resource\\arial.ttf");

	nazwa_1->setText("Text");
	nazwa_2->setText("Text");
	nazwa_3->setText("Text");

	gui.add(m_panel_4, "4");

	nazwa_3->setText("Text2");
	
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
