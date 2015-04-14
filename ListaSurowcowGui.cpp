#include "ListaSurowcowGui.h"
#include "Aplikacja.h"

namespace tgui {

	Widget* ListaSurowcowGui::createWidget(Container* container, const std::string& name){
		return ListaSurowcowGui::Ptr(*container, name).get();
	}
	
	ListaSurowcowGui::ListaSurowcowGui(const ListaSurowcowGui& o)
		: m_LoadedConfigFile_(o.m_LoadedConfigFile_), Panel(o)
	{
		template_ = this->get<SurowiecGui>("Szablon");
		for (auto e : o.objects_){
			std::string nazwa;
			if (o.getWidgetName(e, nazwa)){
				if (!nazwa.empty()){
					objects_.push_back(this->get<SurowiecGui>(nazwa));
				}
			}
		}
	}

	bool ListaSurowcowGui::setProperty(std::string property, const std::string& value){
		if (property == "configfile"){
			return load(value);
		}
		else
			return Panel::setProperty(property, value);
	}

	bool ListaSurowcowGui::getProperty(std::string property, std::string& value) const{
		if (property == "ConfigFile"){
			value = m_LoadedConfigFile_;
			return true;
		}
		else
			return Panel::getProperty(property, value);
	}

	std::list< std::pair<std::string, std::string> > ListaSurowcowGui::getPropertyList() const{
		auto list = Panel::getPropertyList();
		list.push_back(std::pair<std::string, std::string>("ConfigFile", "string"));
		return list;
	}

	void ListaSurowcowGui::initialize(Container *const container){
		Panel::setGlobalFont(container->getGlobalFont());
		template_ = SurowiecGui::Ptr(*this, "Szablon");
		template_->hide();
	}

	void ListaSurowcowGui::setTransparency(unsigned char transparency){
		Panel::setBackgroundColor(sf::Color(255, 255, 255, transparency));
		Panel::setTransparency(transparency);
		template_->setTransparency(transparency);
		for (auto &element : objects_){
			element->setTransparency(transparency);
		}
	}

	ListaSurowcowGui* ListaSurowcowGui::clone(){
		return new ListaSurowcowGui(*this);
	}

	const std::string& ListaSurowcowGui::getLoadedConfigFile() const{
		return m_LoadedConfigFile_;
	}

	void ListaSurowcowGui::draw(sf::RenderTarget& target, sf::RenderStates states) const{
		std::lock_guard<std::mutex> lock(zmianaDanych_);
		Panel::draw(target, states);
	}

	void ListaSurowcowGui::ustawDane(const SpEx::Planeta& planeta){
		auto listaObj = planeta.pobierzSurowce();
		if (objects_.size() == listaObj.size()){ // Je¿eli iloœæ kontrolek jest taka sama, jak iloœæ obiektów to tylko aktualizujemy dane.
			int n = 0;
			for (auto element : objects_)
				element->ustawDane(*listaObj.at(n++));
		}
		else{

			// Usuniêcie niepotrzebnych okien
			for (auto iter = objects_.begin(); iter != objects_.end();){
				if (listaObj.find((*iter)->pobierzIdObiektu()) != listaObj.end()){
					++iter;
				}
				else{
					std::lock_guard<std::mutex> lock(zmianaDanych_);
					this->remove(*iter);
					iter = objects_.erase(iter);
				}
			}

			// Dodanie brakuj¹cych elementów oraz uaktualnienie obecnych.
			auto iter = objects_.begin();
			for (auto &id : listaObj){
				if (iter == objects_.end() || (*iter)->pobierzIdObiektu() != id.first){
					std::lock_guard<std::mutex> lock(zmianaDanych_);
					auto widget = this->copy(template_, id.second->pobierzSurowceInfo().pobierzNazwe()());
					widget->show();
					iter = objects_.emplace(iter, widget);
					/*if (shader_)
						(*iter)->ustawShader(shader_.get());*/
				}
				if (iter != objects_.end()){
					(*iter)->ustawDane(*id.second);
					++iter;
				}
			}
		}
		refreshPosition();
	}
	
	void ListaSurowcowGui::refreshPosition(){
		//auto panelSize = getSize();
		//decltype(panelSize) obszarSize;
		float positionX = 0.f;
		for (auto element : objects_){
			auto temp = element->getSize();
			element->setPosition(positionX, 0.f);
			positionX += temp.x + 20;
		}
		
	}

	void ListaSurowcowGui::setSize(float width, float hight){
		Panel::setSize(width, hight);
		refreshPosition();
	}

	bool ListaSurowcowGui::load(const std::string& configFileFilename){
		// Don't continue when the config file was empty
		if (configFileFilename.empty())
			return true;

		m_LoadedConfigFile_ = getResourcePath() + configFileFilename;

		// Open the config file
		ConfigFile configFile;
		if (!configFile.open(m_LoadedConfigFile_))
		{
			TGUI_OUTPUT("TGUI error: Failed to open " + m_LoadedConfigFile_ + ".");
			return false;
		}

		// Read the properties and their values (as strings)
		std::vector<std::string> properties;
		std::vector<std::string> values;
		if (!configFile.read("ListaSurowcowGui", properties, values))
		{
			TGUI_OUTPUT("TGUI error: Failed to parse " + m_LoadedConfigFile_ + ".");
			return false;
		}

		// Close the config file
		configFile.close();

		// Find the folder that contains the config file
		std::string configFileFolder = "";
		std::string::size_type slashPos = m_LoadedConfigFile_.find_last_of("/\\");
		if (slashPos != std::string::npos)
			configFileFolder = m_LoadedConfigFile_.substr(0, slashPos + 1);

		// Handle the read properties
		for (unsigned int i = 0; i < properties.size(); ++i)
		{
			std::string property = properties[i];
			std::string value = values[i];
			if (property == "templateconfig")
			{
				template_->load(configFileFolder + value);
			}
			else if(property == "textsize")
			{
				template_->setTextSize(std::strtoul(value.c_str(),nullptr,10));
			}
			else if (property == "textcolor")
			{
				template_->setTextColor(extractColor(value));
			}
			else
				TGUI_OUTPUT("TGUI warning: Unrecognized property '" + property + "' in section KontrolkaObiektu in " + m_LoadedConfigFile_ + ".");
		}
		return true;
	}

	

	//-------------
	// SurowiecGui
	//-------------

	ListaSurowcowGui::SurowiecGui::SurowiecGui(const SurowiecGui& o)
		: m_LoadedConfigFile_(o.m_LoadedConfigFile_), Panel(o), idObiektu_(o.idObiektu_)
	{
		tekst_ = this->get<Label>("Nazwa");
	}

	const STyp::Identyfikator& ListaSurowcowGui::SurowiecGui::pobierzIdObiektu() const{
		return idObiektu_;
	}

	bool ListaSurowcowGui::SurowiecGui::setProperty(std::string property, const std::string& value){
		if (property == "configfile"){
			return load(value);
		}
		else
			return Panel::setProperty(property, value);
	}

	bool ListaSurowcowGui::SurowiecGui::getProperty(std::string property, std::string& value) const{
		if (property == "ConfigFile"){
			value = m_LoadedConfigFile_;
			return true;
		}
		else
			return Panel::getProperty(property, value);
	}

	std::list< std::pair<std::string, std::string> > ListaSurowcowGui::SurowiecGui::getPropertyList() const{
		auto list = Panel::getPropertyList();
		list.push_back(std::pair<std::string, std::string>("ConfigFile", "string"));
		return list;
	}

	void ListaSurowcowGui::SurowiecGui::initialize(Container *const container){
		Panel::setGlobalFont(container->getGlobalFont());
		tekst_ = Label::Ptr(*this, "Nazwa");
		Panel::setBackgroundColor(sf::Color::Transparent);
	}

	void ListaSurowcowGui::SurowiecGui::setTransparency(unsigned char transparency){
		Panel::setBackgroundColor(sf::Color(255, 255, 255, transparency));
		Panel::setTransparency(transparency);
		tekst_->setTransparency(transparency);
	}

	ListaSurowcowGui::SurowiecGui* ListaSurowcowGui::SurowiecGui::clone(){
		return new SurowiecGui(*this);
	}

	const std::string& ListaSurowcowGui::SurowiecGui::getLoadedConfigFile() const{
		return m_LoadedConfigFile_;
	}

	void ListaSurowcowGui::SurowiecGui::ustawDane(const SpEx::Obiekt& obiekt){
		std::string napis;
		idObiektu_ = obiekt.pobierzIdentyfikator();
		napis += obiekt.pobierzObiektInfo().pobierzNazwe()() + "\n" + obiekt.pobierzIlosc().napis();
		tekst_->setText(napis);
		auto size = tekst_->getSize();
		setSize(size.x,size.y);
	}
	
	void ListaSurowcowGui::SurowiecGui::setTextSize(unsigned int size){
		tekst_->setTextSize(size);
	}

	void ListaSurowcowGui::SurowiecGui::setTextColor(sf::Color color){
		tekst_->setTextColor(color);
	}
	
	bool ListaSurowcowGui::SurowiecGui::load(const std::string& configFileFilename){
		// Don't continue when the config file was empty
		if (configFileFilename.empty())
			return true;

		m_LoadedConfigFile_ = getResourcePath() + configFileFilename;

		// Open the config file
		ConfigFile configFile;
		if (!configFile.open(m_LoadedConfigFile_))
		{
			TGUI_OUTPUT("TGUI error: Failed to open " + m_LoadedConfigFile_ + ".");
			return false;
		}

		// Read the properties and their values (as strings)
		std::vector<std::string> properties;
		std::vector<std::string> values;
		if (!configFile.read("SurowiecGui", properties, values))
		{
			TGUI_OUTPUT("TGUI error: Failed to parse " + m_LoadedConfigFile_ + ".");
			return false;
		}

		// Close the config file
		configFile.close();

		// Find the folder that contains the config file
		std::string configFileFolder = "";
		std::string::size_type slashPos = m_LoadedConfigFile_.find_last_of("/\\");
		if (slashPos != std::string::npos)
			configFileFolder = m_LoadedConfigFile_.substr(0, slashPos + 1);
		
		// Handle the read properties
		for (unsigned int i = 0; i < properties.size(); ++i)
		{
			std::string property = properties[i];
			std::string value = values[i];
			if (property == "tekstconfig")
			{
				tekst_->load(configFileFolder + value);
			}
			else
				TGUI_OUTPUT("TGUI warning: Unrecognized property '" + property + "' in section KontrolkaObiektu in " + m_LoadedConfigFile_ + ".");
		}
		return true;
	}


};