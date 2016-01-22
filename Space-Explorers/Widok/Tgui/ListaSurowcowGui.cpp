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

	ListaSurowcowGui::ListaSurowcowGui(const ListaSurowcowGui& o)
		:BazowyWidzet(o), plikKonfiguracyjny_(o.plikKonfiguracyjny_)
	{
		/*tekst_ = this->get<Label>("Nazwa");*/
	}

	ListaSurowcowGui& ListaSurowcowGui::operator=(const ListaSurowcowGui & right)
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
	
	const std::string& ListaSurowcowGui::getLoadedConfigFile() const{
		return plikKonfiguracyjny_;
	}

	void ListaSurowcowGui::draw(sf::RenderTarget& target, sf::RenderStates states) const{
		std::lock_guard<std::mutex> lock(zmianaDanych_);
		BazowyWidzet::draw(target, states);
	}

	void ListaSurowcowGui::aktualizacjaDanych(const SpEx::Planeta& planeta){
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
					auto widget = std::make_shared<SurowiecGui>(*szablonKontrolki_);
					m_panel->add(widget,id.second->pobierzSurowceInfo().pobierzNazwe()());
					widget->show();
					iter = kontrolki_.emplace(iter, widget);
				}
				if (iter != kontrolki_.end()){
					(*iter)->ustawDane(*id.second);
					++iter;
				}
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

	std::shared_ptr<WidgetRenderer> ListaSurowcowGuiRenderer::clone(Widget * widget){
		auto renderer = std::make_shared<ListaSurowcowGuiRenderer>(*this);
		renderer->kontrolka_ = static_cast<BazowyWidzet*>(widget);
		return renderer;
	}

};