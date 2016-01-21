#pragma once
#include <TGUI\TGUI.hpp>

namespace tgui {

	class BazowyWidzet :
		public Widget
	{
		friend class BazowyRenderer;
	public:
		typedef std::shared_ptr<BazowyWidzet> Ptr; ///< Shared widget pointer
		typedef std::shared_ptr<const BazowyWidzet> ConstPtr; ///< Shared constant widget pointer
		
		BazowyWidzet() = default;

		BazowyWidzet(const BazowyWidzet& zrodlowy);

		BazowyWidzet& operator= (const BazowyWidzet& right);
		
		void setPosition(const Layout2d& position) override;
		using Transformable::setPosition;

		void setSize(const Layout2d& size) override;
		using Transformable::setSize;

		sf::Vector2f getFullSize() const override;

		void setFont(const Font& font);

		std::shared_ptr<sf::Font> getTextFont() {
			return m_panel->getFont();
		}

		bool mouseOnWidget(float x, float y) override;

		std::shared_ptr<BazowyRenderer> getRenderer() const {
			return std::static_pointer_cast<BazowyRenderer>(m_renderer);
		}

		Widget::Ptr clone() const override{
			return std::make_shared<BazowyWidzet>(*this);
		}

	protected:

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		void reload(const std::string& primary = "", const std::string& secondary = "", bool force = false) override;

		Panel::Ptr m_panel = std::make_shared<Panel>();

		virtual void updateRendering();

		friend class std::shared_ptr<DataIO::Node> saveBazowyWidzet(BazowyWidzet::Ptr widget);
	};
};