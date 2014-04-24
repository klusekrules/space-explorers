#include "LogListGui.h"

namespace tgui{

	Widget* LogListGui::createWidget(Container* container, const std::string& name){
		return LogListGui::Ptr(*container, name).get();
	}

	bool LogListGui::deleteLastMessage(){
		if (sum_ == 0)
			return false;
		listaObiektow_[pos(static_cast<int>(empty_)-static_cast<int>(sum_--))].second->hide();
		return true;
	}

	bool LogListGui::addMessage(MessageType number, std::string text){
		if (number >= opisTypowKomunikatow_.size())
			return false;
		auto panelSize = Panel::getSize();

		if (sum_ > 0){
			auto prev = listaObiektow_[empty_ == 0 ? max_ - 1 : empty_ - 1];
			prev.second->setTextColor(opisTypowKomunikatow_[prev.first].colorSecondary_);
			prev.second->setTextSize(opisTypowKomunikatow_[prev.first].textSizeSecondary_);
			if (!autoSized_)
				prev.second->setSize(panelSize.x - (margin_.left + margin_.right), opisTypowKomunikatow_[prev.first].textSizeSecondary_);
		}

		auto actual = listaObiektow_[empty_];
		actual.second->setTextColor(opisTypowKomunikatow_[number].colorFirst_);
		actual.second->setTextSize(opisTypowKomunikatow_[number].textSizeFirst_);
		if (!autoSized_)
			actual.second->setSize(panelSize.x - (margin_.left + margin_.right), opisTypowKomunikatow_[number].textSizeFirst_);
		actual.second->setText(text);

		listaObiektow_[empty_].first = number;
		empty_++;
		if (empty_ >= max_)
			empty_ -= max_;
		sum_++;
		if (sum_ >= max_)
			sum_ = max_;
		recalculatePosition();

		return true;
	}
	
	void LogListGui::recalculatePosition(){
		float xPos = 0.f, yPos = 0.f, ySum = 0.f;

		if (wPionie_ == MIDDLE){
			for (unsigned int numer = 1, position = static_cast<unsigned int>(pos(static_cast<int>(empty_)-1)); numer <= sum_; ++numer, position = static_cast<unsigned int>(pos(static_cast<int>(position)-1))){
				ySum += listaObiektow_[position].second->getSize().y + interspace_;
			}
			ySum -= interspace_;
		}

		for (unsigned int numer = 1, position = static_cast<unsigned int>(pos(static_cast<int>(empty_)-1)); numer <= sum_; ++numer, position = static_cast<unsigned int>(pos(static_cast<int>(position)-1))){
			xPos = 0.f;
			auto labelSize = listaObiektow_[position].second->getSize();
			auto panelSize = Panel::getSize();

			switch (wPoziomie_)
			{
			case tgui::LogListGui::LEFT:
				xPos = margin_.left;
				break;
			case tgui::LogListGui::CENTER:
				xPos = (panelSize.x - (margin_.left + margin_.right + labelSize.x)) / 2.f + margin_.left;
				break;
			case tgui::LogListGui::RIGHT:
				xPos  = panelSize.x - (margin_.right + labelSize.x);
				break;
			default:
				break;
			}

			switch (wPionie_)
			{
			case tgui::LogListGui::TOP: 
				if (numer == 1){
					yPos = margin_.top;
				}
				else{
					yPos += interspace_;
				}
				break;
			case tgui::LogListGui::MIDDLE:
				if (numer == 1){
					yPos = (panelSize.y - ySum) / 2.f;
				}
				else{
					yPos += interspace_;
				}
				break;
			case tgui::LogListGui::BOTTOM:
				if (numer == 1){
					yPos = panelSize.y - (margin_.bottom + labelSize.y);
				}
				else{
					yPos -= interspace_ + labelSize.y;
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
		if (!autoSized_){
			float xPos = width - (margin_.left + margin_.right);
			for (auto e : listaObiektow_){
				e.second->setSize(xPos, opisTypowKomunikatow_[e.first].textSizeSecondary_);
			}
		}
		recalculatePosition();
	}
	
	LogListGui* LogListGui::clone(){
		return new LogListGui(*this);
	}

	void LogListGui::clear(){
		sum_ = 0;
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
		std::string configFileFolder = "";
		std::string::size_type slashPos = m_LoadedConfigFile.find_last_of("/\\");
		if (slashPos != std::string::npos)
			configFileFolder = m_LoadedConfigFile.substr(0, slashPos + 1);


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
					autoSized_ = true;
				else if ((value == "false") || (value == "False"))
					autoSized_ = false;
				else
					TGUI_OUTPUT("TGUI error: Failed to parse 'Enabled' property.");
			}
			else if (property == "margin")
			{
				extractBorders(value, margin_);
			}
			else if (property == "lines")
			{
				max_ = std::strtol(value.c_str(), nullptr, 10);
			}
			else if (property == "interspace")
			{
				interspace_ = std::strtof(value.c_str(), nullptr);
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

		if (max_ >= 0){
			listaObiektow_.resize(max_);
			for (unsigned int i = 0; i < max_; ++i){
				listaObiektow_[i] = std::make_pair( 0 ,Label::Ptr(*this, std::to_string(i) ) );
			}
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
		return static_cast<std::vector<Label::Ptr>::size_type>(position < 0 ? max_ + position : position);
	}
};
