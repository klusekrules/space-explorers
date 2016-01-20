#include "SurowiecGui.h"
#include "Model\Obiekt.h"
namespace tgui {
	//-------------
	// SurowiecGui
	//-------------

	SurowiecGui::SurowiecGui()
		:BazowyWidzet()
	{
		m_callback.widgetType = "KontrolkaObiektu";
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
		
	std::shared_ptr<WidgetRenderer> tgui::SurowiecGuiRenderer::clone(Widget * widget){
		auto renderer = std::shared_ptr<SurowiecGuiRenderer>(new SurowiecGuiRenderer{ *this });
		renderer->kontrolka_ = static_cast<BazowyWidzet*>(widget);
		return renderer;
	}

};
