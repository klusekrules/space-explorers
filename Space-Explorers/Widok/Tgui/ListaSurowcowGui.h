#pragma once
#include <TGUI\TGUI.hpp>
#include <memory>
#include <mutex>
#include <unordered_map>
#include "Model\ObiektInfo.h"
#include "SurowiecGui.h"
namespace tgui{

	/**
	* \brief Klasa listy kontrolek surowców.
	*
	* Klasa reprezentuje listê kontrolek surowców. Wyœwietla listê surowców dostênych na planecie.
	* \warning Uwaga!!! Klasa przeznaczona do refaktoryzacji. Przesuniêcie refaktoryzacji do czasu migracji do TGUI v7.
	* \author Daniel Wojdak
	* \version 2
	* \date 01-10-2014
	*/
	class ListaSurowcowGui :
		public Widget
	{
	public:
				
		/**
		* \brief Domyœlny konstruktor.
		*
		* Domyœlny konstruktor.
		*/
		ListaSurowcowGui() = default;

		/**
		* \brief Konstruktor kopiuj¹cy.
		*
		* Konstruktor kopiuj¹cy.
		* \param[in] zrodlowy - Obiekt Ÿród³owy.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-10-2014
		*/
		ListaSurowcowGui(const ListaSurowcowGui& zrodlowy);
		
		/**
		* \brief Domyœlny destruktor.
		*
		* Domyœlny destruktor.
		*/
		virtual ~ListaSurowcowGui() = default;

		/**
		* \brief Metoda odœwiezaj¹ca dane kontrolek.
		*
		* Metoda uaktualnia dane reprezentowane przez kontrolkê.
		* \param[in] planeta - Planeta z której s¹ pobierane dane.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-10-2014
		*/
		void aktualizacjaDanych(const SpEx::Planeta& planeta);

		
		/**
		* \brief Metoda zwracaj¹ca adres pliku konfiguracynego.
		*
		* Metoda zwraca adres pliku konfiguracyjnego, z którego zosta³y zaczytane parametry kontrolki.
		* \return Adres pliku konfiguracyjnego.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-10-2014
		*/
		const std::string& getLoadedConfigFile() const;
		
	protected:

		/**
		* \brief Metoda rysuj¹ca kontrolkê.
		*
		* Metoda rysuje kontrolkê.
		* \param[in] target - kontekst na którym ma byæ rysowana kontrolka.
		* \param[in] states - dodatkowy stan kontekstu rysowania kontrolki.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-10-2014
		*/
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		
		/**
		* \brief Metoda odœwie¿aj¹ca pozycjê kontrolek.
		*
		* Metoda odœwie¿a pozycjê kontrolek.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-10-2014
		*/
		void odswiezPozycje();

		mutable std::mutex zmianaDanych_; /// Muteks dostêpu do modyfikacji danych kontrolek.
		std::string plikKonfiguracyjny_ = ""; /// Adres pliku konfiguracyjnego.
		SurowiecGui::Ptr szablonKontrolki_; /// WskaŸnik na szablon kontrolki obiektu.
		std::vector<SurowiecGui::Ptr> kontrolki_; /// Kontener z kontrolkami obiektów.

	};
};
