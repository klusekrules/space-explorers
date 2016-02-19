#include "KontrolkaObiektu.h"
#include "Utils\UtilsGui.h"
#include "Model\Planeta.h"
#include "Kontroler\Aplikacja.h"
#include "Narzedzia\ZarzadcaZasobow.h"
#include "Kontroler\Gra.h"
#include "Utils\Utils.h"

namespace tgui{
	
	KontrolkaObiektu::KontrolkaObiektu() : BazowyWidzet() {
		m_callback.widgetType = "KontrolkaObiektu";
		m_draggableWidget = false;

		m_panel->setBackgroundColor(sf::Color::Transparent);
		m_panel->setSize(410, 110);

		obraz_ = std::make_shared<Picture>();
		m_panel->add(obraz_, "ObrazObiektu");
		obraz_->setTexture("resource\\Brak_obrazka.png");
		//Zbyt niska wydajnoœæ: obraz_->setSize({"&.h-10"},{"&.h-10"});
		obraz_->setSize(100, 100);
		obraz_->setPosition(5,5);
				
		nazwa_ = std::make_shared<Label>();
		m_panel->add(nazwa_,"NazwaObiektu");
		nazwa_->setTextSize(14);
		nazwa_->setTextColor({ 255,0,0 });
		//Zbyt niska wydajnoœæ: nazwa_->setSize({ "{ ( &.w - &.h - 20 ) * 0.715 , ( &.h - 11 ) * 0.15 }" });
		//Zbyt niska wydajnoœæ: nazwa_->setPosition({ "{ &.h , 3 }" });
		nazwa_->setSize(280*0.715,99*0.15);
		nazwa_->setPosition(110,3);
		nazwa_->setText("Nazwa Obiektu");

		tresc_ = std::make_shared<Label>();
		m_panel->add(tresc_,"OpisObiektu");
		tresc_->setTextSize(14);
		tresc_->setTextColor({ 255,255,255 });
		//Zbyt niska wydajnoœæ: tresc_->setSize({ "{(&.w-&.h-20)*0.715,(&.h-11)*0.85}" });
		//Zbyt niska wydajnoœæ: tresc_->setPosition({ "{&.h,((&.h-11)*0.15) + 7}" });
		tresc_->setSize(280 * 0.715, 99 * 0.85);
		tresc_->setPosition(110, 99 * 0.15 + 7);
		tresc_->setText("Opis Obiektu\nw wielu liniach.\nKoniec Opisu.");
		
		czasRozbudowy_ = std::make_shared<Label>();
		m_panel->add(czasRozbudowy_, "CzasRozbudowy");
		czasRozbudowy_->setTextSize(14);
		czasRozbudowy_->setTextColor({ 255,255,255 });
		//Zbyt niska wydajnoœæ: czasRozbudowy_->setSize({ "{(&.w-&.h-20)*0.285,(&.h-10)*0.15}" });
		//Zbyt niska wydajnoœæ: czasRozbudowy_->setPosition({ "{&.h+(&.w-&.h-20)*0.715+15,3+(&.h-10)*0.05}" });
		czasRozbudowy_->setSize(280 * 0.285,15);
		czasRozbudowy_->setPosition(110 + 280 * 0.715 + 15, 8);
		czasRozbudowy_->setText("Czas rozbudowy");
		
		czasZburzenia_ = std::make_shared<Label>();
		m_panel->add(czasZburzenia_, "CzasZburzenia");
		czasZburzenia_->setTextSize(14);
		czasZburzenia_->setTextColor({ 255,255,255 });
		//Zbyt niska wydajnoœæ: czasZburzenia_->setSize({ "{(&.w-&.h-20)*0.285,(&.h-10)*0.15}" });
		//Zbyt niska wydajnoœæ: czasZburzenia_->setPosition({ "{&.h+(&.w-&.h-20)*0.715+15,7+(&.h-10)*0.5}" });
		czasZburzenia_->setSize(280 * 0.285, 15);
		czasZburzenia_->setPosition(110 + 280 * 0.715 + 15,57);
		czasZburzenia_->setText("Czas burzenia");

		rozbuduj_ = std::make_shared<Button>();
		m_panel->add(rozbuduj_,"Rozbuduj");
		rozbuduj_->setTextSize(14);
		//Zbyt niska wydajnoœæ: rozbuduj_->setSize({ "{(&.w-&.h-20)*0.285,(&.h-10)*0.3}" });
		//Zbyt niska wydajnoœæ: rozbuduj_->setPosition({ "{&.h+(&.w-&.h-20)*0.715+15,3+(&.h-10)*0.2}" });
		rozbuduj_->setSize(280 * 0.285, 30);
		rozbuduj_->setPosition(110 + 280 * 0.715 + 15, 23);
		rozbuduj_->setText("Buduj");
		rozbuduj_->getRenderer()->setBorders({ 0,0,0,0 });
		rozbuduj_->getRenderer()->setTextColorNormal("#BEBEBE");
		rozbuduj_->getRenderer()->setProperty("NormalImage", "\"widgets\\Black.png\" Part(0, 64, 45, 50) Middle(10, 0, 25, 50)");

		zniszcz_ = std::make_shared<Button>();
		m_panel->add(zniszcz_,"Zburz");
		zniszcz_->setTextSize(14);
		//Zbyt niska wydajnoœæ: zniszcz_->setSize({ "{(&.w-&.h-20)*0.285,(&.h-10)*0.3}" });
		//Zbyt niska wydajnoœæ: zniszcz_->setPosition({ "{&.h+(&.w-&.h-20)*0.715+15,7+(&.h-10)*0.65}" });
		zniszcz_->setSize(280 * 0.285, 30);
		zniszcz_->setPosition(110 + 280 * 0.715 + 15, 72);
		zniszcz_->setText("Zburz");
		zniszcz_->getRenderer()->setBorders({ 0,0,0,0 });
		zniszcz_->getRenderer()->setTextColorNormal("#BEBEBE");
		zniszcz_->getRenderer()->setProperty("NormalImage", "\"widgets\\Black.png\" Part(0, 64, 45, 50) Middle(10, 0, 25, 50)");
		

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
		obraz_ = m_panel->get<Picture>("ObrazObiektu");
		nazwa_ = m_panel->get<Label>("NazwaObiektu");
		tresc_ = m_panel->get<Label>("OpisObiektu");
		rozbuduj_ = m_panel->get<Button>("Rozbuduj");
		zniszcz_ = m_panel->get<Button>("Zburz");
		czasRozbudowy_ = m_panel->get<Label>("CzasRozbudowy");
		czasZburzenia_ = m_panel->get<Label>("CzasZburzenia");
	}

	KontrolkaObiektu & KontrolkaObiektu::operator=(const KontrolkaObiektu & right){
		if (this != &right)
		{
			BazowyWidzet::operator=(right);
			idZdarzeniaBudowy_ = right.idZdarzeniaBudowy_;
			idZdarzeniaBurzenia_ = right.idZdarzeniaBurzenia_;
			idZdarzeniaKlikniecia_ = right.idZdarzeniaKlikniecia_;
			idObiektu_ = right.idObiektu_;
			obraz_ = m_panel->get<Picture>("ObrazObiektu");
			nazwa_ = m_panel->get<Label>("NazwaObiektu");
			tresc_ = m_panel->get<Label>("OpisObiektu");
			rozbuduj_ = m_panel->get<Button>("Rozbuduj");
			zniszcz_ = m_panel->get<Button>("Zburz");
			czasRozbudowy_ = m_panel->get<Label>("CzasRozbudowy");
			czasZburzenia_ = m_panel->get<Label>("CzasZburzenia");
		}

		return *this;
	}

	KontrolkaObiektu::Ptr KontrolkaObiektu::copy(KontrolkaObiektu::ConstPtr widget){
		if (widget)
			return std::static_pointer_cast<KontrolkaObiektu>(widget->clone());
		else
			return nullptr;
	}

	void KontrolkaObiektu::reload(const std::string& primary, const std::string& secondary, bool force) {
		auto renderer = getRenderer();
		renderer->setBorders({ 0, 0, 0, 0 });
		renderer->setPadding({ 0, 0, 0, 0 });
		renderer->setBackgroundTexture({ "widgets\\tlo.png" });

		if (m_theme && primary != ""){
			BazowyWidzet::reload(primary, secondary, force);
		}

		if (force){
			if (renderer->m_backgroundTexture.isLoaded())
				setSize(renderer->m_backgroundTexture.getImageSize());
		}

		updateSize();
	}
	
	const STyp::Identyfikator& KontrolkaObiektu::pobierzIdObiektu() const{
		return idObiektu_;
	}

	bool KontrolkaObiektu::mouseOnWidget(float x, float y) const{
		return sf::FloatRect{ getPosition().x, getPosition().y, getSize().x, getSize().y }.contains(x, y);
		/*if (sf::FloatRect{ getPosition().x, getPosition().y, getSize().x, getSize().y }.contains(x, y))
			return true;
		else{
			if (m_mouseHover)
				mouseLeftWidget();

			m_mouseHover = false;
			return false;
		}*/
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

	void KontrolkaObiektu::ustawKontrolkeObrazuObiektu(Picture::Ptr ptr) {
		m_panel->remove(obraz_);
		obraz_ = ptr;
		if (obraz_)
			m_panel->add(obraz_);
	}
	void KontrolkaObiektu::ustawKontrolkeNazwaObiektu(Label::Ptr ptr) {
		m_panel->remove(nazwa_);
		nazwa_ = ptr;
		if (nazwa_)
			m_panel->add(nazwa_);
	}
	void KontrolkaObiektu::ustawKontrolkeOpisObiektu(Label::Ptr ptr) {
		m_panel->remove(tresc_);
		tresc_ = ptr;
		if (tresc_)
			m_panel->add(tresc_);
	}
	void KontrolkaObiektu::ustawKontrolkeRozbudujObiekt(Button::Ptr ptr) {
		m_panel->remove(rozbuduj_);
		rozbuduj_ = ptr;
		if (rozbuduj_)
			m_panel->add(rozbuduj_);
	}
	void KontrolkaObiektu::ustawKontrolkeZburzObiekt(Button::Ptr ptr) {
		m_panel->remove(zniszcz_);
		zniszcz_ = ptr;
		if (zniszcz_)
			m_panel->add(zniszcz_);
	}
	void KontrolkaObiektu::ustawKontrolkeCzasBudowyObiektu(Label::Ptr ptr) {
		m_panel->remove(czasRozbudowy_);
		czasRozbudowy_ = ptr;
		if (czasRozbudowy_)
			m_panel->add(czasRozbudowy_);
	}
	void KontrolkaObiektu::ustawKontrolkeCzasBurzeniaObiektu(Label::Ptr ptr) {
		m_panel->remove(czasZburzenia_);
		czasZburzenia_ = ptr;
		if (czasZburzenia_)
			m_panel->add(czasZburzenia_);
	}

	void KontrolkaObiektuRenderer::setProperty(std::string property, const std::string& value) {
		property = toLower(property);

		if (property == "ObrazObiektu") {
			if (toLower(value) == "none")
				static_cast<KontrolkaObiektu*>(kontrolka_)->ustawKontrolkeObrazuObiektu(nullptr);
			else {
				if (kontrolka_->getTheme() == nullptr)
					throw Exception{ "Failed to load Picture, KontrolkaObiektu has no connected theme to load the Picture with" };

				static_cast<KontrolkaObiektu*>(kontrolka_)->ustawKontrolkeObrazuObiektu(kontrolka_->getTheme()->internalLoad(kontrolka_->getPrimaryLoadingParameter(), value));
			}
		}
		else if(property == "NazwaObiektu") {
			if (toLower(value) == "none")
				static_cast<KontrolkaObiektu*>(kontrolka_)->ustawKontrolkeOpisObiektu(nullptr);
			else {
				if (kontrolka_->getTheme() == nullptr)
					throw Exception{ "Failed to load Label, KontrolkaObiektu has no connected theme to load the Label with" };

				static_cast<KontrolkaObiektu*>(kontrolka_)->ustawKontrolkeOpisObiektu(kontrolka_->getTheme()->internalLoad(kontrolka_->getPrimaryLoadingParameter(), value));
			}
		}
		else if (property == "OpisObiektu") {
			if (toLower(value) == "none")
				static_cast<KontrolkaObiektu*>(kontrolka_)->ustawKontrolkeOpisObiektu(nullptr);
			else {
				if (kontrolka_->getTheme() == nullptr)
					throw Exception{ "Failed to load Label, KontrolkaObiektu has no connected theme to load the Label with" };

				static_cast<KontrolkaObiektu*>(kontrolka_)->ustawKontrolkeOpisObiektu(kontrolka_->getTheme()->internalLoad(kontrolka_->getPrimaryLoadingParameter(), value));
			}
		}
		else if (property == "Rozbuduj") {
			if (toLower(value) == "none")
				static_cast<KontrolkaObiektu*>(kontrolka_)->ustawKontrolkeRozbudujObiekt(nullptr);
			else {
				if (kontrolka_->getTheme() == nullptr)
					throw Exception{ "Failed to load Button, KontrolkaObiektu has no connected theme to load the Button with" };

				static_cast<KontrolkaObiektu*>(kontrolka_)->ustawKontrolkeRozbudujObiekt(kontrolka_->getTheme()->internalLoad(kontrolka_->getPrimaryLoadingParameter(), value));
			}
		}
		else if (property == "Zburz") {
			if (toLower(value) == "none")
				static_cast<KontrolkaObiektu*>(kontrolka_)->ustawKontrolkeZburzObiekt(nullptr);
			else {
				if (kontrolka_->getTheme() == nullptr)
					throw Exception{ "Failed to load Button, KontrolkaObiektu has no connected theme to load the Button with" };

				static_cast<KontrolkaObiektu*>(kontrolka_)->ustawKontrolkeZburzObiekt(kontrolka_->getTheme()->internalLoad(kontrolka_->getPrimaryLoadingParameter(), value));
			}
		}
		else if (property == "CzasRozbudowy") {
			if (toLower(value) == "none")
				static_cast<KontrolkaObiektu*>(kontrolka_)->ustawKontrolkeCzasBudowyObiektu(nullptr);
			else {
				if (kontrolka_->getTheme() == nullptr)
					throw Exception{ "Failed to load Label, KontrolkaObiektu has no connected theme to load the Label with" };

				static_cast<KontrolkaObiektu*>(kontrolka_)->ustawKontrolkeCzasBudowyObiektu(kontrolka_->getTheme()->internalLoad(kontrolka_->getPrimaryLoadingParameter(), value));
			}
		}
		else if (property == "CzasZburzenia") {
			if (toLower(value) == "none")
				static_cast<KontrolkaObiektu*>(kontrolka_)->ustawKontrolkeCzasBurzeniaObiektu(nullptr);
			else {
				if (kontrolka_->getTheme() == nullptr)
					throw Exception{ "Failed to load Label, KontrolkaObiektu has no connected theme to load the Label with" };

				static_cast<KontrolkaObiektu*>(kontrolka_)->ustawKontrolkeCzasBurzeniaObiektu(kontrolka_->getTheme()->internalLoad(kontrolka_->getPrimaryLoadingParameter(), value));
			}
		}
		else
			BazowyRenderer::setProperty(property, value);
	}

	void KontrolkaObiektuRenderer::setProperty(std::string property, ObjectConverter&& value) {
		property = toLower(property);

		if (value.getType() == ObjectConverter::Type::String) {
			if (property == "ObrazObiektu") {
				if (toLower(value.getString()) == "none")
					static_cast<KontrolkaObiektu*>(kontrolka_)->ustawKontrolkeObrazuObiektu(nullptr);
				else{
					if (kontrolka_->getTheme() == nullptr)
						throw Exception{ "Failed to load Picture, KontrolkaObiektu has no connected theme to load the Picture with" };

					static_cast<KontrolkaObiektu*>(kontrolka_)->ustawKontrolkeObrazuObiektu(kontrolka_->getTheme()->internalLoad(kontrolka_->getPrimaryLoadingParameter(), value.getString()));
				}
			}
			else if (property == "NazwaObiektu") {
				if (toLower(value.getString()) == "none")
					static_cast<KontrolkaObiektu*>(kontrolka_)->ustawKontrolkeOpisObiektu(nullptr);
				else {
					if (kontrolka_->getTheme() == nullptr)
						throw Exception{ "Failed to load Label, KontrolkaObiektu has no connected theme to load the Label with" };

					static_cast<KontrolkaObiektu*>(kontrolka_)->ustawKontrolkeOpisObiektu(kontrolka_->getTheme()->internalLoad(kontrolka_->getPrimaryLoadingParameter(), value.getString()));
				}
			}
			else if (property == "OpisObiektu") {
				if (toLower(value.getString()) == "none")
					static_cast<KontrolkaObiektu*>(kontrolka_)->ustawKontrolkeOpisObiektu(nullptr);
				else {
					if (kontrolka_->getTheme() == nullptr)
						throw Exception{ "Failed to load Label, KontrolkaObiektu has no connected theme to load the Label with" };

					static_cast<KontrolkaObiektu*>(kontrolka_)->ustawKontrolkeOpisObiektu(kontrolka_->getTheme()->internalLoad(kontrolka_->getPrimaryLoadingParameter(), value.getString()));
				}
			}
			else if (property == "Rozbuduj") {
				if (toLower(value.getString()) == "none")
					static_cast<KontrolkaObiektu*>(kontrolka_)->ustawKontrolkeRozbudujObiekt(nullptr);
				else {
					if (kontrolka_->getTheme() == nullptr)
						throw Exception{ "Failed to load Button, KontrolkaObiektu has no connected theme to load the Button with" };

					static_cast<KontrolkaObiektu*>(kontrolka_)->ustawKontrolkeRozbudujObiekt(kontrolka_->getTheme()->internalLoad(kontrolka_->getPrimaryLoadingParameter(), value.getString()));
				}
			}
			else if (property == "Zburz") {
				if (toLower(value.getString()) == "none")
					static_cast<KontrolkaObiektu*>(kontrolka_)->ustawKontrolkeZburzObiekt(nullptr);
				else {
					if (kontrolka_->getTheme() == nullptr)
						throw Exception{ "Failed to load Button, KontrolkaObiektu has no connected theme to load the Button with" };

					static_cast<KontrolkaObiektu*>(kontrolka_)->ustawKontrolkeZburzObiekt(kontrolka_->getTheme()->internalLoad(kontrolka_->getPrimaryLoadingParameter(), value.getString()));
				}
			}
			else if (property == "CzasRozbudowy") {
				if (toLower(value.getString()) == "none")
					static_cast<KontrolkaObiektu*>(kontrolka_)->ustawKontrolkeCzasBudowyObiektu(nullptr);
				else {
					if (kontrolka_->getTheme() == nullptr)
						throw Exception{ "Failed to load Label, KontrolkaObiektu has no connected theme to load the Label with" };

					static_cast<KontrolkaObiektu*>(kontrolka_)->ustawKontrolkeCzasBudowyObiektu(kontrolka_->getTheme()->internalLoad(kontrolka_->getPrimaryLoadingParameter(), value.getString()));
				}
			}
			else if (property == "CzasZburzenia") {
				if (toLower(value.getString()) == "none")
					static_cast<KontrolkaObiektu*>(kontrolka_)->ustawKontrolkeCzasBurzeniaObiektu(nullptr);
				else {
					if (kontrolka_->getTheme() == nullptr)
						throw Exception{ "Failed to load Label, KontrolkaObiektu has no connected theme to load the Label with" };

					static_cast<KontrolkaObiektu*>(kontrolka_)->ustawKontrolkeCzasBurzeniaObiektu(kontrolka_->getTheme()->internalLoad(kontrolka_->getPrimaryLoadingParameter(), value.getString()));
				}
			}else
				BazowyRenderer::setProperty(property, std::move(value));
		}else
			BazowyRenderer::setProperty(property, std::move(value));
	}

	std::shared_ptr<WidgetRenderer> KontrolkaObiektuRenderer::clone(Widget * widget){
		auto renderer = std::make_shared<KontrolkaObiektuRenderer>(*this);
		renderer->kontrolka_ = static_cast<KontrolkaObiektu*>(widget);
		return renderer;
	}


};
