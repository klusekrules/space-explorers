#include "ListaObiektowGui.h"
#include "Kontroler\Aplikacja.h"
#include <SFML\OpenGL.hpp>
#include "Kontroler\Gra.h"

namespace tgui {

	ListaObiektowGui::ListaObiektowGui(){
		m_callback.widgetType = "ListaObiektowGui";
		m_draggableWidget = false;
		mnoznikRolki_ = 6;
		m_panel->setBackgroundColor(sf::Color::Transparent);
		
		m_renderer = std::make_shared<ListaObiektowGuiRenderer>(this);

		getRenderer()->setBackgroundTexture(Texture("resource\\White.bmp"));

		if (sf::Shader::isAvailable()) 
			getRenderer()->setProperty("shader", "resource\\simple.frag");

		suwak_ = std::make_shared<Scrollbar>();
		suwak_->connectEx("ValueChanged",std::bind(&ListaObiektowGui::scrollbarValueChanged, this, std::placeholders::_1));

		if (pokazSuwak_)
			suwak_->show();
		else
			suwak_->hide();

		reload("", "", true);
		setSize(430.f, 350.f);
	}

	ListaObiektowGui::ListaObiektowGui(const ListaObiektowGui& o)
		: BazowyWidzet(o), szablonKontrolki_(KontrolkaObiektu::copy(o.szablonKontrolki_)), kontrolki_()
		, szerokoscSuwaka_(o.szerokoscSuwaka_), odstepMiedzyKontrolkami_(o.odstepMiedzyKontrolkami_)
		, mnoznikRolki_(o.mnoznikRolki_), typObiektu_(o.typObiektu_), pokazSuwak_(o.pokazSuwak_), czyAutoRozmiar_(o.czyAutoRozmiar_)
	{
		suwak_ = m_panel->get<Scrollbar>("PasekPrzewijania");
		for (auto& widget : m_panel->getWidgets()) {
			if (widget->getWidgetType() == "KontrolkaObiektu") {
				kontrolki_.push_back(std::static_pointer_cast<KontrolkaObiektu>(widget));
			}
		}
		uaktualnijShader();
	}

	ListaObiektowGui & ListaObiektowGui::operator=(const ListaObiektowGui & right){
		if (this != &right){
			BazowyWidzet::operator=(right);
			szerokoscSuwaka_ = right.szerokoscSuwaka_;
			odstepMiedzyKontrolkami_ = right.odstepMiedzyKontrolkami_;
			mnoznikRolki_ = right.mnoznikRolki_;
			typObiektu_ = right.typObiektu_;
			pokazSuwak_ = right.pokazSuwak_;
			czyAutoRozmiar_ = right.czyAutoRozmiar_;
			szablonKontrolki_ = KontrolkaObiektu::copy(right.szablonKontrolki_);
			suwak_ = m_panel->get<Scrollbar>("PasekPrzewijania"); 
			for (auto& widget : m_panel->getWidgets()) {
				if (widget->getWidgetType() == "KontrolkaObiektu") {
					kontrolki_.push_back(std::static_pointer_cast<KontrolkaObiektu>(widget));
				}
			}
			uaktualnijShader();
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
		uaktualnijShader();
	}

	void ListaObiektowGui::wyczyscDane() {
		std::lock_guard<std::mutex> lock(zmianaDanych_);
		m_panel->removeAllWidgets();
		szablonKontrolki_ = nullptr;
		kontrolki_.clear();
	}

	void ListaObiektowGui::uaktualnijShader(){
		auto shader = getRenderer()->getShader();
		if (shader && szablonKontrolki_) {
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
			shader->setParameter("texture", sf::Shader::CurrentTexture);
		}
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
			
	void ListaObiektowGui::scrollbarValueChanged(const tgui::Callback& callback){
		przeliczPozycjeKontrolek(callback.value);
	}

	void ListaObiektowGui::przeliczPozycjeKontrolek(int delta, bool uaktualnijRozmiar){
		if (!szablonKontrolki_)
			return;
		int t = 1;
		auto padding = getRenderer()->getPadding();
		auto size = szablonKontrolki_->getSize();
		auto upMargin = t*(size.y + odstepMiedzyKontrolkami_) + padding.top - 50;
		auto downMargin = (t + 1)*(size.y + odstepMiedzyKontrolkami_) + padding.top + 50;
		for (auto e : kontrolki_){
			if (uaktualnijRozmiar)
				e->setSize(size.x, size.y);
			auto hight = t*(size.y + odstepMiedzyKontrolkami_) + padding.top - delta;
			e->setPosition(static_cast<float>(padding.left), hight);
			t++;
		}
	}

	void ListaObiektowGui::uaktualnijSuwak(float hight, bool czyResetSuwaka){
		if (!szablonKontrolki_ || !suwak_)
			return;
		auto padding = getRenderer()->getPadding();
		auto size = szablonKontrolki_->getSize();
		float insideHight = (kontrolki_.size() + 2)*(size.y + odstepMiedzyKontrolkami_) + padding.top + padding.bottom - odstepMiedzyKontrolkami_;

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
		uaktualnijShader();
	}

	void ListaObiektowGui::setSize(const Layout2d& newSize){
		BazowyWidzet::setSize(newSize);
		auto padding = getRenderer()->getPadding();
		if (pokazSuwak_ && suwak_){
			auto size = suwak_->getSize();
			suwak_->setPosition(newSize.x - size.x, 0);
			suwak_->setSize(size.x, newSize.y);
			if (czyAutoRozmiar_ && szablonKontrolki_)
				szablonKontrolki_->setSize(newSize.x - (padding.left + padding.right + size.x), newSize.y);
		}
		else{
			if (czyAutoRozmiar_&& szablonKontrolki_)
				szablonKontrolki_->setSize(newSize.x - (padding.left + padding.right), newSize.y);
		}
		
		przeliczPozycjeKontrolek(0,true);
		uaktualnijSuwak(newSize.y.getValue(),false);
		uaktualnijShader();
	}

	void ListaObiektowGui::mouseWheelMoved(int delta, int x, int y){
		if(suwak_)
			suwak_->mouseWheelMoved(delta*mnoznikRolki_, x, y);
	}

	void ListaObiektowGui::draw(sf::RenderTarget& target, sf::RenderStates states) const{
		std::lock_guard<std::mutex> lock(zmianaDanych_);
		BazowyWidzet::draw(target, states);
	}

	void ListaObiektowGuiRenderer::setProperty(std::string property, const std::string & value){
		property = toLower(property);
		if (property == "KontrolkaObiektu") {
			if (toLower(value) == "none")
				static_cast<ListaObiektowGui*>(kontrolka_)->szablonKontrolki_ = nullptr;
			else {
				if (kontrolka_->getTheme() == nullptr)
					throw Exception{ "Failed to load Label, ListaObiektowGui has no connected theme to load the Label with" };

				static_cast<ListaObiektowGui*>(kontrolka_)->szablonKontrolki_ = kontrolka_->getTheme()->internalLoad(kontrolka_->getPrimaryLoadingParameter(), value);
			}
		}
		else if (property == "Scrollbar") {
			if (toLower(value) == "none")
				static_cast<ListaObiektowGui*>(kontrolka_)->suwak_ = nullptr;
			else {
				if (kontrolka_->getTheme() == nullptr)
					throw Exception{ "Failed to load Label, ListaObiektowGui has no connected theme to load the Label with" };

				static_cast<ListaObiektowGui*>(kontrolka_)->suwak_ = kontrolka_->getTheme()->internalLoad(kontrolka_->getPrimaryLoadingParameter(), value);
			}
		}
		else
			BazowyRenderer::setProperty(property, value);
	}

	void ListaObiektowGuiRenderer::setProperty(std::string property, ObjectConverter && value){
		property = toLower(property);
		if (property == "KontrolkaObiektu") {
			if (toLower(value.getString()) == "none")
				static_cast<ListaObiektowGui*>(kontrolka_)->szablonKontrolki_ = nullptr;
			else {
				if (kontrolka_->getTheme() == nullptr)
					throw Exception{ "Failed to load Label, ListaObiektowGui has no connected theme to load the Label with" };

				static_cast<ListaObiektowGui*>(kontrolka_)->szablonKontrolki_ = kontrolka_->getTheme()->internalLoad(kontrolka_->getPrimaryLoadingParameter(), value.getString());
			}
		}
		else if (property == "Scrollbar") {
			if (toLower(value.getString()) == "none")
				static_cast<ListaObiektowGui*>(kontrolka_)->suwak_ = nullptr;
			else {
				if (kontrolka_->getTheme() == nullptr)
					throw Exception{ "Failed to load Label, ListaObiektowGui has no connected theme to load the Label with" };

				static_cast<ListaObiektowGui*>(kontrolka_)->suwak_ = kontrolka_->getTheme()->internalLoad(kontrolka_->getPrimaryLoadingParameter(), value.getString());
			}
		}
		else
			BazowyRenderer::setProperty(property, std::move(value));
	}

	std::shared_ptr<WidgetRenderer> ListaObiektowGuiRenderer::clone(Widget * widget){
		auto renderer = std::make_shared<ListaObiektowGuiRenderer>(*this);
		renderer->kontrolka_ = static_cast<ListaObiektowGui*>(widget);
		return renderer;
	}
};
