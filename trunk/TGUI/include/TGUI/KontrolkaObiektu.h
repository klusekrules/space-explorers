#pragma once
#include <TGUI\TGUI.hpp>
namespace tgui{
	class TGUI_API KontrolkaObiektu :
		public Panel
	{
	public:
		static Widget* createWidget(Container*, const std::string& name);

		typedef SharedWidgetPtr<KontrolkaObiektu> Ptr;

		KontrolkaObiektu();
		KontrolkaObiektu(const KontrolkaObiektu&);
		virtual ~KontrolkaObiektu() = default;

		bool ustawObrazek(const std::string& obraz);
		void ustawNazwe(const std::string& tekst);
		void ustawOpis(const std::string& opis);
		void ustawShader(sf::Shader* shader = nullptr);

		void blokowanieOk(bool zablokowane);
		void blokowanieCancel(bool zablokowane);

		void setTransparency(unsigned char transparency);
		void setSize(float width, float hight);
		bool load(const std::string& configFileFilename);
		virtual KontrolkaObiektu* clone();
		const std::string& getLoadedConfigFile() const;
		virtual bool setProperty(std::string property, const std::string& value);
		virtual bool getProperty(std::string property, std::string& value) const;
		virtual std::list< std::pair<std::string, std::string> > getPropertyList() const;
	protected:

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Draws the widget on the render target.
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:

		virtual void initialize(Container *const container);

		std::string m_LoadedConfigFile;

		Texture background_;
		Picture::Ptr picture_;
		Label::Ptr nazwa_;
		Label::Ptr tresc_;
		Button::Ptr ok_;
		Button::Ptr can_;
		sf::Shader* shader_ = nullptr;
		
		sf::Vector2f size_;
		sf::Rect<float> pictureRect_;
		sf::Rect<float> titleRect_;
		sf::Rect<float> DescribeRect_;
		sf::Rect<float> ButtonOKRect_;
		sf::Rect<float> ButtonCanRect_;

		bool constSize_ = false;
		bool propotional_ = true;
	};
};
