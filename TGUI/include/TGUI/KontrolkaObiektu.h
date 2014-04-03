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
		void ustawNazwe(sf::String& tekst);
		void ustawOpis(sf::String& opis);

		void blokowanieOk(bool zablokowane);
		void blokowanieCancel(bool zablokowane);

		void setSize(float width, float hight);
		bool load(const std::string& configFileFilename);
		virtual KontrolkaObiektu* clone();
		const std::string& getLoadedConfigFile() const;
		virtual bool setProperty(std::string property, const std::string& value);
		virtual bool getProperty(std::string property, std::string& value) const;
		virtual std::list< std::pair<std::string, std::string> > getPropertyList() const;
	private:

		virtual void initialize(Container *const container);

		std::string m_LoadedConfigFile;

		Picture::Ptr picture_;
		Label::Ptr nazwa_;
		Label::Ptr tresc_;
		Button::Ptr ok_;
		Button::Ptr can_;

		float marginUp = 5.f;
		float marginDown = 5.f;
		float marginLeft = 5.f;
		float marginRight = 5.f;
		float distance = 7.f;
		float marginButtonUp = 10.f;
		float marginButtonDown = 10.f;
		float marginButtonLeft = 11.f;
		float marginButtonRight = 5.f;
		float ratio = 3.7f;
	};
};
