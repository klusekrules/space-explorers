#include "LogListGui.h"

namespace tgui{

	Widget* LogListGui::createWidget(Container* container, const std::string& name){
		return LogListGui::Ptr(*container, name).get();
	}

	bool LogListGui::deleteLastMessage(){
		if (zajete_ == 0)
			return false;
		listaObiektow_[pos(static_cast<int>(puste_)-static_cast<int>(zajete_--))].second->hide();
		return true;
	}

	bool LogListGui::addMessage(MessageType number, std::string text){
		if (number >= opisTypowKomunikatow_.size())
			return false;
		auto panelSize = Panel::getSize();

		if (zajete_ > 0){
			auto prev = listaObiektow_[puste_ == 0 ? wszystkie_ - 1 : puste_ - 1];
			prev.second->setTextColor(opisTypowKomunikatow_[prev.first].drugiKolor_);
			prev.second->setTextSize(opisTypowKomunikatow_[prev.first].drugiRozmiarCzcionki_);
			if (!czyAutoRozmiar_)
				prev.second->setSize(panelSize.x - static_cast<float>(margines_.left + margines_.right), static_cast<float>(opisTypowKomunikatow_[prev.first].drugiRozmiarCzcionki_));
		}

		auto actual = listaObiektow_[puste_];
		actual.second->setTextColor(opisTypowKomunikatow_[number].pierwszyKolor_);
		actual.second->setTextSize(opisTypowKomunikatow_[number].pierwszyRozmiarCzcionki_);
		if (!czyAutoRozmiar_)
			actual.second->setSize(panelSize.x - static_cast<float>(margines_.left + margines_.right), static_cast<float>(opisTypowKomunikatow_[number].pierwszyRozmiarCzcionki_));
		actual.second->setText(text);

		listaObiektow_[puste_].first = number;
		puste_++;
		if (puste_ >= wszystkie_)
			puste_ -= wszystkie_;
		zajete_++;
		if (zajete_ >= wszystkie_)
			zajete_ = wszystkie_;
		recalculatePosition();

		return true;
	}
	
	void LogListGui::recalculatePosition(){
		float yPos = 0.f, ySum = 0.f;

		if (wPionie_ == MIDDLE){
			for (unsigned int numer = 1, position = static_cast<unsigned int>(pos(static_cast<int>(puste_)-1)); numer <= zajete_; ++numer, position = static_cast<unsigned int>(pos(static_cast<int>(position)-1))){
				ySum += listaObiektow_[position].second->getSize().y + odstep_;
			}
			ySum -= odstep_;
		}

		for (unsigned int numer = 1, position = static_cast<unsigned int>(pos(static_cast<int>(puste_)-1)); numer <= zajete_; ++numer, position = static_cast<unsigned int>(pos(static_cast<int>(position)-1))){
			float xPos = 0.f;
			auto labelSize = listaObiektow_[position].second->getSize();
			auto panelSize = Panel::getSize();

			switch (wPoziomie_)
			{
			case tgui::LEFT:
				xPos = static_cast<float>(margines_.left);
				break;
			case tgui::CENTER:
				xPos = (panelSize.x - (margines_.left + margines_.right + labelSize.x)) / 2.f + margines_.left;
				break;
			case tgui::RIGHT:
				xPos = panelSize.x - (margines_.right + labelSize.x);
				break;
			default:
				break;
			}

			switch (wPionie_)
			{
			case tgui::TOP: 
				if (numer == 1){
					yPos = static_cast<float>(margines_.top);
				}else{
					yPos += odstep_;
				}
				break;
			case tgui::MIDDLE:
				if (numer == 1){
					yPos = (panelSize.y - ySum) / 2.f;
				}else{
					yPos += odstep_;
				}
				break;
			case tgui::BOTTOM:
				if (numer == 1){
					yPos = panelSize.y - (margines_.bottom + labelSize.y);
				}else{
					yPos -= odstep_ + labelSize.y;
				}
				break;
			default:
				break;
			}
			
			listaObiektow_[position].second->setPosition(xPos,yPos);

			if (wPionie_ != BOTTOM){
				yPos += labelSize.y;
			}
		}
	}

	void LogListGui::setSize(float width, float hight){
		Panel::setSize(width,hight);
		if (!czyAutoRozmiar_){
			float xPos = width - (margines_.left + margines_.right);
			for (auto e : listaObiektow_){
				e.second->setSize(xPos, static_cast<float>(opisTypowKomunikatow_[e.first].drugiRozmiarCzcionki_));
			}
		}
		recalculatePosition();
	}
	
	LogListGui* LogListGui::clone(){
		return new LogListGui(*this);
	}

	void LogListGui::clear(){
		zajete_ = 0;
		for (auto e : listaObiektow_)
			e.second->hide();
	}

	const std::string& LogListGui::getLoadedConfigFile() const{
		return m_LoadedConfigFile;
	}

	bool LogListGui::load(const std::string& configFileFilename){
		// Don't continue when the config file was empty
		if (configFileFilename.empty())
			return true;

		m_LoadedConfigFile = getResourcePath() + configFileFilename;

		// Open the config file
		ConfigFile configFile;
		if (!configFile.open(m_LoadedConfigFile))
		{
			TGUI_OUTPUT("TGUI error: Failed to open " + m_LoadedConfigFile + ".");
			return false;
		}

		// Read the properties and their values (as strings)
		std::vector<std::string> properties;
		std::vector<std::string> values;
		if (!configFile.read("LogListGui", properties, values))
		{
			TGUI_OUTPUT("TGUI error: Failed to parse " + m_LoadedConfigFile + ".");
			return false;
		}

		// Close the config file
		configFile.close();

		// Find the folder that contains the config file
		/*std::string configFileFolder = "";
		std::string::size_type slashPos = m_LoadedConfigFile.find_last_of("/\\");
		if (slashPos != std::string::npos)
			configFileFolder = m_LoadedConfigFile.substr(0, slashPos + 1);*/


		// Handle the read properties
		for (unsigned int i = 0; i < properties.size(); ++i)
		{
			std::string property = properties[i];
			std::string value = values[i];
			if (property == "messagetype")
			{
				sf::Vector2u temp;

				sf::Color first = extractColor(value);
				auto pos = value.find_first_of(')');
				value.erase(0, pos + 1);

				sf::Color secondary = extractColor(value);
				pos = value.find_first_of(')');
				value.erase(0, pos + 1);

				if (extractVector2u(value, temp))
					opisTypowKomunikatow_.emplace_back(first,secondary,temp.x,temp.y);

			}
			else if (property == "autosize")
			{
				if ((value == "true") || (value == "True"))
					czyAutoRozmiar_ = true;
				else if ((value == "false") || (value == "False"))
					czyAutoRozmiar_ = false;
				else
					TGUI_OUTPUT("TGUI error: Failed to parse 'Enabled' property.");
			}
			else if (property == "margin")
			{
				extractBorders(value, margines_);
			}
			else if (property == "lines")
			{
				wszystkie_ = std::strtol(value.c_str(), nullptr, 10);
			}
			else if (property == "interspace")
			{
				odstep_ = std::strtof(value.c_str(), nullptr);
			}
			else if (property == "horizontal")
			{
				if ((value == "left") || (value == "Left"))
					wPoziomie_ = LEFT;
				else if ((value == "center") || (value == "Center"))
					wPoziomie_ = CENTER;
				else if ((value == "right") || (value == "Right"))
					wPoziomie_ = RIGHT;
				else
					TGUI_OUTPUT("TGUI error: Failed to parse 'Enabled' property.");
			}
			else if (property == "vertical")
			{
				if ((value == "top") || (value == "Top"))
					wPionie_ = TOP;
				else if ((value == "middle") || (value == "Middle"))
					wPionie_ = MIDDLE;
				else if ((value == "bottom") || (value == "Bottom"))
					wPionie_ = BOTTOM;
				else
					TGUI_OUTPUT("TGUI error: Failed to parse 'Enabled' property.");
			}
			else
				TGUI_OUTPUT("TGUI warning: Unrecognized property '" + property + "' in section KontrolkaObiektu in " + m_LoadedConfigFile + ".");
		}

		listaObiektow_.resize(wszystkie_);
		for (unsigned int i = 0; i < wszystkie_; ++i){
			listaObiektow_[i] = std::make_pair( 0 ,Label::Ptr(*this, std::to_string(i) ) );
		}
		return true;
	}

	bool LogListGui::setProperty(std::string property, const std::string& value){
		if (property == "configfile"){
			return load(value);
		}
		else
			return Panel::setProperty(property, value);
	}

	bool LogListGui::getProperty(std::string property, std::string& value) const{
		if (property == "ConfigFile"){
			value = m_LoadedConfigFile;
			return true;
		}
		else
			return Panel::getProperty(property, value);
	}

	std::list< std::pair<std::string, std::string> > LogListGui::getPropertyList() const{
		auto list = Panel::getPropertyList();
		list.push_back(std::pair<std::string, std::string>("ConfigFile", "string"));
		return list;
	}

	void LogListGui::initialize(Container *const container){
		Panel::setGlobalFont(container->getGlobalFont());
	}

	std::vector<Label::Ptr>::size_type LogListGui::pos(int position)const{
		return static_cast<std::vector<Label::Ptr>::size_type>(position < 0 ? wszystkie_ + position : position);
	}
};
