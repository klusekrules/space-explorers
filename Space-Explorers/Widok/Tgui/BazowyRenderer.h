#pragma once
#include "TGUI\TGUI.hpp"
#include "BazowyWidzet.h"

namespace tgui {
	class BazowyRenderer:
		public WidgetRenderer, public WidgetBorders, public WidgetPadding
	{
	public:
		friend class BazowyWidzet;

		BazowyRenderer(BazowyWidzet* kontrolka);
		BazowyRenderer& operator=(const BazowyRenderer&) = delete;

		void setProperty(std::string property, const std::string& value) override;
		void setProperty(std::string property, ObjectConverter&& value) override;
		ObjectConverter getProperty(std::string property) const override;
		std::map<std::string, ObjectConverter> getPropertyValuePairs() const override;

		void setBorderColor(const sf::Color& borderColor);
		void setBackgroundColor(const sf::Color& backgroundColor);
		void setBackgroundTexture(const Texture& texture);

		void setPadding(const Padding& padding) override;
		using WidgetPadding::setPadding;

		void setShader(const sf::Shader*);
		const sf::Shader* getShader() const;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	protected:
		BazowyRenderer(const BazowyRenderer&) = default;

		BazowyWidzet *kontrolka_;

		const sf::Shader* shader_;

		sf::Color m_borderColor;
		sf::Color m_backgroundColor;

		Texture m_backgroundTexture;

	};

};