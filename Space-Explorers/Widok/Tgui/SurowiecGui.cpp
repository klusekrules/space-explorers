#include "SurowiecGui.h"
#include "Model\Obiekt.h"
namespace tgui {
	//-------------
	// SurowiecGui
	//-------------

	SurowiecGui::SurowiecGui(const SurowiecGui& o)
		:BazowyWidzet(o), plikKonfiguracyjny_(o.plikKonfiguracyjny_), idObiektu_(o.idObiektu_)
	{
		/*tekst_ = this->get<Label>("Nazwa");*/
	}

	SurowiecGui& SurowiecGui::operator=(const SurowiecGui & right)
	{
		if (this != &right)
		{
			SurowiecGui temp(right);
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
		
	const STyp::Identyfikator& SurowiecGui::pobierzIdObiektu() const {
		return idObiektu_;
	}
	
	void SurowiecGui::reload(const std::string& primary, const std::string& secondary, bool force)
	{
		getRenderer()->setBorders({ 2, 2, 2, 2 });
		getRenderer()->setPadding({ 2, 2, 2, 2 });
		getRenderer()->setBackgroundColor({ 245, 245, 245 });
		getRenderer()->setBorderColor({ 245, 0, 0 });
		getRenderer()->setBackgroundTexture({ "widgets\\tlo.png" });

		if (m_theme && primary != "")
		{
			getRenderer()->setBorders({ 0, 0, 0, 0 });
			getRenderer()->setPadding({ 0, 0, 0, 0 });

			Widget::reload(primary, secondary, force);

			if (force)
			{
				if (getRenderer()->m_backgroundTexture.isLoaded())
					setSize(getRenderer()->m_backgroundTexture.getImageSize());
			}

			updateSize();
		}
	}

	void SurowiecGui::ustawDane(const SpEx::Obiekt& obiekt) {
		std::string napis;
		idObiektu_ = obiekt.pobierzIdentyfikator();
		napis += obiekt.pobierzObiektInfo().pobierzNazwe()() + "\n" + std::to_string(obiekt.pobierzIlosc()());
		tekst_->setText(napis);
		auto size = tekst_->getSize();
		setSize(size.x, size.y);
	}

	void SurowiecGui::setTextSize(unsigned int size) {
		tekst_->setTextSize(size);
	}

	void SurowiecGui::setTextColor(sf::Color color) {
		tekst_->setTextColor(color);
	}
		
	std::shared_ptr<WidgetRenderer> tgui::SurowiecGuiRenderer::clone(Widget * widget)
	{
		auto renderer = std::shared_ptr<SurowiecGuiRenderer>(new SurowiecGuiRenderer{ *this });
		renderer->kontrolka_ = static_cast<BazowyWidzet*>(widget);
		return renderer;
	}

};
