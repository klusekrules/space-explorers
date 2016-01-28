#include "MySaver.h"
#include "Utils\FromTGUI.h"
#include <TGUI\TGUI.hpp>

namespace tgui {

	TGUI_API Widget::Ptr copyloadWidget(std::shared_ptr<DataIO::Node> node, Widget::Ptr widget)
	{
		assert(widget != nullptr);

		if (node->propertyValuePairs["visible"])
		{
			bool visible = parseBoolean(node->propertyValuePairs["visible"]->value);
			if (visible)
				widget->show();
			else
				widget->hide();
		}
		if (node->propertyValuePairs["enabled"])
		{
			bool enabled = parseBoolean(node->propertyValuePairs["enabled"]->value);
			if (enabled)
				widget->enable();
			else
				widget->disable();
		}
		if (node->propertyValuePairs["position"])
			widget->setPosition(parseLayout(node->propertyValuePairs["position"]->value));
		if (node->propertyValuePairs["size"])
			widget->setSize(parseLayout(node->propertyValuePairs["size"]->value));
		if (node->propertyValuePairs["opacity"])
			widget->setOpacity(tgui::stof(node->propertyValuePairs["opacity"]->value));

		/// TODO: Font and ToolTip (and Theme?)

		for (auto& childNode : node->children)
		{
			if (toLower(childNode->name) == "renderer")
			{
				for (auto& pair : childNode->propertyValuePairs)
					widget->getRenderer()->setProperty(pair.first, pair.second->value);
			}
		}
		REMOVE_CHILD("renderer");

		return widget;
	}

	Widget::Ptr loadBazowyWidzet(std::shared_ptr<DataIO::Node> node, Widget::Ptr widget = nullptr) {
		BazowyWidzet::Ptr widgetPtr;
		if (widget)
			widgetPtr = std::static_pointer_cast<BazowyWidzet>(widget);
		else
			widgetPtr = std::make_shared<BazowyWidzet>();

		copyloadWidget(node, widget);

		for (auto& childNode : node->children){
			if (toLower(childNode->name) == "panel"){
				widgetPtr->m_panel = std::static_pointer_cast<Panel>(WidgetLoader::getLoadFunction("Panel")(childNode));
			}
		}
		REMOVE_CHILD("panel");
		
		return widgetPtr;
	}

	Widget::Ptr loadSurowiecGui(std::shared_ptr<DataIO::Node> node, Widget::Ptr widget = nullptr) {
		SurowiecGui::Ptr widgetPtr;
		if (widget)
			widgetPtr = std::static_pointer_cast<SurowiecGui>(widget);
		else
			widgetPtr = std::make_shared<SurowiecGui>();
				
		loadBazowyWidzet(node, widgetPtr);

		if (node->propertyValuePairs["IdentyfikatorObiektu"])
			widgetPtr->idObiektu_(tgui::stoi(node->propertyValuePairs["IdentyfikatorObiektu"]->value));

		widgetPtr->tekst_ = widgetPtr->m_panel->get<Label>("Nazwa");

		return widgetPtr;
	}

	Widget::Ptr loadKontrolkaObiektu(std::shared_ptr<DataIO::Node> node, Widget::Ptr widget = nullptr) {
		KontrolkaObiektu::Ptr widgetPtr;
		if (widget)
			widgetPtr = std::static_pointer_cast<KontrolkaObiektu>(widget);
		else
			widgetPtr = std::make_shared<KontrolkaObiektu>();

		loadBazowyWidzet(node, widgetPtr);

		if (node->propertyValuePairs["IdentyfikatorObiektu"])
			widgetPtr->idObiektu_(tgui::stoi(node->propertyValuePairs["IdentyfikatorObiektu"]->value));
		if (node->propertyValuePairs["IdentyfikatorZdarzeniaBudowy"])
			widgetPtr->idZdarzeniaBudowy_ = tgui::stoi(node->propertyValuePairs["IdentyfikatorZdarzeniaBudowy"]->value);
		if (node->propertyValuePairs["IdentyfikatorZdarzeniaBurzenia"])
			widgetPtr->idZdarzeniaBurzenia_ = tgui::stoi(node->propertyValuePairs["IdentyfikatorZdarzeniaBurzenia"]->value);
		if (node->propertyValuePairs["IdentyfikatorZdarzeniaKlikniecia"])
			widgetPtr->idZdarzeniaKlikniecia_ = tgui::stoi(node->propertyValuePairs["IdentyfikatorZdarzeniaKlikniecia"]->value);

		widgetPtr->obraz_ = widgetPtr->m_panel->get<Picture>("ObrazObiektu");
		widgetPtr->nazwa_ = widgetPtr->m_panel->get<Label>("NazwaObiektu");
		widgetPtr->tresc_ = widgetPtr->m_panel->get<Label>("OpisObiektu");
		widgetPtr->rozbuduj_ = widgetPtr->m_panel->get<Button>("Rozbuduj");
		widgetPtr->zniszcz_ = widgetPtr->m_panel->get<Button>("Zburz");
		widgetPtr->czasRozbudowy_ = widgetPtr->m_panel->get<Label>("CzasRozbudowy");
		widgetPtr->czasZburzenia_ = widgetPtr->m_panel->get<Label>("CzasZburzenia");

		return widgetPtr;
	}
};