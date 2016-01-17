#pragma once
#include "TGUI\TGUI.hpp"

namespace tgui {

	class BazowyWidzet :
		public Widget
	{
		typedef std::shared_ptr<BazowyWidzet> Ptr; ///< Shared widget pointer
		typedef std::shared_ptr<const BazowyWidzet> ConstPtr; ///< Shared constant widget pointer

		friend class BazowyRenderer;
	public:
		BazowyWidzet() = default;

		BazowyWidzet(const BazowyWidzet& zrodlowy);

		BazowyWidzet& operator= (const BazowyWidzet& right);

		std::shared_ptr<BazowyRenderer> getRenderer() const {
			return std::static_pointer_cast<BazowyRenderer>(m_renderer);
		}

		virtual void setPosition(const Layout2d& position) override;
		using Transformable::setPosition;

		void setSize(const Layout2d& size) override;
		using Transformable::setSize;

		virtual sf::Vector2f getFullSize() const override;

		void setFont(const Font& font);

		std::shared_ptr<sf::Font> getTextFont() {
			return m_panel->getFont();
		}

		bool mouseOnWidget(float x, float y) override;

	protected:

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		virtual Widget::Ptr clone() const override
		{
			return std::make_shared<BazowyWidzet>(*this);
		}

		virtual void reload(const std::string& primary = "", const std::string& secondary = "", bool force = false) override;

		Panel::Ptr m_panel = std::make_shared<Panel>();

		virtual void updateRendering();

	};
};