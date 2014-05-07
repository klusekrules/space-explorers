#pragma once
#include "stdafx.h"
#include "Stan.h"
namespace SpEx{
	class EkranSzablon :
		public sf::Drawable,
		public sf::Transformable
	{
	public:
		EkranSzablon(XmlBO::ElementWezla wezel);

		virtual ~EkranSzablon(void) = default;

		virtual void uaktualnij(Stan& stan);

		virtual void odbierz(Stan& stan, const sf::Event& zdarzenie);

		virtual void podlacz(sf::RenderWindow&);

		virtual void odlacz(sf::RenderWindow&);

		const STyp::Identyfikator& pobierzId() const;

		tgui::Gui& pobierzGUI();

		virtual void clear();

	protected:

		bool wczytajDaneKontrolki(XmlBO::ElementWezla wezel, tgui::Widget::Ptr kontrolka);

		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		STyp::Identyfikator id_;
		mutable tgui::Gui interfejs_;
	};
};

