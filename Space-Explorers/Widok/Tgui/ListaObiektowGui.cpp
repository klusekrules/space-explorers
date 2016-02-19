#include "ListaObiektowGui.h"
#include "Kontroler\Aplikacja.h"
#include <SFML\OpenGL.hpp>
#include "Kontroler\Gra.h"

namespace tgui {

	ListaObiektowGui::ListaObiektowGui(){
		m_callback.widgetType = "ListaObiektowGui";
		m_draggableWidget = false;
		mnoznikRolki_ = 6;
		m_panel->setBackgroundColor(sf::Color::White);
		
		auto renderer = std::make_shared<ListaObiektowGuiRenderer>(this);
		m_renderer = renderer;

		if (sf::Shader::isAvailable()) {
			auto shader = std::make_shared<sf::Shader>();
			shader->loadFromFile("resource\\simple.frag", sf::Shader::Type::Fragment);
			shader->setParameter("texture", sf::Shader::CurrentTexture);
			renderer->setShader(shader);
		}

		suwak_ = std::make_shared<Scrollbar>();
		suwak_->connectEx("ValueChanged",std::bind(&ListaObiektowGui::scrollbarValueChanged, this, std::placeholders::_1));
		//suwak_->connectEx("ValueChanged", std::bind(&ListaObiektowGui::scrollbarValueChanged, this, std::placeholders::_1));
		if (pokazSuwak_)
			suwak_->show();
		else
			suwak_->hide();

		reload("", "", true);
		setSize(430.f, 350.f);
	}

	ListaObiektowGui::ListaObiektowGui(const ListaObiektowGui& o)
		: BazowyWidzet(o), szablonKontrolki_(KontrolkaObiektu::copy(o.szablonKontrolki_)), kontrolki_()
	{
		suwak_ = m_panel->get<Scrollbar>("PasekPrzewijania");
		for (auto& widget : m_panel->getWidgets()) {
			if (widget->getWidgetType() == "KontrolkaObiektu") {
				kontrolki_.push_back(std::static_pointer_cast<KontrolkaObiektu>(widget));
			}
		}
	}

	ListaObiektowGui & ListaObiektowGui::operator=(const ListaObiektowGui & right){
		if (this != &right){
			BazowyWidzet::operator=(right);
			szablonKontrolki_ = KontrolkaObiektu::copy(right.szablonKontrolki_);
			suwak_ = m_panel->get<Scrollbar>("PasekPrzewijania"); 
			for (auto& widget : m_panel->getWidgets()) {
				if (widget->getWidgetType() == "KontrolkaObiektu") {
					kontrolki_.push_back(std::static_pointer_cast<KontrolkaObiektu>(widget));
				}
			}
		}
		return *this;
	}

	ListaObiektowGui::Ptr ListaObiektowGui::copy(ListaObiektowGui::ConstPtr widget){
		if (widget)
			return std::static_pointer_cast<ListaObiektowGui>(widget->clone());
		else
			return nullptr;
	}

	void ListaObiektowGui::aktualizacjaDanych(const SpEx::Planeta& planeta){
		if (szablonKontrolki_ == nullptr) {
			wyczyscDane();
			stworzDomyslnySzablonKontrolki();
		}
		std::vector<STyp::Identyfikator> listaId;
		auto listaObj = SpEx::Aplikacja::pobierzInstancje().pobierzGre().pobierzDostepneObiektyInfo(planeta, pobierzTypObiektu(), listaId);
		std::sort(listaId.begin(), listaId.end());
		if (kontrolki_.size() == listaId.size()){ 
			// Je¿eli iloœæ kontrolek jest taka sama, jak iloœæ obiektów to tylko aktualizujemy dane.
			int n = 0;
			for (auto element : kontrolki_)
				element->ustawDane(*listaObj.at(listaId[n++]), planeta);
		}else{
			// Usuniêcie niepotrzebnych okien
			for (auto iter = kontrolki_.begin(); iter != kontrolki_.end();){
				if (std::find(listaId.begin(), listaId.end(), (*iter)->pobierzIdObiektu()) != listaId.end()){
					++iter;
				}else{
					std::lock_guard<std::mutex> lock(zmianaDanych_);
					m_panel->remove(*iter);
					iter = kontrolki_.erase(iter);
				}
			}
			// Dodanie brakuj¹cych elementów oraz uaktualnienie obecnych.
			auto iter = kontrolki_.begin();
			for (auto &id : listaId) {
				if (iter == kontrolki_.end() || (*iter)->pobierzIdObiektu() != id) {
					std::lock_guard<std::mutex> lock(zmianaDanych_);
					auto widget = KontrolkaObiektu::copy(szablonKontrolki_);
					m_panel->add(widget, listaObj.at(id)->pobierzNazwe()());
					widget->ustawDane(*listaObj.at(id), planeta);
					widget->show();
					if (iter == kontrolki_.end()) {
						kontrolki_.emplace_back(widget);
						iter = kontrolki_.end();
						continue;
					}
					else {
						auto nIter = kontrolki_.emplace(iter, widget);
						iter = nIter;
					}
				}
				else {
					if (iter != kontrolki_.end()) {
						(*iter)->ustawDane(*listaObj.at(id), planeta);
					}
				}
				++iter;
			}
		}
		odswiez(false);
	}
	
	void ListaObiektowGui::stworzDomyslnySzablonKontrolki() {
		szablonKontrolki_ = std::make_shared<KontrolkaObiektu>();
		szablonKontrolki_->hide();
	}

	void ListaObiektowGui::wyczyscDane() {
		std::lock_guard<std::mutex> lock(zmianaDanych_);
		m_panel->removeAllWidgets();
		szablonKontrolki_ = nullptr;
		kontrolki_.clear();
	}

	int ListaObiektowGui::pobierzTypObiektu() const{
		return typObiektu_;
	}

	void ListaObiektowGui::ustawTypObiektu(int typ){
		typObiektu_ = typ;
	}

	void ListaObiektowGui::odswiez(bool czyResetSuwaka){
		if (!suwak_)
			return;
		auto size = BazowyWidzet::getSize();
		uaktualnijSuwak(size.y, czyResetSuwaka);
		przeliczPozycjeKontrolek(suwak_->getValue(), true);
	}
		
	const std::string& ListaObiektowGui::getLoadedConfigFile() const{
		return plikKonfiguracyjny_;
	}
	
	void ListaObiektowGui::scrollbarValueChanged(const tgui::Callback& callback){
		przeliczPozycjeKontrolek(callback.value);
	}

	void ListaObiektowGui::przeliczPozycjeKontrolek(int delta, bool uaktualnijRozmiar){
		if (!szablonKontrolki_)
			return;
		int t = 1;
		auto size = szablonKontrolki_->getSize();
		auto upMargin = t*(size.y + odstepMiedzyKontrolkami_) + margines_.top - 50;
		auto downMargin = (t + 1)*(size.y + odstepMiedzyKontrolkami_) + margines_.top + 50;
		for (auto e : kontrolki_){
			if (uaktualnijRozmiar)
				e->setSize(size.x, size.y);
			auto hight = t*(size.y + odstepMiedzyKontrolkami_) + margines_.top - delta;
			e->setPosition(static_cast<float>(margines_.left), hight);
			t++;
		}
	}

	void ListaObiektowGui::uaktualnijSuwak(float hight, bool czyResetSuwaka){
		if (!szablonKontrolki_ || !suwak_)
			return;
		auto size = szablonKontrolki_->getSize();
		float insideHight = (kontrolki_.size() + 2)*(size.y + odstepMiedzyKontrolkami_) + margines_.top + margines_.bottom - odstepMiedzyKontrolkami_;

		if (insideHight <= hight){
			suwak_->setLowValue(0);
			suwak_->setMaximum(0);
			suwak_->setValue(0);
		}
		else{
			suwak_->setLowValue(static_cast<unsigned int>(hight));
			suwak_->setMaximum(static_cast<unsigned int>(insideHight + 1.f));
			if (czyResetSuwaka)
				suwak_->setValue(0);
			else{
				if (suwak_->getValue() > suwak_->getMaximum())
					suwak_->setValue(0);
			}
		}
	}

	void ListaObiektowGui::setPosition(const Layout2d& position){
		BazowyWidzet::setPosition(position);
		auto shader = getRenderer()->getShader();
		if (shader){
			auto size = szablonKontrolki_->getSize();
			auto pSize = BazowyWidzet::getSize();
			auto pozycja = BazowyWidzet::getPosition();
			GLint viewport[4];
			GLfloat upBorder, downBorder;
			glGetIntegerv(GL_VIEWPORT, viewport);
			downBorder = (float)viewport[3] - (pozycja.y + pSize.y);
			upBorder = (float)viewport[3] - pozycja.y;
			shader->setParameter("zakres", size.y);
			shader->setParameter("upMargin", upBorder - size.y);
			shader->setParameter("downMargin", downBorder + size.y);
		}
	}

	void ListaObiektowGui::setSize(const Layout2d& newSize){
		BazowyWidzet::setSize(newSize);
		if (pokazSuwak_ && suwak_){
			auto size = suwak_->getSize();
			suwak_->setPosition(newSize.x - size.x, 0);
			suwak_->setSize(size.x, newSize.y);
			if (czyAutoRozmiar_ && szablonKontrolki_)
				szablonKontrolki_->setSize(newSize.x - (margines_.left + margines_.right + size.x), newSize.y);
		}
		else{
			if (czyAutoRozmiar_&& szablonKontrolki_)
				szablonKontrolki_->setSize(newSize.x - (margines_.left + margines_.right), newSize.y);
		}
		
		przeliczPozycjeKontrolek(0,true);
		uaktualnijSuwak(newSize.y.getValue(),false);
		auto shader = getRenderer()->getShader();
		if (shader && szablonKontrolki_){
			auto size = szablonKontrolki_->getSize();
			auto pozycja = BazowyWidzet::getPosition();
			GLint viewport[4];
			GLfloat upBorder, downBorder;
			glGetIntegerv(GL_VIEWPORT, viewport);
			downBorder = (float)viewport[3] - (pozycja.y + newSize.y.getValue());
			upBorder = (float)viewport[3] - pozycja.y;
			shader->setParameter("zakres", size.y);
			shader->setParameter("upMargin", upBorder - size.y);
			shader->setParameter("downMargin", downBorder + size.y);
		}
	}
	void ListaObiektowGui::mouseWheelMoved(int delta, int x, int y){
		if(suwak_)
			suwak_->mouseWheelMoved(delta*mnoznikRolki_, x, y);
	}

	/*bool ListaObiektowGui::setProperty(std::string property, const std::string& value){
		if (property == "mnoznikrolki"){
			mnoznikRolki_ = std::strtol(value.c_str(), nullptr, 10);
		}
		else if (property == "typobiektu"){
			typObiektu_ = std::strtol(value.c_str(), nullptr, 10);
		}
		else if (property == "idzdarzeniabudowy"){
			szablonKontrolki_->setProperty(property, value);
		}
		else if (property == "idzdarzeniaburzenia"){
			szablonKontrolki_->setProperty(property, value);
		}
		else if (property == "idzdarzeniaklikniecia"){
			szablonKontrolki_->setProperty(property, value);
		}
		else if(property == "scrollbarpokaz"){
			if ((value == "true") || (value == "True"))
				pokazSuwak_ = true;
			else if ((value == "false") || (value == "False"))
				pokazSuwak_ = false;
			else
				TGUI_OUTPUT("TGUI error: Failed to parse 'Enabled' property.");
			
			if (pokazSuwak_)
				suwak_->show();
			else
				suwak_->hide();
		}
		else if (property == "kontrolkaautosize"){
			if ((value == "true") || (value == "True"))
				czyAutoRozmiar_ = true;
			else if ((value == "false") || (value == "False"))
				czyAutoRozmiar_ = false;
			else
				TGUI_OUTPUT("TGUI error: Failed to parse 'Enabled' property.");
		}
		else if (property == "scrollbarszerokosc"){
			auto var = std::strtof(value.c_str(), nullptr);
			auto size = suwak_->getSize();
			suwak_->setSize(var, size.y);
		}
		else if (property == "configfile"){
			return load(value);
		}
		else
			return Panel::setProperty(property, value);
		return true;
	}

	bool ListaObiektowGui::getProperty(std::string property, std::string& value) const{
		if (property == "mnoznikrolki"){
			value = std::to_string(mnoznikRolki_);
		}
		else if (property == "typobiektu"){
			value = std::to_string(typObiektu_);
		}
		else if (property == "scrollbarpokaz"){
			value = std::string(pokazSuwak_ ? "true" : "false");
		}
		else if (property == "scrollbarszerokosc"){
			value = std::to_string(suwak_->getSize().x);
		}
		else if (property == "kontrolkaautosize"){
			value = std::string(czyAutoRozmiar_ ? "true" : "false");
		}
		else if (property == "ConfigFile"){
			value = plikKonfiguracyjny_;
		}
		else if (property == "IdZdarzeniaBudowy"){
			szablonKontrolki_->getProperty(property, value);
		}
		else if (property == "IdZdarzeniaBurzenia"){
			szablonKontrolki_->getProperty(property, value);
		}
		else if (property == "IdZdarzeniaKlikniecia"){
			szablonKontrolki_->getProperty(property, value);
		}
		else
			return Panel::getProperty(property, value);
		return true;
	}

	std::list< std::pair<std::string, std::string> > ListaObiektowGui::getPropertyList() const{
		auto list = Panel::getPropertyList();
		list.push_back(std::pair<std::string, std::string>("ConfigFile", "string"));
		list.push_back(std::pair<std::string, std::string>("mnoznikrolki", "int"));
		list.push_back(std::pair<std::string, std::string>("scrollbarpokaz", "bool"));
		list.push_back(std::pair<std::string, std::string>("scrollbarszerokosc", "float"));
		list.push_back(std::pair<std::string, std::string>("kontrolkaautosize", "bool"));
		return list;
	}*/

	void ListaObiektowGui::draw(sf::RenderTarget& target, sf::RenderStates states) const{
		std::lock_guard<std::mutex> lock(zmianaDanych_);
		BazowyWidzet::draw(target, states);
	}

	std::shared_ptr<WidgetRenderer> ListaObiektowGuiRenderer::clone(Widget * widget){
		auto renderer = std::make_shared<ListaObiektowGuiRenderer>(*this);
		renderer->kontrolka_ = static_cast<ListaObiektowGui*>(widget);
		return renderer;
	}
};
