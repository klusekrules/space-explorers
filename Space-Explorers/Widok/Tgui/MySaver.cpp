#include "MySaver.h"
#include "Utils\FromTGUI.h"
#include <TGUI\TGUI.hpp>

namespace tgui {
	std::shared_ptr<DataIO::Node> saveBazowyWidzet(BazowyWidzet::Ptr widget){
		auto node = std::make_shared<DataIO::Node>();
		auto& savewidget = WidgetSaver::getSaveFunction(toLower("Widget"));
		if (savewidget)
			node = savewidget(WidgetConverter{ widget });
		else
			throw Exception{ "No save function exists for widget type 'Widget'." };

		auto& savePanel = WidgetSaver::getSaveFunction(toLower("Panel"));
		if (savePanel)
			node->children.emplace_back(savePanel(WidgetConverter{ widget->m_panel }));
		else
			throw Exception{ "No save function exists for widget type 'Widget'." };

		return node;
	}

	std::shared_ptr<DataIO::Node> saveSurowiecGui(SurowiecGui::Ptr widget)
	{
		auto node = saveBazowyWidzet(widget);
		
		SET_PROPERTY("IdentyfikatorObiektu", tgui::to_string(widget->pobierzIdObiektu()));

		return node;
	}

	std::shared_ptr<DataIO::Node> saveKontrolkaObiektu(KontrolkaObiektu::Ptr widget)
	{
		auto node = saveBazowyWidzet(widget);

		SET_PROPERTY("IdentyfikatorObiektu", tgui::to_string(widget->pobierzIdObiektu()));
		SET_PROPERTY("IdentyfikatorZdarzeniaBudowy", tgui::to_string(widget->pobierzIdentyfikatorZdarzeniaBudowy()));
		SET_PROPERTY("IdentyfikatorZdarzeniaBurzenia", tgui::to_string(widget->pobierzIdentyfikatorZdarzeniaBurzenia()));
		SET_PROPERTY("IdentyfikatorZdarzeniaKlikniecia", tgui::to_string(widget->pobierzIdentyfikatorZdarzeniaKlikniecia()));

		return node;
	}

};