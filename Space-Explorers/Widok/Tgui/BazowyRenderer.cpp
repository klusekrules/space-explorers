#include "BazowyRenderer.h"

namespace tgui {

	BazowyRenderer::BazowyRenderer(BazowyWidzet* kontrolka) 
		: kontrolka_(kontrolka), shader_(nullptr)
	{}

	void BazowyRenderer::setProperty(std::string property, const std::string& value) {
		property = toLower(property);
		if (property == "borders")
			setBorders(Deserializer::deserialize(ObjectConverter::Type::Borders, value).getBorders());
		else if (property == "padding")
			setPadding(Deserializer::deserialize(ObjectConverter::Type::Borders, value).getBorders());
		else if (property == "backgroundcolor")
			setBackgroundColor(Deserializer::deserialize(ObjectConverter::Type::Color, value).getColor());
		else if (property == "bordercolor")
			setBorderColor(Deserializer::deserialize(ObjectConverter::Type::Color, value).getColor());
		else if (property == "backgroundimage")
			setBackgroundTexture(Deserializer::deserialize(ObjectConverter::Type::Texture, value).getTexture());
		else if (property == "shader") {
			shader_ = std::make_shared<sf::SpShader>();
			if (!shader_->loadFromParam(value)) {
				shader_ = nullptr;
			}
		}else
			WidgetRenderer::setProperty(property, value);
	}

	void BazowyRenderer::setProperty(std::string property, ObjectConverter&& value) {
		property = toLower(property);

		if (value.getType() == ObjectConverter::Type::Borders){
			if (property == "borders")
				setBorders(value.getBorders());
			else if (property == "padding")
				setPadding(value.getBorders());
		}else if (value.getType() == ObjectConverter::Type::Color){
			if (property == "backgroundcolor")
				setBackgroundColor(value.getColor());
			else if (property == "bordercolor")
				setBorderColor(value.getColor());
		}else if (value.getType() == ObjectConverter::Type::Texture){
			if (property == "backgroundimage")
				setBackgroundTexture(value.getTexture());
		}else if (value.getType() == ObjectConverter::Type::String) {
			if (property == "shader")
				shader_ = std::make_shared<sf::SpShader>();
				if (!shader_->loadFromParam(value.getString())) {
					shader_ = nullptr;
				}
		}else
			WidgetRenderer::setProperty(property, std::move(value));
	}

	ObjectConverter BazowyRenderer::getProperty(std::string property) const {
		property = toLower(property);

		if (property == "borders")
			return m_borders;
		else if (property == "padding")
			return m_padding;
		else if (property == "backgroundcolor")
			return m_backgroundColor;
		else if (property == "Shader") {
			if (shader_)
				return shader_->getParamString();
			else
				return "none";
		}
		else if (property == "bordercolor")
			return m_borderColor;
		else if (property == "backgroundimage")
			return m_backgroundTexture;
		else
			return WidgetRenderer::getProperty(property);
	}

	std::map<std::string, ObjectConverter> BazowyRenderer::getPropertyValuePairs() const {
		auto map = WidgetRenderer::getPropertyValuePairs();
		if (m_backgroundTexture.isLoaded())
			map["BackgroundImage"] = m_backgroundTexture;
        else
			map["BackgroundColor"] = m_backgroundColor;
		map["BorderColor"] = m_borderColor;

		if (shader_)
			map["Shader"] = shader_->getParamString();
		else
			map["Shader"] = sf::String("none");

		map["Borders"] = m_borders;
		map["Padding"] = m_padding;
		return map;
	}

	void tgui::BazowyRenderer::setBorderColor(const sf::Color & borderColor){
		m_borderColor = borderColor;
	}

	void tgui::BazowyRenderer::setBackgroundColor(const sf::Color & backgroundColor){
		m_backgroundColor = backgroundColor;
	}

	void BazowyRenderer::setBackgroundTexture(const Texture & texture){
		m_backgroundTexture = texture;
		if (m_backgroundTexture.isLoaded()){
			m_backgroundTexture.setPosition(kontrolka_->getPosition());
			m_backgroundTexture.setSize(kontrolka_->getSize());
			m_backgroundTexture.setColor({ 255, 255, 255, static_cast<sf::Uint8>(kontrolka_->getOpacity() * 255) });
		}
	}

	void BazowyRenderer::setPadding(const Padding & padding){
		WidgetPadding::setPadding(padding);
	}

	void BazowyRenderer::draw(sf::RenderTarget & target, sf::RenderStates states) const{
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
		
	void BazowyRenderer::setShader(std::shared_ptr<sf::SpShader> shader) {
		shader_ = shader;
	}

	std::shared_ptr<sf::SpShader> BazowyRenderer::getShader() const {
		return shader_;
	}
};