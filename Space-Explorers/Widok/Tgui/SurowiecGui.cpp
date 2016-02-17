#include "SurowiecGui.h"
#include "Model\Obiekt.h"
namespace tgui {
	//-------------
	// SurowiecGui
	//-------------

	SurowiecGui::SurowiecGui()
		:BazowyWidzet()
	{
		m_callback.widgetType = "SurowiecGui";
		m_draggableWidget = false;

		tekst_ = std::make_shared<Label>();
		tekst_->setAutoSize(true);
		tekst_->setTextSize(14);
		tekst_->setTextColor({255,255,255});
		m_panel->add(tekst_,"Nazwa");
		tekst_->setPosition({"w > &.w ? 0 : (&.w - w) / 2"}, { "h > &.h ? 0 : (&.h - h) / 2" });
		m_panel->setBackgroundColor(sf::Color::Transparent);

		m_renderer = std::make_shared<SurowiecGuiRenderer>(this);
		reload("","",true);
	}

	SurowiecGui::SurowiecGui(const SurowiecGui& o)
		:BazowyWidzet(o), idObiektu_(o.idObiektu_)
	{
		tekst_ = m_panel->get<Label>("Nazwa");
	}

	SurowiecGui& SurowiecGui::operator=(const SurowiecGui & right){
		if (this != &right){
			BazowyWidzet::operator=(right);
			tekst_ = m_panel->get<Label>("Nazwa");
		}

		return *this;
	}

	SurowiecGui::Ptr SurowiecGui::copy(SurowiecGui::ConstPtr surowiecGui){
		if (surowiecGui)
			return std::static_pointer_cast<SurowiecGui>(surowiecGui->clone());
		else
			return nullptr;
	}

	void SurowiecGui::ustawKontrolkeLabel(Label::Ptr ptr) {
		m_panel->remove(tekst_);
		tekst_ = ptr;
		if (tekst_)
			m_panel->add(tekst_);
	}
		
	const STyp::Identyfikator& SurowiecGui::pobierzIdObiektu() const {
		return idObiektu_;
	}
	
	void SurowiecGui::reload(const std::string& primary, const std::string& secondary, bool force){
		auto renderer = getRenderer();
		renderer->setBorders({ 0, 0, 0, 0 });
		renderer->setPadding({ 0, 0, 0, 0 });
		renderer->setBackgroundTexture({ "widgets\\tlo_surowce.png" });

		if (m_theme && primary != ""){
			BazowyWidzet::reload(primary, secondary, force);
		}

		if (force) {
			if (renderer->m_backgroundTexture.isLoaded())
				setSize(renderer->m_backgroundTexture.getImageSize());
		}

		updateSize();
	}

	void SurowiecGui::ustawDane(const SpEx::Obiekt& obiekt) {
		std::string napis;
		idObiektu_ = obiekt.pobierzIdentyfikator();
		napis += obiekt.pobierzObiektInfo().pobierzNazwe()() + "\n" + std::to_string(obiekt.pobierzIlosc()());
		tekst_->setText(napis);
		updateSize(true);
	}

	void SurowiecGui::setTextSize(unsigned int size) {
		tekst_->setTextSize(size);
	}

	void SurowiecGui::setTextColor(sf::Color color) {
		tekst_->setTextColor(color);
	}
		
	void SurowiecGuiRenderer::setProperty(std::string property, const std::string& value) {
		property = toLower(property);

		if (property == "label"){
			if (toLower(value) == "none")
				static_cast<SurowiecGui*>(kontrolka_)->ustawKontrolkeLabel(nullptr);
			else{
				if (kontrolka_->getTheme() == nullptr)
					throw Exception{ "Failed to load Label, SurowiecGui has no connected theme to load the Label with" };

				static_cast<SurowiecGui*>(kontrolka_)->ustawKontrolkeLabel(kontrolka_->getTheme()->internalLoad(kontrolka_->getPrimaryLoadingParameter(), value));
			}
		}else
			BazowyRenderer::setProperty(property, value);
	}

	void SurowiecGuiRenderer::setProperty(std::string property, ObjectConverter&& value) {
		property = toLower(property);

		if (value.getType() == ObjectConverter::Type::String){
			if (property == "label"){
				if (toLower(value.getString()) == "none")
					static_cast<SurowiecGui*>(kontrolka_)->ustawKontrolkeLabel(nullptr);
				else{
					if (kontrolka_->getTheme() == nullptr)
						throw Exception{ "Failed to load Label, SurowiecGui has no connected theme to load the Label with" };

					static_cast<SurowiecGui*>(kontrolka_)->ustawKontrolkeLabel(kontrolka_->getTheme()->internalLoad(kontrolka_->getPrimaryLoadingParameter(), value.getString()));
				}
			}else
				BazowyRenderer::setProperty(property, std::move(value));
		}else
			BazowyRenderer::setProperty(property, std::move(value));
	}

	std::shared_ptr<WidgetRenderer> SurowiecGuiRenderer::clone(Widget * widget){
		auto renderer = std::make_shared<SurowiecGuiRenderer>(*this);
		renderer->kontrolka_ = static_cast<SurowiecGui*>(widget);
		return renderer;
	}

};
