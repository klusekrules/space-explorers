#include "KontrolkaObiektu.h"
#include "UtilsGui.h"
#include "Planeta.h"
#include "Aplikacja.h"

namespace tgui{
	
	void convertFromBorderToRect(const Borders& borders, sf::Rect<float>& rectangle){
		rectangle.left = static_cast<float>(borders.left);
		rectangle.top = static_cast<float>(borders.top);
		rectangle.width = static_cast<float>(borders.right);
		rectangle.height = static_cast<float>(borders.bottom);
	}

	void normalizujRect(sf::Rect<float>& rect, float leftWidth, float topHeight){
		rect.left /= leftWidth;
		rect.width /= leftWidth;
		rect.top /= topHeight;
		rect.height /= topHeight;
	}

	KontrolkaObiektu::KontrolkaObiektu(){
		tlo_.data = nullptr;
		m_Callback.widgetType = Type_KontrolkaObiektu;
		m_ContainerWidget = false;
	}

	KontrolkaObiektu::KontrolkaObiektu(const KontrolkaObiektu& copy)
		: Panel(copy), 
		rozmiarKontrolki_(copy.rozmiarKontrolki_), 
		obrazRect_(copy.obrazRect_), 

		nazwaRect_(copy.nazwaRect_),
		nazwaWyrownanieHoryzontalne_(copy.nazwaWyrownanieHoryzontalne_),
		nazwaWyrownanieWertykalne_(copy.nazwaWyrownanieWertykalne_),

		trescRect_(copy.trescRect_),
		trescWyrownanieHoryzontalne_(copy.trescWyrownanieHoryzontalne_),
		trescWyrownanieWertykalne_(copy.trescWyrownanieWertykalne_),
		
		czasRozbudowyRect_(copy.czasRozbudowyRect_),
		czasRozbudowyWyrownanieHoryzontalne_(copy.czasRozbudowyWyrownanieHoryzontalne_),
		czasRozbudowyWyrownanieWertykalne_(copy.czasRozbudowyWyrownanieWertykalne_),

		czasZburzeniaRect_(copy.czasZburzeniaRect_),
		czasZburzeniaWyrownanieHoryzontalne_(copy.czasZburzeniaWyrownanieHoryzontalne_),
		czasZburzeniaWyrownanieWertykalne_(copy.czasZburzeniaWyrownanieWertykalne_),
		
		rozbudujRect_(copy.rozbudujRect_),
		idZdarzeniaBudowy_(copy.idZdarzeniaBudowy_),

		zniszczRect_(copy.zniszczRect_),
		idZdarzeniaBurzenia_(copy.idZdarzeniaBurzenia_),

		idZdarzeniaKlikniecia_(copy.idZdarzeniaKlikniecia_),
		idObiektu_(copy.idObiektu_),
		czyStalyRozmiar_(copy.czyStalyRozmiar_),
		czyProporcjonalny_(copy.czyProporcjonalny_)

	{
		obraz_ = this->get<Picture>("ObrazObiektu");
		nazwa_ = this->get<Label>("NazwaObiektu");
		tresc_ = this->get<Label>("OpisObiektu");
		rozbuduj_ = this->get<Button>("Rozbuduj");
		zniszcz_ = this->get<Button>("Zburz");
		czasRozbudowy_ = this->get<Label>("CzasRozbudowy");
		czasZburzenia_ = this->get<Label>("CzasZburzenia");
	}

	sf::Rect<float> KontrolkaObiektu::pozycjonujLabel(Label::Ptr label, const sf::Rect<float>& rect, float width, float height, WYROWNANIE_HORYZONTALNE horyzontalne, WYROWNANIE_WERTYKALNE wertykalne ){
		sf::Text text;
		text.setFont(*label->getTextFont());
		text.setCharacterSize(label->getTextSize());
		text.setString(label->getText());
		auto bounds = text.getLocalBounds();
		bounds.width += bounds.left;
		bounds.height += bounds.top;
		sf::Rect<float> labelRect(rect.left*width, rect.top*height, rect.width*width, rect.height*height);
		switch (horyzontalne)
		{
		case tgui::LEFT:
			break;
		case tgui::CENTER:
			if (labelRect.width >= bounds.width){
				labelRect.left += (labelRect.width - bounds.width) / 2;
				labelRect.width = bounds.width;
			}
			break;
		case tgui::RIGHT:
			if (labelRect.width >= bounds.width){
				labelRect.left += labelRect.width - bounds.width;
				labelRect.width = bounds.width;
			}			
			break;
		}
		switch (wertykalne)
		{
		case tgui::TOP:
			break;
		case tgui::MIDDLE:
			if (labelRect.height >= bounds.height){
				labelRect.top += (labelRect.height - bounds.height) / 2;
				labelRect.height = bounds.height;
			}
			break;
		case tgui::BOTTOM:
			if (labelRect.height >= bounds.height){
				labelRect.top += labelRect.height - bounds.height;
				labelRect.height = bounds.height;
			}
			break;
		}
		return labelRect;
	}

	Widget* KontrolkaObiektu::createWidget(Container* container, const std::string& name){
		return KontrolkaObiektu::Ptr(*container, name).get();
	}
	
	void KontrolkaObiektu::initialize(Container *const container){
		Panel::setGlobalFont(container->getGlobalFont());
		
		obraz_ = Picture::Ptr(*this, "ObrazObiektu");
				
		nazwa_ = Label::Ptr(*this, "NazwaObiektu");
		nazwa_->setTextSize(11);
		nazwa_->setText("Nazwa");
		
		tresc_ = Label::Ptr(*this, "OpisObiektu");
		tresc_->setTextSize(10);
		tresc_->setText("Opis \nWieloliniowy.");

		czasRozbudowy_ = Label::Ptr(*this, "CzasRozbudowy");
		czasRozbudowy_->setTextSize(11);
		czasRozbudowy_->setText("00:00:00");

		czasZburzenia_ = Label::Ptr(*this, "CzasZburzenia");
		czasZburzenia_->setTextSize(11);
		czasZburzenia_->setText("00:00:00");
		
		rozbuduj_ = Button::Ptr(*this, "Rozbuduj");
		rozbuduj_->setTextSize(10);
		rozbuduj_->setText("Rozbuduj");
		
		zniszcz_ = Button::Ptr(*this, "Zburz");
		zniszcz_->setTextSize(10);
		zniszcz_->setText("Zburz");

		setSize(410.f, 110.f);
	}

	void KontrolkaObiektu::setTransparency(unsigned char transparency){
		Panel::setBackgroundColor(sf::Color(255, 255, 255, transparency));
		Panel::setTransparency(transparency);
		obraz_->setTransparency(transparency);

		nazwa_->setTransparency(transparency);
		auto kolor = nazwa_->getTextColor();
		kolor.a = transparency;
		nazwa_->setTextColor(kolor);

		tresc_->setTransparency(transparency);
		kolor = tresc_->getTextColor();
		kolor.a = transparency;
		tresc_->setTextColor(kolor);

		czasRozbudowy_->setTransparency(transparency);
		kolor = czasRozbudowy_->getTextColor();
		kolor.a = transparency;
		czasRozbudowy_->setTextColor(kolor);

		czasZburzenia_->setTransparency(transparency);
		kolor = czasZburzenia_->getTextColor();
		kolor.a = transparency;
		czasZburzenia_->setTextColor(kolor);

		rozbuduj_->setTransparency(transparency);
		kolor = rozbuduj_->getTextColor();
		kolor.a = transparency;
		rozbuduj_->setTextColor(kolor);

		zniszcz_->setTransparency(transparency);
		kolor = zniszcz_->getTextColor();
		kolor.a = transparency;
		zniszcz_->setTextColor(kolor);

	}

	void KontrolkaObiektu::setSize(float width, float hight){

		float absWidth = width;
		float absHight = hight;

		if (czyStalyRozmiar_){
			absWidth = rozmiarKontrolki_.x;
			absHight = rozmiarKontrolki_.y;
		}else{
			if (czyProporcjonalny_){
				auto ratio = rozmiarKontrolki_.x / rozmiarKontrolki_.y;
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

		obraz_->setPosition(obrazRect_.left * absWidth, obrazRect_.top * absHight);
		if (obraz_->isLoaded())
			obraz_->setSize(obrazRect_.width * absWidth, obrazRect_.height * absHight);

		auto nazwaRect = pozycjonujLabel(nazwa_, nazwaRect_, absWidth, absHight, nazwaWyrownanieHoryzontalne_, nazwaWyrownanieWertykalne_);
		nazwa_->setPosition(nazwaRect.left, nazwaRect.top);
		nazwa_->setSize(nazwaRect.width, nazwaRect.height);

		auto trescRect = pozycjonujLabel(tresc_, trescRect_, absWidth, absHight, trescWyrownanieHoryzontalne_, trescWyrownanieWertykalne_);
		tresc_->setPosition(trescRect.left, trescRect.top);
		tresc_->setSize(trescRect.width, trescRect.height);

		auto czasRozbudowyRect = pozycjonujLabel(czasRozbudowy_, czasRozbudowyRect_, absWidth, absHight, czasRozbudowyWyrownanieHoryzontalne_,czasRozbudowyWyrownanieWertykalne_);
		czasRozbudowy_->setPosition(czasRozbudowyRect.left, czasRozbudowyRect.top);
		czasRozbudowy_->setSize(czasRozbudowyRect.width, czasRozbudowyRect.height);

		auto czasZburzeniaRect = pozycjonujLabel(czasZburzenia_, czasZburzeniaRect_, absWidth, absHight, czasZburzeniaWyrownanieHoryzontalne_, czasZburzeniaWyrownanieWertykalne_);
		czasZburzenia_->setPosition(czasZburzeniaRect.left, czasZburzeniaRect.top);
		czasZburzenia_->setSize(czasZburzeniaRect.width, czasZburzeniaRect.height);

		rozbuduj_->setPosition(rozbudujRect_.left * absWidth, rozbudujRect_.top * absHight);
		rozbuduj_->setSize(rozbudujRect_.width * absWidth, rozbudujRect_.height * absHight);

		zniszcz_->setPosition(zniszczRect_.left * absWidth, zniszczRect_.top * absHight);
		zniszcz_->setSize(zniszczRect_.width * absWidth, zniszczRect_.height * absHight);
		
	}

	KontrolkaObiektu* KontrolkaObiektu::clone(){
		return new KontrolkaObiektu(*this);
	}

	bool KontrolkaObiektu::load(const std::string& configFileFilename){
		// Don't continue when the config file was empty
		if (configFileFilename.empty())
			return true;

		plikKonfiguracyjny_ = getResourcePath() + configFileFilename;

		// Open the config file
		ConfigFile configFile;
		if (!configFile.open(plikKonfiguracyjny_))
		{
			TGUI_OUTPUT("TGUI error: Failed to open " + plikKonfiguracyjny_ + ".");
			return false;
		}

		// Read the properties and their values (as strings)
		std::vector<std::string> properties;
		std::vector<std::string> values;
		if (!configFile.read("KontrolkaObiektu", properties, values))
		{
			TGUI_OUTPUT("TGUI error: Failed to parse " + plikKonfiguracyjny_ + ".");
			return false;
		}

		// Close the config file
		configFile.close();

		// Find the folder that contains the config file
		std::string configFileFolder = "";
		std::string::size_type slashPos = plikKonfiguracyjny_.find_last_of("/\\");
		if (slashPos != std::string::npos)
			configFileFolder = plikKonfiguracyjny_.substr(0, slashPos + 1);


		// Handle the read properties
		for (unsigned int i = 0; i < properties.size(); ++i)
		{
			std::string property = properties[i];
			std::string value = values[i];
			//setTextColor(extractColor(value));
			if (property == "background")
			{				
				if (!configFile.readTexture(value, configFileFolder, tlo_))
				{
					TGUI_OUTPUT("TGUI error: Failed to parse value for NormalImage in section Button in " + plikKonfiguracyjny_ + ".");
					return false;
				}
				setBackgroundTexture(&(tlo_.data->texture));
			}
			else if (property == "titletextsize")
			{
				nazwa_->setTextSize(std::strtol(value.c_str(), nullptr, 10));
			}
			else if (property == "describetextsize")
			{
				tresc_->setTextSize(std::strtol(value.c_str(), nullptr, 10));
			}
			else if (property == "buttonrozbudujtextsize")
			{
				rozbuduj_->setTextSize(std::strtol(value.c_str(), nullptr, 10));
			}
			else if (property == "buttonzniszcztextsize")
			{
				zniszcz_->setTextSize(std::strtol(value.c_str(), nullptr, 10));
			}
			else if (property == "czasrozbudowytextsize")
			{
				czasRozbudowy_->setTextSize(std::strtol(value.c_str(), nullptr, 10));
			}
			else if (property == "czaszburzeniatextsize")
			{
				czasZburzenia_->setTextSize(std::strtol(value.c_str(), nullptr, 10));
			}
			else if (property == "titletextcolor")
			{
				nazwa_->setTextColor(extractColor(value));
			}
			else if (property == "describetextcolor")
			{
				tresc_->setTextColor(extractColor(value));
			}
			else if (property == "buttonrozbudujtextcolor")
			{
				rozbuduj_->setTextColor(extractColor(value));
			}
			else if (property == "buttonzniszcztextcolor")
			{
				zniszcz_->setTextColor(extractColor(value));
			}
			else if (property == "czasrozbudowytextcolor")
			{
				czasRozbudowy_->setTextColor(extractColor(value));
			}
			else if (property == "czaszburzeniatextcolor")
			{
				czasZburzenia_->setTextColor(extractColor(value));
			}
			else if (property == "titleconfig")
			{
				nazwa_->load(configFileFolder + value);
			}
			else if (property == "describeconfig")
			{
				tresc_->load(configFileFolder + value);
			}
			else if (property == "czasrozbudowyconfig")
			{
				czasRozbudowy_->load(configFileFolder + value);
			}
			else if (property == "czaszburzeniaconfig")
			{
				czasZburzenia_->load(configFileFolder + value);
			}
			else if (property == "buttonrozbudujconfig")
			{
				rozbuduj_->load(configFileFolder + value);
			}
			else if(property == "buttonzniszczconfig")
			{
				zniszcz_->load(configFileFolder + value);
			}
			else if(property == "size")
			{
				sf::Vector2u temp;
				extractVector2u(value, temp);
				rozmiarKontrolki_.x = static_cast<float>(temp.x);
				rozmiarKontrolki_.y = static_cast<float>(temp.y);
			}
			else if (property == "picturerect")
			{
				Borders temp;
				extractBorders(value, temp);
				convertFromBorderToRect(temp, obrazRect_);
			}
			else if (property == "titlerect")
			{
				Borders temp;
				extractBorders(value, temp);
				convertFromBorderToRect(temp, nazwaRect_);
			}
			else if (property == "describerect")
			{
				Borders temp;
				extractBorders(value, temp);
				convertFromBorderToRect(temp, trescRect_);
			}
			else if (property == "buttonrozbudujrect")
			{
				Borders temp;
				extractBorders(value, temp);
				convertFromBorderToRect(temp, rozbudujRect_);
			}
			else if (property == "buttonzniszczrect")
			{
				Borders temp;
				extractBorders(value, temp);
				convertFromBorderToRect(temp, zniszczRect_);
			}
			else if (property == "czasrozbudowyrect")
			{
				Borders temp;
				extractBorders(value, temp);
				convertFromBorderToRect(temp, czasRozbudowyRect_);
			}
			else if (property == "czaszburzeniarect")
			{
				Borders temp;
				extractBorders(value, temp);
				convertFromBorderToRect(temp, czasZburzeniaRect_);
			}
			else if (property == "czaszburzeniatexthaling")
			{
				if ((value == "left") || (value == "Left"))
					czasZburzeniaWyrownanieHoryzontalne_ = LEFT;
				else if ((value == "center") || (value == "Center"))
					czasZburzeniaWyrownanieHoryzontalne_ = CENTER;
				else if ((value == "right") || (value == "Right"))
					czasZburzeniaWyrownanieHoryzontalne_ = RIGHT;
				else
					TGUI_OUTPUT("TGUI error: Failed to parse 'czaszburzeniatexthaling' property.");
			}
			else if (property == "czaszburzeniatextvaling")
			{
				if ((value == "top") || (value == "Top"))
					czasZburzeniaWyrownanieWertykalne_ = TOP;
				else if ((value == "middle") || (value == "Middle"))
					czasZburzeniaWyrownanieWertykalne_ = MIDDLE;
				else if ((value == "bottom") || (value == "Bottom"))
					czasZburzeniaWyrownanieWertykalne_ = BOTTOM;
				else
					TGUI_OUTPUT("TGUI error: Failed to parse 'czaszburzeniatextvaling' property.");
			}
			else if (property == "czasrozbudowytexthaling")
			{
				if ((value == "left") || (value == "Left"))
					czasRozbudowyWyrownanieHoryzontalne_ = LEFT;
				else if ((value == "center") || (value == "Center"))
					czasRozbudowyWyrownanieHoryzontalne_ = CENTER;
				else if((value == "right") || (value == "Right"))
					czasRozbudowyWyrownanieHoryzontalne_ = RIGHT;
				else 
					TGUI_OUTPUT("TGUI error: Failed to parse 'czasrozbudowytexthaling' property.");
			}
			else if (property == "czasrozbudowytextvaling")
			{
				if ((value == "top") || (value == "Top"))
					czasRozbudowyWyrownanieWertykalne_ = TOP;
				else if ((value == "middle") || (value == "Middle"))
					czasRozbudowyWyrownanieWertykalne_ = MIDDLE;
				else if ((value == "bottom") || (value == "Bottom"))
					czasRozbudowyWyrownanieWertykalne_ = BOTTOM;
				else
					TGUI_OUTPUT("TGUI error: Failed to parse 'czasrozbudowytextvaling' property.");
			}
			else if (property == "titletexthaling")
			{
				if ((value == "left") || (value == "Left"))
					nazwaWyrownanieHoryzontalne_ = LEFT;
				else if ((value == "center") || (value == "Center"))
					nazwaWyrownanieHoryzontalne_ = CENTER;
				else if ((value == "right") || (value == "Right"))
					nazwaWyrownanieHoryzontalne_ = RIGHT;
				else
					TGUI_OUTPUT("TGUI error: Failed to parse 'titletexthaling' property.");
			}
			else if (property == "titletextvaling")
			{
				if ((value == "top") || (value == "Top"))
					nazwaWyrownanieWertykalne_ = TOP;
				else if ((value == "middle") || (value == "Middle"))
					nazwaWyrownanieWertykalne_ = MIDDLE;
				else if ((value == "bottom") || (value == "Bottom"))
					nazwaWyrownanieWertykalne_ = BOTTOM;
				else
					TGUI_OUTPUT("TGUI error: Failed to parse 'titletextvaling' property.");
			}
			else if (property == "describetexthaling")
			{
				if ((value == "left") || (value == "Left"))
					trescWyrownanieHoryzontalne_ = LEFT;
				else if ((value == "center") || (value == "Center"))
					trescWyrownanieHoryzontalne_ = CENTER;
				else if ((value == "right") || (value == "Right"))
					trescWyrownanieHoryzontalne_ = RIGHT;
				else
					TGUI_OUTPUT("TGUI error: Failed to parse 'describetexthaling' property.");
			}
			else if (property == "describetextvaling")
			{
				if ((value == "top") || (value == "Top"))
					trescWyrownanieWertykalne_ = TOP;
				else if ((value == "middle") || (value == "Middle"))
					trescWyrownanieWertykalne_ = MIDDLE;
				else if ((value == "bottom") || (value == "Bottom"))
					trescWyrownanieWertykalne_ = BOTTOM;
				else
					TGUI_OUTPUT("TGUI error: Failed to parse 'describetextvaling' property.");
			}
			else if (property == "proportional")
			{
				if ((value == "true") || (value == "True"))
					czyProporcjonalny_ = true;
				else if ((value == "false") || (value == "False"))
					czyProporcjonalny_ = false;
				else
					TGUI_OUTPUT("TGUI error: Failed to parse 'proportional' property.");
			}
			else if (property == "constsize")
			{
				if ((value == "true") || (value == "True"))
					czyStalyRozmiar_ = true;
				else if ((value == "false") || (value == "False"))
					czyStalyRozmiar_ = false;
				else
					TGUI_OUTPUT("TGUI error: Failed to parse 'constsize' property.");
			}
			else
				TGUI_OUTPUT("TGUI warning: Unrecognized property '" + property + "' in section KontrolkaObiektu in " + plikKonfiguracyjny_ + ".");
		}

		float percentLW = 100.f;
		if (rozmiarKontrolki_.x > 0){
			percentLW = rozmiarKontrolki_.x;
		}

		float percentTH = 100.f;
		if (rozmiarKontrolki_.y > 0){
			percentTH = rozmiarKontrolki_.y;
		}

		normalizujRect(obrazRect_, percentLW, percentTH);
		normalizujRect(nazwaRect_, percentLW, percentTH);
		normalizujRect(trescRect_, percentLW, percentTH);
		normalizujRect(czasRozbudowyRect_, percentLW, percentTH);
		normalizujRect(czasZburzeniaRect_, percentLW, percentTH);
		normalizujRect(rozbudujRect_, percentLW, percentTH);
		normalizujRect(zniszczRect_, percentLW, percentTH);

		setSize(rozmiarKontrolki_.x, rozmiarKontrolki_.y);
		return true;
	}

	const std::string& KontrolkaObiektu::getLoadedConfigFile() const{
		return plikKonfiguracyjny_;
	}

	const STyp::Identyfikator& KontrolkaObiektu::pobierzIdObiektu() const{
		return idObiektu_;
	}

	bool KontrolkaObiektu::ustawDane(const SpEx::ObiektInfo& obj, const SpEx::Planeta& planeta){
		obraz_->load(SpEx::Aplikacja::pobierzInstancje().zarzadcaZasobow_.pobierzAdresObrazka(obj.pobierzIdentyfikatorObrazka()));
		idObiektu_ = obj.pobierzIdentyfikator()();

		rozbuduj_->unbindCallback(64);
		if (idZdarzeniaBudowy_ != 0){
			SpEx::UtilsGui::bindCallbackEvent(rozbuduj_, idZdarzeniaBudowy_, idObiektu_(), Button::LeftMouseClicked);
		}

		zniszcz_->unbindCallback(64);
		if (idZdarzeniaBurzenia_ != 0){
			SpEx::UtilsGui::bindCallbackEvent(zniszcz_, idZdarzeniaBurzenia_, idObiektu_(), Button::LeftMouseClicked);
		}

		obraz_->unbindCallback(64);
		if (idZdarzeniaKlikniecia_ != 0){
			SpEx::UtilsGui::bindCallbackEvent(obraz_, idZdarzeniaKlikniecia_, idObiektu_(), Button::LeftMouseClicked);
		}

		auto wsk = planeta.pobierzObiektJesliIstnieje<SpEx::Obiekt>(idObiektu_);
		if (wsk){
			auto &gra = SpEx::Aplikacja::pobierzInstancje().pobierzGre();
			auto warunki = wsk->pobierzKryteriaRozbudowy();
			std::string opisObiektu;
			opisObiektu = SpEx::Utils::trim(obj.pobierzOpis()());
			for (auto &element : warunki){
				if (element->typAtrybutu() == SpEx::Kryterium::ILOSC){
					auto obiektInfo = gra.pobierzObiektInfoJesliIstnieje<SpEx::ObiektInfo>(element->pobierzIdentyfikator());
					if (obiektInfo)
						opisObiektu += "\n" + obiektInfo->pobierzNazwe()() + " : " + std::to_string(element->pobierzIlosc()());
					else
						opisObiektu += "\n[ ObiektInfo ID: " + element->pobierzIdentyfikator().napis() + " ] : " + std::to_string(element->pobierzIlosc()());
				}
			}
			tresc_->setText(opisObiektu);

			switch (obj.pobierzTypAtrybutu())
			{
			case SpEx::PodstawoweParametry::POZIOM:
				nazwa_->setText(obj.pobierzNazwe()() + " ( Poziom " + std::to_string(wsk->pobierzPoziom()()) + " )");
				break;
			case SpEx::PodstawoweParametry::ILOSC:
				nazwa_->setText(obj.pobierzNazwe()() + " ( Iloœæ " + std::to_string(wsk->pobierzIlosc()()) + " )");
				break;
			default:
				break;
			}
			czasRozbudowy_->setText(SpEx::Utils::konwersja(wsk->pobierzCzasRozbudowy()));
		}
		else{
			auto &gra = SpEx::Aplikacja::pobierzInstancje().pobierzGre();
			auto parametry = SpEx::PodstawoweParametry::wartoscJednostkowaParametru(obj.pobierzTypAtrybutu());
			parametry.ustawIdentyfikatorPlanety(planeta.pobierzIdentyfikator());
			auto warunki = obj.pobierzWarunki(parametry);
			std::string opisObiektu;
			opisObiektu = SpEx::Utils::trim(obj.pobierzOpis()());
			for (auto &element : warunki){
				if (element->typAtrybutu() == SpEx::Kryterium::ILOSC){
					auto obiektInfo = gra.pobierzObiektInfoJesliIstnieje<SpEx::ObiektInfo>(element->pobierzIdentyfikator());
					if (obiektInfo)
						opisObiektu += "\n" + obiektInfo->pobierzNazwe()() + " : " + std::to_string(element->pobierzIlosc()());
					else
						opisObiektu += "\n[ ObiektInfo ID: " + element->pobierzIdentyfikator().napis() + " ] : " + std::to_string(element->pobierzIlosc()());
				}
			}

			tresc_->setText(opisObiektu);
			czasRozbudowy_->setText(SpEx::Utils::konwersja(obj.pobierzCzasBudowy(parametry)));
			nazwa_->setText(obj.pobierzNazwe()());
		}
		return true;
	}

	bool KontrolkaObiektu::setProperty(std::string property, const std::string& value){
		if (property == "image"){
			return obraz_->load(value);
		}else if(property == "idzdarzeniabudowy"){
			idZdarzeniaBudowy_ = std::strtol(value.c_str(), nullptr, 10);
			return true;
		}
		else if (property == "idzdarzeniaburzenia"){
			idZdarzeniaBurzenia_ = std::strtol(value.c_str(), nullptr, 10);
			return true;
		}
		else if (property == "idzdarzeniaklikniecia"){
			idZdarzeniaKlikniecia_ = std::strtol(value.c_str(), nullptr, 10);
			return true;
		}
		else if (property == "configfile"){
			return load(value);
		}else
			return Panel::setProperty(property, value);
	}

	bool KontrolkaObiektu::getProperty(std::string property, std::string& value) const{
		if (property == "Image"){
			value = obraz_->getLoadedFilename();
			return true;
		}else if (property == "ConfigFile"){
			value = plikKonfiguracyjny_;
			return true;
		}else if(property == "IdZdarzeniaBudowy"){
			value = idZdarzeniaBudowy_;
		}
		else if (property == "IdZdarzeniaBurzenia"){
			value = idZdarzeniaBurzenia_;
		}
		else if (property == "IdZdarzeniaKlikniecia"){
			value = idZdarzeniaKlikniecia_;
		}
		else
			return Panel::getProperty(property, value);
		return true;
	}

	std::list< std::pair<std::string, std::string> > KontrolkaObiektu::getPropertyList() const{
		auto list = Panel::getPropertyList();
		list.push_back(std::pair<std::string, std::string>("ConfigFile", "string"));
		list.push_back(std::pair<std::string, std::string>("Image", "string"));
		list.push_back(std::pair<std::string, std::string>("IdZdarzeniaBudowy", "int"));
		list.push_back(std::pair<std::string, std::string>("IdZdarzeniaBurzenia", "int"));
		list.push_back(std::pair<std::string, std::string>("IdZdarzeniaKlikniecia", "int"));
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
