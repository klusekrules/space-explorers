
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
		: Panel(copy), size_(copy.size_),pictureRect_(copy.pictureRect_),titleRect_(copy.titleRect_),
		DescribeRect_(copy.DescribeRect_), ButtonOKRect_(copy.ButtonOKRect_), ButtonCanRect_(copy.ButtonCanRect_),
		constSize_(copy.constSize_), propotional_(copy.propotional_)
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

		float absWidth = width;
		float absHight = hight;

		if (constSize_){
			absWidth = size_.x;
			absHight = size_.y;
		}else{
			if (propotional_){
				auto ratio = size_.x / size_.y;
				if (absWidth / absHight > ratio ) {
					absWidth = absHight * ratio;
				}else{
					if (absWidth / absHight < ratio){
						absHight = absWidth / ratio;
					}
				}
			}
		}

		Panel::setSize(absWidth, absHight);

		picture_->setPosition(pictureRect_.left * absWidth, pictureRect_.top * absHight);
		if (picture_->isLoaded())
			picture_->setSize(pictureRect_.width * absWidth, pictureRect_.height * absHight);

		nazwa_->setPosition(titleRect_.left * absWidth, titleRect_.top * absHight);
		nazwa_->setSize(titleRect_.width * absWidth, titleRect_.height * absHight);

		tresc_->setPosition(DescribeRect_.left * absWidth, DescribeRect_.top * absHight);
		tresc_->setSize(DescribeRect_.width * absWidth, DescribeRect_.height * absHight);

		ok_->setPosition(ButtonOKRect_.left * absWidth, ButtonOKRect_.top * absHight);
		ok_->setSize(ButtonOKRect_.width * absWidth, ButtonOKRect_.height * absHight);

		can_->setPosition(ButtonCanRect_.left * absWidth, ButtonCanRect_.top * absHight);
		can_->setSize(ButtonCanRect_.width * absWidth, ButtonCanRect_.height * absHight);
		
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
			else if (property == "titletextsize")
			{
				nazwa_->setTextSize(std::strtol(value.c_str(), nullptr, 10));
			}
			else if (property == "describetextsize")
			{
				tresc_->setTextSize(std::strtol(value.c_str(), nullptr, 10));
			}
			else if (property == "buttonoktextsize")
			{
				ok_->setTextSize(std::strtol(value.c_str(), nullptr, 10));
			}
			else if (property == "buttoncantextsize")
			{
				can_->setTextSize(std::strtol(value.c_str(),nullptr,10));
			}
			else if (property == "titletextcolor")
			{
				nazwa_->setTextColor(extractColor(value));
			}
			else if (property == "describetextcolor")
			{
				tresc_->setTextColor(extractColor(value));
			}
			else if (property == "buttonoktextcolor")
			{
				ok_->setTextColor(extractColor(value));
			}
			else if (property == "buttoncantextcolor")
			{
				can_->setTextColor(extractColor(value));
			}
			else if (property == "canconfig")
			{
				can_->load(configFileFolder + value);
			}
			else if (property == "nameconfig")
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
			else if(property == "size")
			{
				sf::Vector2u temp;
				extractVector2u(value, temp);
				size_.x = static_cast<float>(temp.x);
				size_.y = static_cast<float>(temp.y);
			}
			else if (property == "picturerect")
			{
				Borders temp;
				extractBorders(value, temp);
				pictureRect_.left = static_cast<float>(temp.left);
				pictureRect_.top = static_cast<float>(temp.top);
				pictureRect_.width = static_cast<float>(temp.right);
				pictureRect_.height = static_cast<float>(temp.bottom);
			}
			else if (property == "titlerect")
			{
				Borders temp;
				extractBorders(value, temp);
				titleRect_.left = static_cast<float>(temp.left);
				titleRect_.top = static_cast<float>(temp.top);
				titleRect_.width = static_cast<float>(temp.right);
				titleRect_.height = static_cast<float>(temp.bottom);
			}
			else if (property == "describerect")
			{
				Borders temp;
				extractBorders(value, temp);
				DescribeRect_.left = static_cast<float>(temp.left);
				DescribeRect_.top = static_cast<float>(temp.top);
				DescribeRect_.width = static_cast<float>(temp.right);
				DescribeRect_.height = static_cast<float>(temp.bottom);
			}
			else if (property == "buttonokrect")
			{
				Borders temp;
				extractBorders(value, temp);
				ButtonOKRect_.left = static_cast<float>(temp.left);
				ButtonOKRect_.top = static_cast<float>(temp.top);
				ButtonOKRect_.width = static_cast<float>(temp.right);
				ButtonOKRect_.height = static_cast<float>(temp.bottom);
			}
			else if (property == "buttoncanrect")
			{
				Borders temp;
				extractBorders(value, temp);
				ButtonCanRect_.left = static_cast<float>(temp.left);
				ButtonCanRect_.top = static_cast<float>(temp.top);
				ButtonCanRect_.width = static_cast<float>(temp.right);
				ButtonCanRect_.height = static_cast<float>(temp.bottom);
			}
			else if (property == "proportional")
			{
				if ((value == "true") || (value == "True"))
					propotional_ = true;
				else if ((value == "false") || (value == "False"))
					propotional_ = false;
				else
					TGUI_OUTPUT("TGUI error: Failed to parse 'Enabled' property.");
			}
			else if (property == "constsize")
			{
				if ((value == "true") || (value == "True"))
					constSize_ = true;
				else if ((value == "false") || (value == "False"))
					constSize_ = false;
				else
					TGUI_OUTPUT("TGUI error: Failed to parse 'Enabled' property.");
			}
			else
				TGUI_OUTPUT("TGUI warning: Unrecognized property '" + property + "' in section KontrolkaObiektu in " + m_LoadedConfigFile + ".");
		}

		float percent = 100.f;
		if (size_.x > 0){
			percent = size_.x;
		}
		pictureRect_.left /= percent;
		pictureRect_.width /= percent;

		titleRect_.left /= percent;
		titleRect_.width /= percent;

		DescribeRect_.left /= percent;
		DescribeRect_.width /= percent;

		ButtonOKRect_.left /= percent;
		ButtonOKRect_.width /= percent;

		ButtonCanRect_.left /= percent;
		ButtonCanRect_.width /= percent;

		percent = 100.f;
		if (size_.y > 0){
			percent = size_.y;
		}
		pictureRect_.top /= percent;
		pictureRect_.height /= percent;

		titleRect_.top /= percent;
		titleRect_.height /= percent;

		DescribeRect_.top /= percent;
		DescribeRect_.height /= percent;

		ButtonOKRect_.top /= percent;
		ButtonOKRect_.height /= percent;

		ButtonCanRect_.top /= percent;
		ButtonCanRect_.height /= percent;

		setSize(size_.x, size_.y);
		return true;
	}

	const std::string& KontrolkaObiektu::getLoadedConfigFile() const{
		return m_LoadedConfigFile;
	}

	bool KontrolkaObiektu::ustawObrazek(const std::string& obraz){
		return picture_->load(obraz);
	}

	void KontrolkaObiektu::ustawNazwe(const std::string& tekst){
		nazwa_->setText(tekst);
	}

	void KontrolkaObiektu::ustawOpis(const std::string& opis){
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
