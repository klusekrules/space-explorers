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
			throw Exception{ "No save function exists for widget type 'Panel'." };

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

	std::shared_ptr<DataIO::Node> saveLogListGui(LogListGui::Ptr widget) {
		auto node = std::make_shared<DataIO::Node>();
		auto& savewidget = WidgetSaver::getSaveFunction(toLower("ChatBox"));
		if (savewidget)
			node = savewidget(WidgetConverter{ widget });
		else
			throw Exception{ "No save function exists for widget type 'ChatBox'." };

		SET_PROPERTY("MessageTypeFile", tgui::to_string(widget->pobierzPlikOpisowTypowKomunikatow()));
		return node;
	}

	std::shared_ptr<DataIO::Node> saveListaSurowcowGui(ListaSurowcowGui::Ptr widget)
	{
		auto node = saveBazowyWidzet(widget);

		auto& saveSzablon = WidgetSaver::getSaveFunction(toLower("SurowiecGui"));
		if (saveSzablon)
			node->children.emplace_back(saveSzablon(WidgetConverter{ widget->szablonKontrolki_ }));
		else
			throw Exception{ "No save function exists for widget type 'SurowiecGui'." };

		return node;
	}

	std::shared_ptr<DataIO::Node> saveListaObiektowGui(ListaObiektowGui::Ptr widget){
		auto node = saveBazowyWidzet(widget);
		SET_PROPERTY("MnoznikRolki", tgui::to_string(widget->mnoznikRolki_));
		SET_PROPERTY("OdstepMiedzyKontrolkami", tgui::to_string(widget->odstepMiedzyKontrolkami_));
		SET_PROPERTY("TypObiektu", tgui::to_string(widget->typObiektu_));
		SET_PROPERTY("AutoRozmiar", tgui::to_string(widget->czyAutoRozmiar_));

		auto& saveSzablon = WidgetSaver::getSaveFunction(toLower("KontrolkaObiektu"));
		if (saveSzablon)
			node->children.emplace_back(saveSzablon(WidgetConverter{ widget->szablonKontrolki_ }));
		else
			throw Exception{ "No save function exists for widget type 'KontrolkaObiektu'." };

		return node;
	}

};