#include "BazowyRenderer.h"

namespace tgui {

	BazowyRenderer::BazowyRenderer(BazowyWidzet* kontrolka) 
		: kontrolka_(kontrolka), shader_(nullptr)
	{}


	void BazowyRenderer::setProperty(std::string property, const std::string& value) {
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

	void BazowyRenderer::setProperty(std::string property, ObjectConverter&& value) {
		property = toLower(property);
		WidgetRenderer::setProperty(property, std::move(value));
	}

	ObjectConverter BazowyRenderer::getProperty(std::string property) const {
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
	}

	std::map<std::string, ObjectConverter> BazowyRenderer::getPropertyValuePairs() const {
		auto map = WidgetRenderer::getPropertyValuePairs();
		map["BackgroundColor"] = m_backgroundColor;
		map["BorderColor"] = m_borderColor;
		map["Texture"] = m_backgroundTexture;
		map["Shader"] = !!shader_;
		return map;
	}

	void tgui::BazowyRenderer::setBorderColor(const sf::Color & borderColor)
	{
		m_borderColor = borderColor;
	}

	void tgui::BazowyRenderer::setBackgroundColor(const sf::Color & backgroundColor)
	{
		m_backgroundColor = backgroundColor;
	}

	void BazowyRenderer::setBackgroundTexture(const Texture & texture)
	{
		m_backgroundTexture = texture;
		if (m_backgroundTexture.isLoaded())
		{
			m_backgroundTexture.setPosition(kontrolka_->getPosition());
			m_backgroundTexture.setSize(kontrolka_->getSize());
			m_backgroundTexture.setColor({ 255, 255, 255, static_cast<sf::Uint8>(kontrolka_->getOpacity() * 255) });
		}
	}

	void BazowyRenderer::setPadding(const Padding & padding)
	{
		WidgetPadding::setPadding(padding);

		kontrolka_->updateRendering();
	}

	void BazowyRenderer::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{

		if (m_backgroundTexture.isLoaded())
			target.draw(m_backgroundTexture, states);
		else
		{
			sf::RectangleShape background(kontrolka_->getSize());
			background.setPosition(kontrolka_->getPosition());
			background.setFillColor(calcColorOpacity(m_backgroundColor, kontrolka_->getOpacity()));
			target.draw(background, states);
		}

		if (m_borders != Borders{ 0, 0, 0, 0 })
		{
			sf::Vector2f position = kontrolka_->getPosition();
			sf::Vector2f size = kontrolka_->getSize();

			// Draw left border
			sf::RectangleShape border({ m_borders.left, size.y + m_borders.top });
			border.setPosition({ position.x - m_borders.left, position.y - m_borders.top });
			border.setFillColor(calcColorOpacity(m_borderColor, kontrolka_->getOpacity()));
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

	void BazowyRenderer::copyParameters(const BazowyRenderer & object){
		WidgetBorders::operator=(object);
		WidgetPadding::operator=(object);
		shader_ = object.shader_;
		m_borderColor = object.m_borderColor;
		m_backgroundColor = object.m_backgroundColor;
		m_backgroundTexture = object.m_backgroundTexture;
	}
	
	void BazowyRenderer::setShader(const sf::Shader* shader) {
		shader_ = shader;
	}

	const sf::Shader* BazowyRenderer::getShader() const {
		return shader_;
	}
};