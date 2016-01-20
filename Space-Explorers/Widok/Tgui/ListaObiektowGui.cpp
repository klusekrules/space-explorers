#include "ListaObiektowGui.h"
#include "Kontroler\Aplikacja.h"
#include <SFML\OpenGL.hpp>
#include "Kontroler\Gra.h"

namespace tgui {

	ListaObiektowGui::ListaObiektowGui(const ListaObiektowGui& o)
		: BazowyWidzet(o)
	{
		szablonKontrolki_ = m_panel->get<KontrolkaObiektu>("Szablon");
		suwak_ = m_panel->get<Scrollbar>("PasekPrzewijania");
		for (auto e : o.kontrolki_) {
			std::string nazwa = m_panel->getWidgetName(e);
			if (!nazwa.empty()) {
				kontrolki_.push_back(m_panel->get<KontrolkaObiektu>(nazwa));
			}
		}
	}

	ListaObiektowGui & ListaObiektowGui::operator=(const ListaObiektowGui & right)
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

	void ListaObiektowGui::aktualizacjaDanych(const SpEx::Planeta& planeta){
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
			for (auto &id : listaId){
				if (iter == kontrolki_.end() || (*iter)->pobierzIdObiektu() != id){
					std::lock_guard<std::mutex> lock(zmianaDanych_);
					auto widget = std::make_shared<KontrolkaObiektu>(*szablonKontrolki_);
					m_panel->add(widget,listaObj.at(id)->pobierzNazwe()());
					widget->show();
					iter = kontrolki_.emplace(iter, widget);
					if (shader_)
						(*iter)->getRenderer()->setShader(shader_.get());					
				}
				if (iter != kontrolki_.end()){
					(*iter)->ustawDane(*listaObj.at(id), planeta);
					++iter;
				}
			}
		}
		odswiez(false);
	}
	
	int ListaObiektowGui::pobierzTypObiektu() const{
		return typObiektu_;
	}

	void ListaObiektowGui::odswiez(bool czyResetSuwaka){
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
		if (shader_){
			auto size = szablonKontrolki_->getSize();
			auto pSize = BazowyWidzet::getSize();
			auto pozycja = BazowyWidzet::getPosition();
			GLint viewport[4];
			GLfloat upBorder, downBorder;
			glGetIntegerv(GL_VIEWPORT, viewport);
			downBorder = (float)viewport[3] - (pozycja.y + pSize.y);
			upBorder = (float)viewport[3] - pozycja.y;
			shader_->setParameter("zakres", size.y);
			shader_->setParameter("upMargin", upBorder - size.y);
			shader_->setParameter("downMargin", downBorder + size.y);
		}
	}

	void ListaObiektowGui::setSize(const Layout2d& newSize){
		BazowyWidzet::setSize(newSize);
		if (pokazSuwak_){
			auto size = suwak_->getSize();
			suwak_->setPosition(newSize.x - size.x, 0);
			suwak_->setSize(size.x, newSize.y);
			if (czyAutoRozmiar_)
				szablonKontrolki_->setSize(newSize.x - (margines_.left + margines_.right + size.x), newSize.y);
		}
		else{
			if (czyAutoRozmiar_)
				szablonKontrolki_->setSize(newSize.x - (margines_.left + margines_.right), newSize.y);
		}
		
		przeliczPozycjeKontrolek(0,true);
		uaktualnijSuwak(newSize.y.getValue(),false);
		if (shader_){
			auto size = szablonKontrolki_->getSize();
			auto pozycja = BazowyWidzet::getPosition();
			GLint viewport[4];
			GLfloat upBorder, downBorder;
			glGetIntegerv(GL_VIEWPORT, viewport);
			downBorder = (float)viewport[3] - (pozycja.y + newSize.y.getValue());
			upBorder = (float)viewport[3] - pozycja.y;
			shader_->setParameter("zakres", size.y);
			shader_->setParameter("upMargin", upBorder - size.y);
			shader_->setParameter("downMargin", downBorder + size.y);
		}
	}
	/*
	void ListaObiektowGui::initialize(Container *const container){
		Panel::setGlobalFont(container->getGlobalFont());
		if (sf::Shader::isAvailable()){
			shader_ = std::make_shared<sf::Shader>();
			shader_->loadFromFile("resource\\simple.frag", sf::Shader::Type::Fragment);
			shader_->setParameter("texture", sf::Shader::CurrentTexture);
		}
		szablonKontrolki_ = KontrolkaObiektu::Ptr(*this, "Szablon");
		szablonKontrolki_->hide();

		suwak_ = Scrollbar::Ptr(*this, "PasekPrzewijania");
		suwak_->bindCallbackEx(std::bind(&ListaObiektowGui::scrollbarValueChanged, this, std::placeholders::_1), tgui::Scrollbar::ValueChanged);
		if (pokazSuwak_)
			suwak_->show();
		else
			suwak_->hide();

		setSize(430.f, 350.f);
	}*/

	void ListaObiektowGui::mouseWheelMoved(int delta, int x, int y){
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
		auto renderer = std::shared_ptr<ListaObiektowGuiRenderer>(new ListaObiektowGuiRenderer{ *this });
		renderer->kontrolka_ = static_cast<BazowyWidzet*>(widget);
		return renderer;
	}
};
