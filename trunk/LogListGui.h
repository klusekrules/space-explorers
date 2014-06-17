#pragma once
#include <TGUI\TGUI.hpp>

namespace tgui{

	/**
	* \brief Klasa kontrolki wyœwietlaj¹cej logi.
	*
	* Klasa reprezentuje kontrolkê wyœwietlaj¹cej logi.
	* \warning Uwaga!!! Klasa przeznaczona do refaktoryzacji. Z tego powodu brak dokumentacji metod.
	* \author Daniel Wojdak
	* \version 1
	* \date 06-06-2014
	*/
	class LogListGui :
		public Panel
	{
	private:
		struct MessageTypeDescription{

			MessageTypeDescription(const sf::Color& colorFirst, const sf::Color& colorSecondary, unsigned int tekstFirst, unsigned int tekstSecondary)
			: colorFirst_(colorFirst), colorSecondary_(colorSecondary), textSizeFirst_(tekstFirst), textSizeSecondary_(tekstSecondary)
			{
			}
			
			sf::Color colorFirst_;
			sf::Color colorSecondary_;
			unsigned int textSizeFirst_;
			unsigned int textSizeSecondary_;
		};

	public:
		typedef std::vector<MessageTypeDescription>::size_type MessageType;

		static Widget* createWidget(Container*, const std::string& name);

		typedef SharedWidgetPtr<LogListGui> Ptr;

		LogListGui() = default;
		virtual ~LogListGui() = default;

		bool deleteLastMessage();
		bool addMessage( MessageType number , std::string text);

		void setSize(float width, float hight) override;
		bool load(const std::string& configFileFilename);
		virtual LogListGui* clone();
		void clear();
		const std::string& getLoadedConfigFile() const;
		virtual bool setProperty(std::string property, const std::string& value);
		virtual bool getProperty(std::string property, std::string& value) const;
		virtual std::list< std::pair<std::string, std::string> > getPropertyList() const;
	private:

		enum WYROWNANIE_WERTYKALNE{
			TOP,
			MIDDLE,
			BOTTOM
		};

		enum WYROWNANIE_HORYZONTALNE{
			LEFT,
			CENTER,
			RIGHT
		};

		void recalculatePosition();
		typedef std::vector< std::pair< MessageType, Label::Ptr> > ObjectList;

		ObjectList::size_type pos(int position)const;


		virtual void initialize(Container *const container);

		std::string m_LoadedConfigFile = "";

		ObjectList listaObiektow_;
		std::vector<MessageTypeDescription> opisTypowKomunikatow_;
		Borders margin_;
		float interspace_ = 0.f;
		unsigned int sum_ = 0;
		unsigned int empty_ = 0;
		unsigned int max_ = 0;
		bool autoSized_ = true;

		WYROWNANIE_WERTYKALNE wPionie_ = TOP;
		WYROWNANIE_HORYZONTALNE wPoziomie_ = CENTER;

	};
};
