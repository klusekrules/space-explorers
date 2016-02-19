#include "MySaver.h"
#include "Utils\FromTGUI.h"
#include <TGUI\TGUI.hpp>
#include "MyLoader.h"

namespace tgui {

	Widget::Ptr copyloadWidget(std::shared_ptr<DataIO::Node> node, Widget::Ptr widget){
		assert(widget != nullptr);

		if (node->propertyValuePairs["visible"]){
			bool visible = parseBoolean(node->propertyValuePairs["visible"]->value);
			if (visible)
				widget->show();
			else
				widget->hide();
		}
		if (node->propertyValuePairs["enabled"]){
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

		for (auto& childNode : node->children){
			if (toLower(childNode->name) == "renderer"){
				for (auto& pair : childNode->propertyValuePairs)
					widget->getRenderer()->setProperty(pair.first, pair.second->value);
			}
		}
		REMOVE_CHILD("renderer");

		return widget;
	}

	Widget::Ptr copyloadChatBox(std::shared_ptr<DataIO::Node> node, Widget::Ptr widget = nullptr)
	{
		ChatBox::Ptr chatBox;
		if (widget)
			chatBox = std::static_pointer_cast<ChatBox>(widget);
		else
			chatBox = std::make_shared<ChatBox>();

		copyloadWidget(node, chatBox);

		if (node->propertyValuePairs["textsize"])
			chatBox->setTextSize(tgui::stoi(node->propertyValuePairs["textsize"]->value));
		if (node->propertyValuePairs["textcolor"])
			chatBox->setTextColor(Deserializer::deserialize(ObjectConverter::Type::Color, node->propertyValuePairs["textcolor"]->value).getColor());

		for (auto& childNode : node->children){
			if (toLower(childNode->name) == "scrollbar")
				chatBox->setScrollbar(std::static_pointer_cast<Scrollbar>(WidgetLoader::getLoadFunction("scrollbar")(childNode)));
		}
		REMOVE_CHILD("scrollbar");

		for (auto& childNode : node->children){
			if (toLower(childNode->name) == "line"){
				unsigned int lineTextSize = chatBox->getTextSize();
				sf::Color lineTextColor = chatBox->getTextColor();

				if (childNode->propertyValuePairs["textsize"])
					lineTextSize = tgui::stoi(childNode->propertyValuePairs["textsize"]->value);
				if (childNode->propertyValuePairs["color"])
					lineTextColor = Deserializer::deserialize(ObjectConverter::Type::Color, childNode->propertyValuePairs["color"]->value).getColor();

				if (childNode->propertyValuePairs["text"])
				{
					chatBox->addLine(Deserializer::deserialize(ObjectConverter::Type::String, childNode->propertyValuePairs["text"]->value).getString(),
						lineTextColor,
						lineTextSize);
				}
			}
		}
		REMOVE_CHILD("line");

		if (node->propertyValuePairs["linesstartfromtop"])
			chatBox->setLinesStartFromTop(parseBoolean(node->propertyValuePairs["linesstartfromtop"]->value));

		// This has to be parsed after the lines have been added
		if (node->propertyValuePairs["newlinesbelowothers"])
			chatBox->setNewLinesBelowOthers(parseBoolean(node->propertyValuePairs["newlinesbelowothers"]->value));

		return chatBox;
	}

	Widget::Ptr loadBazowyWidzet(std::shared_ptr<DataIO::Node> node, Widget::Ptr widget = nullptr) {
		BazowyWidzet::Ptr widgetPtr;
		if (widget)
			widgetPtr = std::static_pointer_cast<BazowyWidzet>(widget);
		else
			widgetPtr = std::make_shared<BazowyWidzet>();

		copyloadWidget(node, widgetPtr);

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

		if (node->propertyValuePairs["identyfikatorobiektu"])
			widgetPtr->idObiektu_(tgui::stoi(node->propertyValuePairs["identyfikatorobiektu"]->value));

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

		if (node->propertyValuePairs["identyfikatorobiektu"])
			widgetPtr->idObiektu_(tgui::stoi(node->propertyValuePairs["identyfikatorobiektu"]->value));
		if (node->propertyValuePairs["identyfikatorzdarzeniabudowy"])
			widgetPtr->idZdarzeniaBudowy_ = tgui::stoi(node->propertyValuePairs["identyfikatorzdarzeniabudowy"]->value);
		if (node->propertyValuePairs["identyfikatorzdarzeniaburzenia"])
			widgetPtr->idZdarzeniaBurzenia_ = tgui::stoi(node->propertyValuePairs["identyfikatorzdarzeniaburzenia"]->value);
		if (node->propertyValuePairs["identyfikatorzdarzeniaklikniecia"])
			widgetPtr->idZdarzeniaKlikniecia_ = tgui::stoi(node->propertyValuePairs["identyfikatorzdarzeniaklikniecia"]->value);

		widgetPtr->obraz_ = widgetPtr->m_panel->get<Picture>("ObrazObiektu");
		widgetPtr->nazwa_ = widgetPtr->m_panel->get<Label>("NazwaObiektu");
		widgetPtr->tresc_ = widgetPtr->m_panel->get<Label>("OpisObiektu");
		widgetPtr->rozbuduj_ = widgetPtr->m_panel->get<Button>("Rozbuduj");
		widgetPtr->zniszcz_ = widgetPtr->m_panel->get<Button>("Zburz");
		widgetPtr->czasRozbudowy_ = widgetPtr->m_panel->get<Label>("CzasRozbudowy");
		widgetPtr->czasZburzenia_ = widgetPtr->m_panel->get<Label>("CzasZburzenia");

		return widgetPtr;
	}

	Widget::Ptr loadLogListGui(std::shared_ptr<DataIO::Node> node, Widget::Ptr widget) {
		LogListGui::Ptr widgetPtr;
		if (widget)
			widgetPtr = std::static_pointer_cast<LogListGui>(widget);
		else
			widgetPtr = std::make_shared<LogListGui>();

		copyloadChatBox(node, widgetPtr);

		if (node->propertyValuePairs["messagetypefile"])
			widgetPtr->wczytajOpisyTypowKomunikatow(node->propertyValuePairs["messagetypefile"]->value);

		return widgetPtr;
	}

	Widget::Ptr loadListaSurowcowGui(std::shared_ptr<DataIO::Node> node, Widget::Ptr widget)
	{
		ListaSurowcowGui::Ptr widgetPtr;
		if (widget)
			widgetPtr = std::static_pointer_cast<ListaSurowcowGui>(widget);
		else
			widgetPtr = std::make_shared<ListaSurowcowGui>();

		loadBazowyWidzet(node, widgetPtr);

		for (auto& childNode : node->children){
			if (toLower(childNode->name) == toLower("SurowiecGui"))
				widgetPtr->szablonKontrolki_ = std::static_pointer_cast<SurowiecGui>(WidgetLoader::getLoadFunction(toLower("SurowiecGui"))(childNode));
		}
		REMOVE_CHILD(toLower("SurowiecGui"));

		for (auto& ref : widgetPtr->m_panel->getWidgets()) {
			if (ref->getWidgetType() == "SurowiecGui") {
				widgetPtr->kontrolki_.push_back(std::static_pointer_cast<SurowiecGui>(ref));
			}
		}

		return widgetPtr;
	}

	Widget::Ptr loadListaObiektowGui(std::shared_ptr<DataIO::Node> node, Widget::Ptr widget)
	{
		ListaObiektowGui::Ptr widgetPtr;
		if (widget)
			widgetPtr = std::static_pointer_cast<ListaObiektowGui>(widget);
		else
			widgetPtr = std::make_shared<ListaObiektowGui>();

		loadBazowyWidzet(node, widgetPtr);

		if (node->propertyValuePairs[toLower("SzerokoscSuwaka")])
			widgetPtr->szerokoscSuwaka_ = tgui::stof(node->propertyValuePairs[toLower("SzerokoscSuwaka")]->value);
		if (node->propertyValuePairs[toLower("OdstepMiedzyKontrolkami")])
			widgetPtr->odstepMiedzyKontrolkami_ = tgui::stof(node->propertyValuePairs[toLower("OdstepMiedzyKontrolkami")]->value);
		
		if (node->propertyValuePairs[toLower("MnoznikRolki")])
			widgetPtr->mnoznikRolki_ = tgui::stoi(node->propertyValuePairs[toLower("MnoznikRolki")]->value);
		if (node->propertyValuePairs[toLower("TypObiektu")])
			widgetPtr->typObiektu_ = tgui::stoi(node->propertyValuePairs[toLower("TypObiektu")]->value);

		if (node->propertyValuePairs[toLower("PokazSuwak")])
			widgetPtr->pokazSuwak_ = parseBoolean(node->propertyValuePairs[toLower("PokazSuwak")]->value);
		if (node->propertyValuePairs[toLower("AutoRozmiar")])
			widgetPtr->czyAutoRozmiar_ = parseBoolean(node->propertyValuePairs[toLower("AutoRozmiar")]->value);
		
		if (widgetPtr->pokazSuwak_)
			widgetPtr->suwak_->show();
		else
			widgetPtr->suwak_->hide();

		for (auto& childNode : node->children) {
			if (toLower(childNode->name) == toLower("KontrolkaObiektu"))
				widgetPtr->szablonKontrolki_ = std::static_pointer_cast<KontrolkaObiektu>(WidgetLoader::getLoadFunction(toLower("KontrolkaObiektu"))(childNode));
			else if (toLower(childNode->name) == toLower("Scrollbar"))
				widgetPtr->suwak_ = std::static_pointer_cast<Scrollbar>(WidgetLoader::getLoadFunction(toLower("Scrollbar"))(childNode));
		}
		REMOVE_CHILD(toLower("KontrolkaObiektu"));
		REMOVE_CHILD(toLower("Scrollbar"));

		for (auto& ref : widgetPtr->m_panel->getWidgets()) {
			if (ref->getWidgetType() == "KontrolkaObiektu") {
				widgetPtr->kontrolki_.push_back(std::static_pointer_cast<KontrolkaObiektu>(ref));
			}
		}
		if(widgetPtr->suwak_)
			widgetPtr->suwak_->connectEx("ValueChanged", std::bind(&ListaObiektowGui::scrollbarValueChanged, widgetPtr, std::placeholders::_1));

		widgetPtr->uaktualnijShader();
		return widgetPtr;
	}
};