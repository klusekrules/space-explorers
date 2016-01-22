#include "BazowyWidzet.h"
#include "BazowyRenderer.h"

namespace tgui {

	BazowyWidzet::BazowyWidzet(const BazowyWidzet& o)
		: Widget(o), m_panel(o.m_panel)
	{
		m_callback.widgetType = "BazowyWidzet";
		m_draggableWidget = false;
	}

	BazowyWidzet& BazowyWidzet::operator=(const BazowyWidzet & right){
		if (this != &right){
			Widget::operator=(right);
			m_panel = Panel::copy(right.m_panel);
		}

		return *this;
	}

	void BazowyWidzet::setPosition(const Layout2d& position){
		Widget::setPosition(position);

		getRenderer()->m_backgroundTexture.setPosition(getPosition());

		updateRendering();
	}

	void BazowyWidzet::setSize(const Layout2d& size){
		Widget::setSize(size);

		getRenderer()->m_backgroundTexture.setSize(getSize());

		updateRendering();
	}

	sf::Vector2f BazowyWidzet::getFullSize() const{
		return{ getSize().x + getRenderer()->m_borders.left + getRenderer()->m_borders.right,
			getSize().y + getRenderer()->m_borders.top + getRenderer()->m_borders.bottom };
	}

	void BazowyWidzet::setFont(const Font& font)
	{
		Widget::setFont(font);

		for (auto& widzet : m_panel->getWidgets()){
			widzet->setFont(font);
		}

	}


	void BazowyWidzet::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		if (getRenderer()->getShader() != nullptr){
			states.shader = getRenderer()->getShader();
		}
		// Draw the background
		getRenderer()->draw(target, states);

		// Draw the panel
		target.draw(*m_panel, states);
	}

	void BazowyWidzet::updateRendering()
	{
		Padding padding = getRenderer()->getPadding();
		Padding scaledPadding = padding;

		auto& texture = getRenderer()->m_backgroundTexture;
		if (texture.isLoaded()){
			switch (texture.getScalingType()){
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

	void BazowyWidzet::reload(const std::string& primary, const std::string& secondary, bool force)
	{
		auto renderer = getRenderer();
		renderer->setBackgroundColor({ 0, 0, 0 ,0 });
		
		if (m_theme && primary != ""){
			Widget::reload(primary, secondary, force);

			if (force){
				if (renderer->m_backgroundTexture.isLoaded())
					setSize(renderer->m_backgroundTexture.getImageSize());
			}

			updateSize();
		}
	}

	bool BazowyWidzet::mouseOnWidget(float, float) const {
		/// TODO: implementacja metody
		return false;
	}

};