#include "ListaSurowcowGui.h"
#include "Model\Planeta.h"
#include "Model\SurowceInfo.h"
namespace tgui {
	
	/*ListaSurowcowGui::ListaSurowcowGui(const ListaSurowcowGui& o)
		: plikKonfiguracyjny_(o.plikKonfiguracyjny_), Panel(o)
	{
		szablonKontrolki_ = this->get<SurowiecGui>("Szablon");
		for (auto e : o.kontrolki_){
			std::string nazwa;
			if (o.getWidgetName(e, nazwa)){
				if (!nazwa.empty()){
					kontrolki_.push_back(this->get<SurowiecGui>(nazwa));
				}
			}
		}
	}*/

	/*void ListaSurowcowGui::initialize(Container *const container){
		Panel::setGlobalFont(container->getGlobalFont());
		szablonKontrolki_ = SurowiecGui::Ptr(*this, "Szablon");
		szablonKontrolki_->hide();
	}

	void ListaSurowcowGui::setTransparency(unsigned char transparency){
		Panel::setBackgroundColor(sf::Color(255, 255, 255, transparency));
		Panel::setTransparency(transparency);
		szablonKontrolki_->setTransparency(transparency);
		for (auto &element : kontrolki_){
			element->setTransparency(transparency);
		}
	}*/




	

	ListaSurowcowGui::ListaSurowcowGui()
		: BazowyWidzet()
	{
		m_callback.widgetType = "ListaSurowcowGui";
		m_draggableWidget = false;
		
		m_panel->setBackgroundColor(sf::Color::White);

		m_renderer = std::make_shared<ListaSurowcowGuiRenderer>(this);
		reload("", "", true);

		setSize(600, 200);
	}

	ListaSurowcowGui::ListaSurowcowGui(const ListaSurowcowGui& o)
		: BazowyWidzet(o)
	{}

	ListaSurowcowGui& ListaSurowcowGui::operator=(const ListaSurowcowGui & right){
		if (this != &right){
			BazowyWidzet::operator=(right);
		}
		return *this;
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
		if (kontrolki_.size() == listaObj.size()){ // Je¿eli iloœæ kontrolek jest taka sama, jak iloœæ obiektów to tylko aktualizujemy dane.
			auto iter = listaObj.begin();
			for (auto element : kontrolki_)
				element->ustawDane(*((iter++)->second));
		}
		else{
			// Usuniêcie niepotrzebnych okien
			for (auto iter = kontrolki_.begin(); iter != kontrolki_.end();){
				if (listaObj.find((*iter)->pobierzIdObiektu()) != listaObj.end()){
					++iter;
				}else{
					std::lock_guard<std::mutex> lock(zmianaDanych_);
					m_panel->remove(*iter);
					iter = kontrolki_.erase(iter);
				}
			}
			// Dodanie brakuj¹cych elementów oraz uaktualnienie obecnych.
			auto iter = kontrolki_.begin();
			for (auto &id : listaObj){
				if (iter == kontrolki_.end() || (*iter)->pobierzIdObiektu() != id.first){
					std::lock_guard<std::mutex> lock(zmianaDanych_);
					auto widget = std::static_pointer_cast<tgui::SurowiecGui>(szablonKontrolki_->clone());
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