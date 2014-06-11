#pragma once
#include <TGUI\TGUI.hpp>
#include "ObiektInfo.h"

namespace tgui{

	void convertFromBorderToRect(const Borders&, sf::Rect<float>&);
	void normalizujRect(sf::Rect<float>&, float leftWidth, float topHeight);


	/**
	* \brief Klasa kontrolki obiektu.
	*
	* Klasa reprezentuje kontrolkê obiektu. Wyœwietla aktualne dane o obiekcie znajduj¹cym sie na planecie. Pozwala na rozbudowe.
	* \warn Uwaga!!! Klasa przeznaczona do refaktoryzacji. Z tego powodu brak dokumentacji metod.
	* \author Daniel Wojdak
	* \version 1
	* \date 06-06-2014
	*/
	class KontrolkaObiektu :
		public Panel
	{
	public:
		static Widget* createWidget(Container*, const std::string& name);

		typedef SharedWidgetPtr<KontrolkaObiektu> Ptr;

		KontrolkaObiektu();
		KontrolkaObiektu(const KontrolkaObiektu&);
		virtual ~KontrolkaObiektu() = default;
		bool ustawDane(const SpEx::ObiektInfo& obj, const SpEx::Planeta& planeta);
		const STyp::Identyfikator& pobierzIdObiektu() const;
		void ustawShader(sf::Shader* shader = nullptr);

		void setTransparency(unsigned char transparency);
		void setSize(float width, float hight);
		bool load(const std::string& configFileFilename);
		virtual KontrolkaObiektu* clone();
		const std::string& getLoadedConfigFile() const;
		virtual bool setProperty(std::string property, const std::string& value);
		virtual bool getProperty(std::string property, std::string& value) const;
		virtual std::list< std::pair<std::string, std::string> > getPropertyList() const;
	protected:

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

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

		sf::Rect<float> pozycjonujLabel(Label::Ptr, const sf::Rect<float>&, float width, float height, WYROWNANIE_HORYZONTALNE horyzontalne, WYROWNANIE_WERTYKALNE wertykalne);
		virtual void initialize(Container *const container);

		std::string m_LoadedConfigFile;

		Texture background_;
		STyp::Identyfikator idObiektu_;
		Picture::Ptr picture_;
		Label::Ptr nazwa_;
		Label::Ptr tresc_;
		Button::Ptr rozbuduj_;
		Button::Ptr zniszcz_;
		Label::Ptr czasRozbudowy_;
		Label::Ptr czasZburzenia_;
		sf::Shader* shader_ = nullptr;
		
		sf::Vector2f size_;
		sf::Rect<float> pictureRect_;
		sf::Rect<float> titleRect_;
		sf::Rect<float> describeRect_;
		sf::Rect<float> buttonRozbudujRect_;
		sf::Rect<float> buttonZniszczRect_;
		sf::Rect<float> czasRozbudowyRect_;
		sf::Rect<float> czasZburzeniaRect_;

		WYROWNANIE_WERTYKALNE czasRozbudowyWyrownanieWertykalne_ = MIDDLE;
		WYROWNANIE_HORYZONTALNE czasRozbudowyWyrownanieHoryzontalne_ = LEFT;

		WYROWNANIE_WERTYKALNE czasZburzeniaWyrownanieWertykalne_ = MIDDLE;
		WYROWNANIE_HORYZONTALNE czasZburzeniaWyrownanieHoryzontalne_ = LEFT;

		WYROWNANIE_WERTYKALNE titleWyrownanieWertykalne_ = MIDDLE;
		WYROWNANIE_HORYZONTALNE titleWyrownanieHoryzontalne_ = LEFT;

		WYROWNANIE_WERTYKALNE describeWyrownanieWertykalne_ = MIDDLE;
		WYROWNANIE_HORYZONTALNE describeWyrownanieHoryzontalne_ = LEFT;

		bool constSize_ = false;
		bool propotional_ = true;

		int idZdarzeniaBudowy_ = 0;
		int idZdarzeniaBurzenia_ = 0;
		int idZdarzeniaKlikniecia_ = 0;

	};
};
