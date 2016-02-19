#pragma once
#include "TGUI\TGUI.hpp"
#include "BazowyWidzet.h"
#include "Widok\SFML\SpShader.h"

namespace tgui {
	class BazowyRenderer:
		public WidgetRenderer, public WidgetBorders, public WidgetPadding
	{
	public:
		friend class BazowyWidzet;

		BazowyRenderer(BazowyWidzet* kontrolka);

		void setProperty(std::string property, const std::string& value) override;
		void setProperty(std::string property, ObjectConverter&& value) override;
		ObjectConverter getProperty(std::string property) const override;
		std::map<std::string, ObjectConverter> getPropertyValuePairs() const override;

		void setBorderColor(const sf::Color& borderColor);
		void setBackgroundColor(const sf::Color& backgroundColor);
		void setBackgroundTexture(const Texture& texture);

		void setPadding(const Padding& padding) override;
		using WidgetPadding::setPadding;

		void setShader(std::shared_ptr<sf::SpShader>);
		std::shared_ptr<sf::SpShader> getShader() const;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	protected:
		BazowyWidzet *kontrolka_;

		std::shared_ptr<sf::SpShader> shader_;

		sf::Color m_borderColor;
		sf::Color m_backgroundColor;

		Texture m_backgroundTexture;

	};

};