#pragma once
#include <TGUI\TGUI.hpp>
#include "PomocniczeTypyTGUI.h"
#include "Model\ObiektInfo.h"
#include "BazowyRenderer.h"

namespace tgui{

	void convertFromBorderToRect(const Borders&, sf::Rect<float>&);
	void normalizujRect(sf::Rect<float>&, float leftWidth, float topHeight);

	class KontrolkaObiektuRenderer;

	/**
	* \brief Klasa kontrolki obiektu.
	*
	* Klasa reprezentuje kontrolkê obiektu. Wyœwietla aktualne dane o obiekcie znajduj¹cym sie na planecie. Pozwala na rozbudowe.
	* \warning Uwaga!!! Klasa przeznaczona do refaktoryzacji. Przesuniêcie refaktoryzacji do czasu migracji do TGUI v7.
	* \author Daniel Wojdak
	* \version 2
	* \date 30-09-2014
	*/
	class KontrolkaObiektu :
		public BazowyWidzet
	{
	public:
		typedef std::shared_ptr<KontrolkaObiektu> Ptr; ///< Shared widget pointer
		typedef std::shared_ptr<const KontrolkaObiektu> ConstPtr; ///< Shared constant widget pointer

		/**
		* \brief Konstruktor obiektu.
		*
		* Konstruktor bezparametrowy.
		* \author Daniel Wojdak
		* \version 3
		* \date 27-11-2015
		*/
		KontrolkaObiektu();

		/**
		* \brief Konstruktor kopiuj¹cy.
		*
		* Konstruktor kopiuj¹cy.
		* \param[in] copy - Obiekt Ÿród³owy.
		* \author Daniel Wojdak
		* \version 3
		* \date 27-11-2015
		*/
		KontrolkaObiektu(const KontrolkaObiektu& copy);
		
		KontrolkaObiektu& operator= (const KontrolkaObiektu& right);

		/**
		* \brief Domyœlny destruktor.
		*
		* Domyœlny destruktor.
		*/
		virtual ~KontrolkaObiektu() = default;

		/**
		* \brief Metoda ustawiaj¹ca dane obiektu.
		*
		* Metoda ustawia dane wyœwietlane w obiekcie.
		* \param[in] obiekt - Obiekt opisuj¹cy.
		* \param[in] planeta - Planeta kontekstu obiektu.
		* \return Zwracana jest wartoœc true je¿eli uda³o siê wczytaæ dane. Zwracana jest wartoœæ false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 2
		* \date 30-09-2014
		*/
		bool ustawDane(const SpEx::ObiektInfo& obiekt, const SpEx::Planeta& planeta);

		/**
		* \brief Metoda pobieraj¹ca identyfikator obiektu.
		*
		* Metoda zwraca identyfikator obiektu, który aktualnie jest wyœwietlany.
		* \return Identyfikator obiektu aktualnie wyœwietlanego.
		* \author Daniel Wojdak
		* \version 2
		* \date 30-09-2014
		*/
		const STyp::Identyfikator& pobierzIdObiektu() const;
		int pobierzIdentyfikatorZdarzeniaBudowy() const {
			return idZdarzeniaBudowy_;
		}
		int pobierzIdentyfikatorZdarzeniaBurzenia() const {
			return idZdarzeniaBurzenia_;
		}
		int pobierzIdentyfikatorZdarzeniaKlikniecia() const {
			return idZdarzeniaKlikniecia_;
		}

		bool mouseOnWidget(float x, float y) override;
		
		std::shared_ptr<KontrolkaObiektuRenderer> getRenderer() const {
			return std::static_pointer_cast<KontrolkaObiektuRenderer>(m_renderer);
		}

		Widget::Ptr clone() const override {
			return std::make_shared<KontrolkaObiektu>(*this);
		}

	protected:
		
		void reload(const std::string& primary = "", const std::string& secondary = "", bool force = false) override;

	private:
		
		STyp::Identyfikator idObiektu_ = -1; /// Identyfikator obiektu gry wyœiwetlanego w kontrolce.
		Picture::Ptr obraz_; /// Obraz obiektu gry.
		Label::Ptr nazwa_; /// Nazwa obiektu gry.
		Label::Ptr tresc_; /// Opis obiektu gry.
		Button::Ptr rozbuduj_; /// Przycisk rozbudowy obiektu gry.
		Button::Ptr zniszcz_; /// Przycisk burzenia obiektu gry.
		Label::Ptr czasRozbudowy_; /// Czas rozbudowy obiektu gry.
		Label::Ptr czasZburzenia_; /// Czas burzenia obiektu gry.

		int idZdarzeniaBudowy_ = 0; /// Numer zdarzenia klikniêcia na przycisk budowy obiektu gry.
		int idZdarzeniaBurzenia_ = 0; /// Numer zdarzenia klikniêcia na przycisk burzenia obiektu gry.
		int idZdarzeniaKlikniecia_ = 0; /// Numer zdarzenia klikniêcia na obrazek obiektu gry.
		
		friend class KontrolkaObiektuRenderer;

	};

	
	class KontrolkaObiektuRenderer : public BazowyRenderer
	{
	public:
		using BazowyRenderer::BazowyRenderer;
	private:
		std::shared_ptr<WidgetRenderer> clone(Widget* widget) override;
		KontrolkaObiektuRenderer(const KontrolkaObiektuRenderer&) = default;
		KontrolkaObiektuRenderer& operator=(const KontrolkaObiektuRenderer&) = delete;
	protected:
		friend class KontrolkaObiektu;
	};
};
