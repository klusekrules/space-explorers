#include "ListaSurowcowGui.h"
#include "Model\Planeta.h"
#include "Model\SurowceInfo.h"
namespace tgui {

	ListaSurowcowGui::ListaSurowcowGui()
		: BazowyWidzet()
	{
		m_callback.widgetType = "ListaSurowcowGui";
		m_draggableWidget = false;
		
		m_panel->setBackgroundColor(sf::Color::Transparent);

		m_renderer = std::make_shared<ListaSurowcowGuiRenderer>(this);
		reload("", "", true);

		setSize(400, 64);
	}

	ListaSurowcowGui::ListaSurowcowGui(const ListaSurowcowGui& o)
		: BazowyWidzet(o), szablonKontrolki_(SurowiecGui::copy(o.szablonKontrolki_)), kontrolki_()
	{
		for (auto& widget : m_panel->getWidgets() ) {
			if (widget->getWidgetType() == "SurowiecGui") {
				kontrolki_.push_back( std::static_pointer_cast<SurowiecGui>(widget));
			}
		}
	}

	ListaSurowcowGui& ListaSurowcowGui::operator=(const ListaSurowcowGui & right){
		if (this != &right){
			BazowyWidzet::operator=(right);
			szablonKontrolki_ = SurowiecGui::copy(right.szablonKontrolki_);
			kontrolki_.clear();
			for (auto& widget : m_panel->getWidgets()) {
				if (widget->getWidgetType() == "SurowiecGui") {
					kontrolki_.push_back(std::static_pointer_cast<SurowiecGui>(widget));
				}
			}
		}
		return *this;
	}

	ListaSurowcowGui::Ptr ListaSurowcowGui::copy(ListaSurowcowGui::ConstPtr widget) {
		if (widget)
			return std::static_pointer_cast<ListaSurowcowGui>(widget->clone());
		else
			return nullptr;
	}
	
	void ListaSurowcowGui::draw(sf::RenderTarget& target, sf::RenderStates states) const{
		std::lock_guard<std::mutex> lock(zmianaDanych_);
		BazowyWidzet::draw(target, states);
	}

	void ListaSurowcowGui::aktualizacjaDanych(const SpEx::Planeta& planeta){
		if (szablonKontrolki_ == nullptr) {
			wyczyscDane();
			stworzDomyslnySzablonKontrolki();
		}

		auto listaObj = planeta.pobierzSurowce();
		if (kontrolki_.size() == listaObj.size()){ // Je�eli ilo�� kontrolek jest taka sama, jak ilo�� obiekt�w to tylko aktualizujemy dane.
			auto iter = listaObj.begin();
			for (auto element : kontrolki_)
				element->ustawDane(*((iter++)->second));
		}
		else{
			// Usuni�cie niepotrzebnych okien
			for (auto iter = kontrolki_.begin(); iter != kontrolki_.end();){
				if (listaObj.find((*iter)->pobierzIdObiektu()) != listaObj.end()){
					++iter;
				}else{
					std::lock_guard<std::mutex> lock(zmianaDanych_);
					m_panel->remove(*iter);
					iter = kontrolki_.erase(iter);
				}
			}
			// Dodanie brakuj�cych element�w oraz uaktualnienie obecnych.
			auto iter = kontrolki_.begin();
			for (auto &id : listaObj){
				if (iter == kontrolki_.end() || (*iter)->pobierzIdObiektu() != id.first){
					std::lock_guard<std::mutex> lock(zmianaDanych_);
					auto widget = SurowiecGui::copy(szablonKontrolki_);
					auto nazwa = id.second->pobierzSurowceInfo().pobierzNazwe()();
					m_panel->add(widget,nazwa);
					widget->ustawDane(*id.second);
					widget->show();
					if (iter == kontrolki_.end()) {
						kontrolki_.emplace_back(widget);
						iter = kontrolki_.end();
						continue;
					}else {
						auto nIter = kontrolki_.emplace(iter, widget);
						iter = nIter;
					}
				}else{
					if (iter != kontrolki_.end()) {
						(*iter)->ustawDane(*id.second);
					}
				}
				++iter;
			}
		}
		odswiezPozycje();
	}
	
	void ListaSurowcowGui::odswiezPozycje(){
		float positionX = 0.f;
		for (auto element : kontrolki_){
			auto temp = element->getSize();
			element->setPosition(positionX, 0.f);
			positionX += temp.x + 20;
		}
	}

	void ListaSurowcowGui::stworzDomyslnySzablonKontrolki(){
		szablonKontrolki_ = std::make_shared<SurowiecGui>();
		szablonKontrolki_->hide();
	}

	void ListaSurowcowGui::wyczyscDane(){
		std::lock_guard<std::mutex> lock(zmianaDanych_);
		m_panel->removeAllWidgets();
		szablonKontrolki_ = nullptr;
		kontrolki_.clear();
	}

	std::shared_ptr<WidgetRenderer> ListaSurowcowGuiRenderer::clone(Widget * widget){
		auto renderer = std::make_shared<ListaSurowcowGuiRenderer>(*this);
		renderer->kontrolka_ = static_cast<ListaSurowcowGui*>(widget);
		return renderer;
	}

};