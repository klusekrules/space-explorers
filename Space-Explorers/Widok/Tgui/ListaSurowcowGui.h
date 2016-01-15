#pragma once
#include <TGUI\TGUI.hpp>
#include <memory>
#include <mutex>
#include <unordered_map>
#include "Model\ObiektInfo.h"
#include "SurowiecGui.h"
namespace tgui{

	/**
	* \brief Klasa listy kontrolek surowc�w.
	*
	* Klasa reprezentuje list� kontrolek surowc�w. Wy�wietla list� surowc�w dost�nych na planecie.
	* \warning Uwaga!!! Klasa przeznaczona do refaktoryzacji. Przesuni�cie refaktoryzacji do czasu migracji do TGUI v7.
	* \author Daniel Wojdak
	* \version 2
	* \date 01-10-2014
	*/
	class ListaSurowcowGui :
		public Widget
	{
	public:
				
		/**
		* \brief Domy�lny konstruktor.
		*
		* Domy�lny konstruktor.
		*/
		ListaSurowcowGui() = default;

		/**
		* \brief Konstruktor kopiuj�cy.
		*
		* Konstruktor kopiuj�cy.
		* \param[in] zrodlowy - Obiekt �r�d�owy.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-10-2014
		*/
		ListaSurowcowGui(const ListaSurowcowGui& zrodlowy);
		
		/**
		* \brief Domy�lny destruktor.
		*
		* Domy�lny destruktor.
		*/
		virtual ~ListaSurowcowGui() = default;

		/**
		* \brief Metoda od�wiezaj�ca dane kontrolek.
		*
		* Metoda uaktualnia dane reprezentowane przez kontrolk�.
		* \param[in] planeta - Planeta z kt�rej s� pobierane dane.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-10-2014
		*/
		void aktualizacjaDanych(const SpEx::Planeta& planeta);

		
		/**
		* \brief Metoda zwracaj�ca adres pliku konfiguracynego.
		*
		* Metoda zwraca adres pliku konfiguracyjnego, z kt�rego zosta�y zaczytane parametry kontrolki.
		* \return Adres pliku konfiguracyjnego.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-10-2014
		*/
		const std::string& getLoadedConfigFile() const;
		
	protected:

		/**
		* \brief Metoda rysuj�ca kontrolk�.
		*
		* Metoda rysuje kontrolk�.
		* \param[in] target - kontekst na kt�rym ma by� rysowana kontrolka.
		* \param[in] states - dodatkowy stan kontekstu rysowania kontrolki.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-10-2014
		*/
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		
		/**
		* \brief Metoda od�wie�aj�ca pozycj� kontrolek.
		*
		* Metoda od�wie�a pozycj� kontrolek.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-10-2014
		*/
		void odswiezPozycje();

		mutable std::mutex zmianaDanych_; /// Muteks dost�pu do modyfikacji danych kontrolek.
		std::string plikKonfiguracyjny_ = ""; /// Adres pliku konfiguracyjnego.
		SurowiecGui::Ptr szablonKontrolki_; /// Wska�nik na szablon kontrolki obiektu.
		std::vector<SurowiecGui::Ptr> kontrolki_; /// Kontener z kontrolkami obiekt�w.

	};
};
