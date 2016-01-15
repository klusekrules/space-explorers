#include "SurowiecGui.h"
#include "Model\Obiekt.h"
namespace tgui {
	//-------------
	// SurowiecGui
	//-------------

	SurowiecGui::SurowiecGui(const SurowiecGui& o)
		:Widget(o), plikKonfiguracyjny_(o.plikKonfiguracyjny_), idObiektu_(o.idObiektu_)
	{
		/*tekst_ = this->get<Label>("Nazwa");*/
	}

	SurowiecGui& SurowiecGui::operator=(const SurowiecGui & right)
	{
		if (this != &right)
		{
			SurowiecGui temp(right);
			Widget::operator=(right);

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
	
	void SurowiecGui::setPosition(const Layout2d& position)
	{
		Widget::setPosition(position);

		getRenderer()->m_backgroundTexture.setPosition(getPosition());

		updateRendering();
	}

	void SurowiecGui::setSize(const Layout2d& size)
	{
		Widget::setSize(size);

		getRenderer()->m_backgroundTexture.setSize(getSize());

		//updatePosition();
	}

	sf::Vector2f SurowiecGui::getFullSize() const
	{
		return{ getSize().x + getRenderer()->m_borders.left + getRenderer()->m_borders.right,
			getSize().y + getRenderer()->m_borders.top + getRenderer()->m_borders.bottom };
	}

	void SurowiecGui::setFont(const Font& font)
	{
		Widget::setFont(font);

		bool lineChanged = false;
		for (auto& label : m_panel->getWidgets())
		{
			auto line = std::static_pointer_cast<Label>(label);
			if (line->getFont() == nullptr)
			{
				line->setFont(font);
				lineChanged = true;
			}
		}

		if (lineChanged)
		{

		}
	}

	const STyp::Identyfikator& SurowiecGui::pobierzIdObiektu() const {
		return idObiektu_;
	}
	
	void SurowiecGui::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		/*if (shader_ != nullptr) {
			states.shader = shader_;
		}*/
		// Draw the background
		getRenderer()->draw(target, states);

		// Draw the panel
		target.draw(*m_panel, states);
	}
	
	void SurowiecGui::updateRendering()
	{
		Padding padding = getRenderer()->getPadding();
		Padding scaledPadding = padding;

		auto& texture = getRenderer()->m_backgroundTexture;
		if (texture.isLoaded())
		{
			switch (texture.getScalingType())
			{
			case Texture::ScalingType::Normal:
				scaledPadding.left = padding.left * (texture.getSize().x / texture.getImageSize().x);
				scaledPadding.right = padding.right * (texture.getSize().x / texture.getImageSize().x);
				scaledPadding.top = padding.top * (texture.getSize().y / texture.getImageSize().y);
				scaledPadding.bottom = padding.bottom * (texture.getSize().y / texture.getImageSize().y);
				break;

			case Texture::ScalingType::Horizontal:
				scaledPadding.left = padding.left * (texture.getSize().y / texture.getImageSize().y);
				scaledPadding.right = padding.right * (texture.getSize().y / texture.getImageSize().y);
				scaledPadding.top = padding.top * (texture.getSize().y / texture.getImageSize().y);
				scaledPadding.bottom = padding.bottom * (texture.getSize().y / texture.getImageSize().y);
				break;

			case Texture::ScalingType::Vertical:
				scaledPadding.left = padding.left * (texture.getSize().x / texture.getImageSize().x);
				scaledPadding.right = padding.right * (texture.getSize().x / texture.getImageSize().x);
				scaledPadding.top = padding.top * (texture.getSize().x / texture.getImageSize().x);
				scaledPadding.bottom = padding.bottom * (texture.getSize().x / texture.getImageSize().x);
				break;

			case Texture::ScalingType::NineSliceScaling:
				break;
			}
		}

		m_panel->setPosition({ getPosition().x + scaledPadding.left, getPosition().y + scaledPadding.top });
		m_panel->setSize({ getSize().x - scaledPadding.left - scaledPadding.right, getSize().y - scaledPadding.top - scaledPadding.bottom });

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
	
	bool SurowiecGui::mouseOnWidget(float, float) {
		/// TODO: implementacja metody
		return false;
	}

	void SurowiecGuiRenderer::setProperty(std::string property, const std::string& value) {
		property = toLower(property);

		/*if (property == "image"){
		obraz_->load(value);
		}else if(property == "idzdarzeniabudowy"){
		idZdarzeniaBudowy_ = std::strtol(value.c_str(), nullptr, 10);
		true;
		}
		else if (property == "idzdarzeniaburzenia"){
		idZdarzeniaBurzenia_ = std::strtol(value.c_str(), nullptr, 10);
		true;
		}
		else if (property == "idzdarzeniaklikniecia"){
		idZdarzeniaKlikniecia_ = std::strtol(value.c_str(), nullptr, 10);
		true;
		}
		else if (property == "configfile"){
		load(value);
		}else*/
		WidgetRenderer::setProperty(property, value);
	}

	void SurowiecGuiRenderer::setProperty(std::string property, ObjectConverter&& value) {
		property = toLower(property);
		WidgetRenderer::setProperty(property, std::move(value));
	}

	ObjectConverter SurowiecGuiRenderer::getProperty(std::string property) const {
		/*if (property == "Image"){
		value = obraz_->getLoadedFilename();
		return true;
		}else if (property == "ConfigFile"){
		value = plikKonfiguracyjny_;
		return true;
		}else if(property == "IdZdarzeniaBudowy"){
		value = idZdarzeniaBudowy_;
		}
		else if (property == "IdZdarzeniaBurzenia"){
		value = idZdarzeniaBurzenia_;
		}
		else if (property == "IdZdarzeniaKlikniecia"){
		value = idZdarzeniaKlikniecia_;
		}
		else*/
		return WidgetRenderer::getProperty(property);
		//return true;
	}

	std::map<std::string, ObjectConverter> SurowiecGuiRenderer::getPropertyValuePairs() const {
		auto map = WidgetRenderer::getPropertyValuePairs();
		/*map.push_back(std::pair<std::string, std::string>("ConfigFile", "string"));
		map.push_back(std::pair<std::string, std::string>("Image", "string"));
		map.push_back(std::pair<std::string, std::string>("IdZdarzeniaBudowy", "int"));
		map.push_back(std::pair<std::string, std::string>("IdZdarzeniaBurzenia", "int"));
		map.push_back(std::pair<std::string, std::string>("IdZdarzeniaKlikniecia", "int"));*/
		return map;
	}

	void tgui::SurowiecGuiRenderer::setBorderColor(const sf::Color & borderColor)
	{
		m_borderColor = borderColor;
	}

	void tgui::SurowiecGuiRenderer::setBackgroundColor(const sf::Color & backgroundColor)
	{
		m_backgroundColor = backgroundColor;
	}

	void tgui::SurowiecGuiRenderer::setBackgroundTexture(const Texture & texture)
	{
		m_backgroundTexture = texture;
		if (m_backgroundTexture.isLoaded())
		{
			m_backgroundTexture.setPosition(m_surowceGui->getPosition());
			m_backgroundTexture.setSize(m_surowceGui->getSize());
			m_backgroundTexture.setColor({ 255, 255, 255, static_cast<sf::Uint8>(m_surowceGui->getOpacity() * 255) });
		}
	}

	void tgui::SurowiecGuiRenderer::setPadding(const Padding & padding)
	{
		WidgetPadding::setPadding(padding);

		m_surowceGui->updateRendering();
	}

	void tgui::SurowiecGuiRenderer::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{

		if (m_backgroundTexture.isLoaded())
			target.draw(m_backgroundTexture, states);
		else
		{
			sf::RectangleShape background(m_surowceGui->getSize());
			background.setPosition(m_surowceGui->getPosition());
			background.setFillColor(calcColorOpacity(m_backgroundColor, m_surowceGui->getOpacity()));
			target.draw(background, states);
		}

		if (m_borders != Borders{ 0, 0, 0, 0 })
		{
			sf::Vector2f position = m_surowceGui->getPosition();
			sf::Vector2f size = m_surowceGui->getSize();

			// Draw left border
			sf::RectangleShape border({ m_borders.left, size.y + m_borders.top });
			border.setPosition({ position.x - m_borders.left, position.y - m_borders.top });
			border.setFillColor(calcColorOpacity(m_borderColor, m_surowceGui->getOpacity()));
			target.draw(border, states);

			// Draw top border
			border.setSize({ size.x + m_borders.right, m_borders.top });
			border.setPosition({ position.x, position.y - m_borders.top });
			target.draw(border, states);

			// Draw right border
			border.setSize({ m_borders.right, size.y + m_borders.bottom });
			border.setPosition({ position.x + size.x, position.y });
			target.draw(border, states);

			// Draw bottom border
			border.setSize({ size.x + m_borders.left, m_borders.bottom });
			border.setPosition({ position.x - m_borders.left, position.y + size.y });
			target.draw(border, states);
		}
	}

	std::shared_ptr<WidgetRenderer> tgui::SurowiecGuiRenderer::clone(Widget * widget)
	{
		auto renderer = std::shared_ptr<SurowiecGuiRenderer>(new SurowiecGuiRenderer{ *this });
		renderer->m_surowceGui = static_cast<SurowiecGui*>(widget);
		return renderer;
	}

};
