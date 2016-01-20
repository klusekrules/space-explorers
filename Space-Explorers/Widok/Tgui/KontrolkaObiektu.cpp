#include "KontrolkaObiektu.h"
#include "Utils\UtilsGui.h"
#include "Model\Planeta.h"
#include "Kontroler\Aplikacja.h"
#include "Narzedzia\ZarzadcaZasobow.h"
#include "Kontroler\Gra.h"
#include "Utils\Utils.h"

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

	KontrolkaObiektu::KontrolkaObiektu() : BazowyWidzet() {
		m_callback.widgetType = "KontrolkaObiektu";
		m_draggableWidget = false;

		m_panel->setBackgroundColor(sf::Color::Transparent);

		m_renderer = std::make_shared<KontrolkaObiektuRenderer>(this);
		reload("","",true);
	}

	KontrolkaObiektu::KontrolkaObiektu(const KontrolkaObiektu& copy)
		: BazowyWidzet(copy),
		idZdarzeniaBudowy_(copy.idZdarzeniaBudowy_),
		idZdarzeniaBurzenia_(copy.idZdarzeniaBurzenia_),
		idZdarzeniaKlikniecia_(copy.idZdarzeniaKlikniecia_),
		idObiektu_(copy.idObiektu_)
	{
		/*obraz_ = this->get<Picture>("ObrazObiektu");
		nazwa_ = this->get<Label>("NazwaObiektu");
		tresc_ = this->get<Label>("OpisObiektu");
		rozbuduj_ = this->get<Button>("Rozbuduj");
		zniszcz_ = this->get<Button>("Zburz");
		czasRozbudowy_ = this->get<Label>("CzasRozbudowy");
		czasZburzenia_ = this->get<Label>("CzasZburzenia");*/
	}

	KontrolkaObiektu & KontrolkaObiektu::operator=(const KontrolkaObiektu & right)
	{
		if (this != &right)
		{
			BazowyWidzet::operator=(right);

			/*std::swap(m_lineSpacing, temp.m_lineSpacing);
			std::swap(m_textSize, temp.m_textSize);
			std::swap(m_textColor, temp.m_textColor);
			std::swap(m_maxLines, temp.m_maxLines);
			std::swap(m_fullTextHeight, temp.m_fullTextHeight);
			std::swap(m_linesStartFromTop, temp.m_linesStartFromTop);
			std::swap(m_panel, temp.m_panel);
			std::swap(m_scroll, temp.m_scroll);*/
		}

		return *this;
	}
	
	/*
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

		Widget::setSize(absWidth, absHight);

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
	
	sf::Rect<float> KontrolkaObiektu::pozycjonujLabel(Label::Ptr label, const sf::Rect<float>& rect, float width, float height, WYROWNANIE_HORYZONTALNE horyzontalne, WYROWNANIE_WERTYKALNE wertykalne ){
		sf::Text text;
		text.setFont(*label->getFont());
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
	}*/

	/*void KontrolkaObiektu::initialize(Container *const container){
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
	*/
	
	void KontrolkaObiektu::reload(const std::string& primary, const std::string& secondary, bool force){
		auto renderer = getRenderer();
		renderer->setBorders({ 2, 2, 2, 2 });
		renderer->setPadding({ 2, 2, 2, 2 });
		renderer->setBackgroundColor({ 245, 245, 245 });
		renderer->setBorderColor({ 245, 0, 0 });
		renderer->setBackgroundTexture({"widgets\\tlo.png"});

		if (m_theme && primary != "")
		{
			renderer->setBorders({ 0, 0, 0, 0 });
			renderer->setPadding({ 0, 0, 0, 0 });

			Widget::reload(primary, secondary, force);
		}

		if (force)
		{
			if (renderer->m_backgroundTexture.isLoaded())
				setSize(renderer->m_backgroundTexture.getImageSize());
		}

		updateSize();
	}
	
	const STyp::Identyfikator& KontrolkaObiektu::pobierzIdObiektu() const{
		return idObiektu_;
	}

	bool KontrolkaObiektu::mouseOnWidget(float x, float y){
		if (sf::FloatRect{ getPosition().x, getPosition().y, getSize().x, getSize().y }.contains(x, y))
			return true;
		else{
			if (m_mouseHover)
				mouseLeftWidget();

			m_mouseHover = false;
			return false;
		}
	}

	bool KontrolkaObiektu::ustawDane(const SpEx::ObiektInfo& obj, const SpEx::Planeta& planeta){
		obraz_->setTexture(SpEx::Aplikacja::pobierzInstancje().pobierzZarzadceZasobow().pobierzAdresObrazka(obj.pobierzIdentyfikatorObrazka()));
		idObiektu_ = obj.pobierzIdentyfikator()();

		rozbuduj_->disconnectAll();
		if (idZdarzeniaBudowy_ != 0){
			SpEx::UtilsGui::bindCallbackEvent(rozbuduj_, idZdarzeniaBudowy_, idObiektu_(), "Pressed");
		}

		zniszcz_->disconnectAll();
		if (idZdarzeniaBurzenia_ != 0){
			SpEx::UtilsGui::bindCallbackEvent(zniszcz_, idZdarzeniaBurzenia_, idObiektu_(), "Pressed");
		}

		obraz_->disconnectAll();
		if (idZdarzeniaKlikniecia_ != 0){
			SpEx::UtilsGui::bindCallbackEvent(obraz_, idZdarzeniaKlikniecia_, idObiektu_(), "Pressed");
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

	std::shared_ptr<WidgetRenderer> tgui::KontrolkaObiektuRenderer::clone(Widget * widget){
		auto renderer = std::shared_ptr<KontrolkaObiektuRenderer>(new KontrolkaObiektuRenderer{ *this });
		renderer->kontrolka_ = static_cast<KontrolkaObiektu*>(widget);
		return renderer;
	}


};
