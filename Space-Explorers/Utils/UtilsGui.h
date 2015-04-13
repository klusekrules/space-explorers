#pragma once
#include "Kontroler\MaszynaStanow\MaszynaStanow.h"
#include <TGUI\TGUI.hpp>
#include "Widok\Tgui\LogListGui.h"

namespace SpEx{

	/**
	* \brief Klasa z przydatnymi metodami.
	*
	* Klasa zawiera kilka przydatnych metod dla interfejsu graficznego, wykorzystywanych w aplikacji.
	* \author Daniel Wojdak
	* \version 1
	* \date 08-07-2014
	*/
	class UtilsGui
	{
	public:
		/**
		* \brief Metoda pobiera wid�et.
		*
		* Metoda pobiera wid�et z aktywnego ekranu aplikacji.
		* \param[in] nazwa - Nazwa wid�etu.
		* \return Wska�nik do wid�etu.
		* \author Daniel Wojdak
		* \version 1
		* \date 08-07-2014
		*/
		template<class T>
		static typename T::Ptr PobierzWidzetZAktywnegoEkranu(const char * nazwa){
			auto oknoGry = SpEx::MaszynaStanow::pobierzInstancje().pobierzOknoGry();
			if (oknoGry)
				return oknoGry->pobierzStosEkranow().back()->pobierzGUI().get<T>(nazwa);
			return nullptr;
		}

		/**
		* \brief Metoda pobiera wid�et.
		*
		* Metoda pobiera wid�et z ekranu  o podanym numerze.
		* \param[in] id - Identyfikator ekranu.
		* \param[in] nazwa - Nazwa wid�etu.
		* \return Wska�nik do wid�etu.
		* \author Daniel Wojdak
		* \version 1
		* \date 08-07-2014
		*/
		template<class T>
		static typename T::Ptr PobierzWidzetZWybranegoEkranu(int id, const char * nazwa){
			auto oknoGry = SpEx::MaszynaStanow::pobierzInstancje().pobierzOknoGry();

			if (oknoGry){
				auto ekran = oknoGry->pobierzEkran(id);
				if (ekran)
					return ekran->pobierzGUI().get<T>(nazwa);
			}
			
			return T::Ptr(nullptr);
		}

		/**
		* \brief Metoda wy�wietla komunikat log�w.
		*
		* Metoda wy�wietla komunikat log�w w ustawionym oknie komunikat�w.
		* \param[in] typ - Typ komunikatu.
		* \param[in] komunikat - Tre�� komunikatu.
		* \author Daniel Wojdak
		* \version 1
		* \date 08-07-2014
		* \note Metoda zostanie usuni�ta. Funkcjonalno�� b�dzie przeniesiona.
		*/
		static void wyswietlWiadomoscWGUI(unsigned int typ, const std::string& komunikat);


		/**
		* \brief Metoda pod��czaj�ca zdarzenie do wid�etu.
		*
		* Metoda ��czy wid�et i zdarzenie.
		* \param[inout] widzet - Wska�nik na wid�et.
		* \param[in] zdarzenie - Identyfikator zdarzenia.
		* \param[in] numer - Dodatkowy numer pomocniczy.
		* \param[in] akcja - Numer akcji wid�eta.
		* \author Daniel Wojdak
		* \version 1
		* \date 08-07-2014
		*/
		static void bindCallbackEvent(const tgui::Widget::Ptr widzet, unsigned int zdarzenie, unsigned int numer, unsigned int akcja);

	private:

		/**
		* \brief Metoda kolejkuj�ca zdarzenie.
		*
		* Metoda kolejkuje zdarzenie w stosie zdarze�.
		* \param[in] callback - Dok�adniejszy opis zdarzenia.
		* \param[in] idZdarzenia - Identyfikator zdarzenia.
		* \param[in] numer - Dodatkowy numer pomocniczy.
		* \author Daniel Wojdak
		* \version 1
		* \date 08-07-2014
		*/
		static void callback(const tgui::Callback& callback, unsigned int idZdarzenia, unsigned int numer);
	};
};
