
#include <TGUI\KontrolkaObiektu.h>

namespace tgui{

	Widget* KontrolkaObiektu::createWidget(Container* container, const std::string& name){
		return KontrolkaObiektu::Ptr(*container, name).get();
	}

	KontrolkaObiektu::KontrolkaObiektu(){
		background_.data = nullptr;
		m_Callback.widgetType = Type_KontrolkaObiektu;
		m_ContainerWidget = false;
	}

	KontrolkaObiektu::KontrolkaObiektu(const KontrolkaObiektu& copy)
		: Panel(copy), marginUp(copy.marginUp), marginDown(copy.marginDown),
		marginLeft(copy.marginLeft), marginRight(copy.marginRight),
		marginButtonDown(copy.marginButtonDown), marginButtonUp(copy.marginButtonUp),
		marginButtonLeft(copy.marginButtonLeft), marginButtonRight(copy.marginButtonRight),
		ratio(copy.ratio), distance(copy.distance)
	{
		picture_ = this->get<Picture>("ObrazObiektu");
		nazwa_ = this->get<Label>("NazwaObiektu");
		tresc_ = this->get<Label>("OpisObiektu");
		ok_ = this->get<Button>("Rozbuduj");
		can_ = this->get<Button>("Zburz");
	}

	void KontrolkaObiektu::initialize(Container *const container){
		Panel::setGlobalFont(container->getGlobalFont());
		
		picture_ = Picture::Ptr(*this,"ObrazObiektu");
				
		nazwa_ = Label::Ptr(*this, "NazwaObiektu");
		nazwa_->setTextSize(11);
		nazwa_->setText("Nazwa");
		
		tresc_ = Label::Ptr(*this, "OpisObiektu");
		tresc_->setTextSize(10);
		tresc_->setText("Opis \nWieloliniowy.");
		
		ok_ = Button::Ptr(*this, "Rozbuduj");
		ok_->setTextSize(10);
		ok_->setText("Rozbuduj");
		
		can_ = Button::Ptr(*this, "Zburz");
		can_->setTextSize(10);
		can_->setText("Zburz");

		setSize(410.f, 110.f);
	}

	void KontrolkaObiektu::setTransparency(unsigned char transparency){
		Panel::setBackgroundColor(sf::Color(255, 255, 255, transparency));
		Panel::setTransparency(transparency);
		picture_->setTransparency(transparency);

		nazwa_->setTransparency(transparency);
		auto kolor = nazwa_->getTextColor();
		kolor.a = transparency;
		nazwa_->setTextColor(kolor);

		tresc_->setTransparency(transparency);
		kolor = tresc_->getTextColor();
		kolor.a = transparency;
		tresc_->setTextColor(kolor);

		ok_->setTransparency(transparency);
		kolor = ok_->getTextColor();
		kolor.a = transparency;
		ok_->setTextColor(kolor);

		can_->setTransparency(transparency);
		kolor = can_->getTextColor();
		kolor.a = transparency;
		can_->setTextColor(kolor);

	}

	void KontrolkaObiektu::setSize(float width, float hight){

		float absWidth = width - (marginLeft + distance + distance + marginButtonLeft + marginButtonRight + marginRight);
		float absHight = hight - (marginUp + marginDown);

		if (absWidth / absHight > ratio){
			width = absHight*ratio + marginLeft + distance + distance + marginButtonLeft + marginButtonRight + marginRight;
		}
		else{
			if (absWidth / absHight < ratio){
				hight = absWidth / ratio + marginUp + marginDown;
			}
		}

		Panel::setSize(width, hight);

		float pictureSize = hight - (marginUp + marginDown);
		picture_->setPosition(marginUp, marginLeft);
		if (picture_->isLoaded())
			picture_->setSize(pictureSize, pictureSize);

		float secondRow = pictureSize + marginLeft + distance;
		float labelSize = pictureSize + pictureSize;
		float titleHight = labelSize / 18.f;

		nazwa_->setPosition(secondRow, marginUp);
		nazwa_->setSize(labelSize, titleHight);

		tresc_->setPosition(secondRow, marginUp + titleHight + interspace_);
		tresc_->setSize(labelSize, hight - (marginUp + titleHight + interspace_ + marginDown));
		
		float thirdRow = secondRow + labelSize + distance + marginButtonLeft;
		float buttonSize = width - (thirdRow + marginButtonRight + marginRight);
		
		sf::Text tekst;
		tekst.setFont(*(ok_->getTextFont()));
		tekst.setCharacterSize(ok_->getTextSize());

		tekst.setString(ok_->getText());
		auto bounds = tekst.getLocalBounds();
		float buttonHight = bounds.top + bounds.height + 20.f;
		ok_->setPosition(thirdRow, marginUp + marginButtonUp);
		ok_->setSize(buttonSize, buttonHight);

		tekst.setString(can_->getText());
		bounds = tekst.getLocalBounds();
		buttonHight = bounds.top + bounds.height + 20.f;
		can_->setPosition(thirdRow, hight - (buttonHight + marginDown + marginButtonDown));
		can_->setSize(buttonSize, buttonHight);

	}

	KontrolkaObiektu* KontrolkaObiektu::clone(){
		return new KontrolkaObiektu(*this);
	}

	bool KontrolkaObiektu::load(const std::string& configFileFilename){
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
		if (!configFile.read("KontrolkaObiektu", properties, values))
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
			//setTextColor(extractColor(value));
			if (property == "background")
			{				
				if (!configFile.readTexture(value, configFileFolder, background_))
				{
					TGUI_OUTPUT("TGUI error: Failed to parse value for NormalImage in section Button in " + m_LoadedConfigFile + ".");
					return false;
				}
				setBackgroundTexture(&(background_.data->texture));
			}
			else if(property == "nameconfig")
			{
				nazwa_->load(configFileFolder + value);
			}
			else if (property == "describeconfig")
			{
				tresc_->load(configFileFolder + value);
			}
			else if(property == "okconfig")
			{
				ok_->load(configFileFolder + value);
			}
			else if(property == "canconfig")
			{
				can_->load(configFileFolder + value);
			}
			else if(property == "margin")
			{
				Borders margin;
				if (extractBorders(value, margin)){
					marginUp = static_cast<float>(margin.top);
					marginDown = static_cast<float>(margin.bottom);
					marginLeft = static_cast<float>(margin.left);
					marginRight = static_cast<float>(margin.right);
				}
			}
			else if (property == "marginbutton")
			{
				Borders margin;
				if (extractBorders(value, margin)){
					marginButtonUp = static_cast<float>(margin.top);
					marginButtonDown = static_cast<float>(margin.bottom);
					marginButtonLeft = static_cast<float>(margin.left);
					marginButtonRight = static_cast<float>(margin.right);
				}
			}
			else if (property == "ratio")
			{
				ratio = strtof(value.c_str(),nullptr);
			}
			else if (property == "distance")
			{
				distance = strtof(value.c_str(), nullptr);
			}
			else if(property == "interspace")
			{
				interspace_ = std::strtof(value.c_str(), nullptr);
			}
			else
				TGUI_OUTPUT("TGUI warning: Unrecognized property '" + property + "' in section KontrolkaObiektu in " + m_LoadedConfigFile + ".");
		}
		sf::Vector2f temp = getSize();
		setSize(temp.x,temp.y);
		return true;
	}

	const std::string& KontrolkaObiektu::getLoadedConfigFile() const{
		return m_LoadedConfigFile;
	}

	bool KontrolkaObiektu::ustawObrazek(const std::string& obraz){
		return picture_->load(obraz);
	}

	void KontrolkaObiektu::ustawNazwe(const sf::String& tekst){
		nazwa_->setText(tekst);
	}

	void KontrolkaObiektu::ustawOpis(const sf::String& opis){
		tresc_->setText(opis);
	}

	void KontrolkaObiektu::blokowanieOk(bool zablokowane){
		if (zablokowane)
			ok_->disable();
		else
			ok_->enable();
	}

	void KontrolkaObiektu::blokowanieCancel(bool zablokowane){
		if (zablokowane)
			can_->disable();
		else
			can_->enable();
	}

	bool KontrolkaObiektu::setProperty(std::string property, const std::string& value){
		if (property == "image"){
			return picture_->load(value);
		}else if(property == "configfile"){
			return load(value);
		}else
			return Panel::setProperty(property, value);
	}

	bool KontrolkaObiektu::getProperty(std::string property, std::string& value) const{
		if (property == "Image"){
			value = picture_->getLoadedFilename();
			return true;
		}else if(property == "ConfigFile"){
			value = m_LoadedConfigFile;
			return true;
		}else
			return Panel::getProperty(property, value);
	}

	std::list< std::pair<std::string, std::string> > KontrolkaObiektu::getPropertyList() const{
		auto list = Panel::getPropertyList();
		list.push_back(std::pair<std::string, std::string>("ConfigFile", "string"));
		list.push_back(std::pair<std::string, std::string>("Image", "string"));
		return list;
	}

	void KontrolkaObiektu::ustawShader(sf::Shader* shader){
		shader_ = shader;
	}
	
	void KontrolkaObiektu::draw(sf::RenderTarget& target, sf::RenderStates states) const{
		if (shader_ != nullptr){
			states.shader = shader_;
		}
		Panel::draw(target,states);
	}

};
