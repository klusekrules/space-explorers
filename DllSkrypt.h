#pragma once
#include <Windows.h>
#include "Skrypt.h"
#include <memory>
#include "Parser\XmlBO.h"

#define XML_ATRYBUT_TYP_SKRYPT_DLL "dll"
namespace SpEx{

	/**
	* \brief Klasa implementuj�ca interfejs klasy Skrypt dla plik�w dll.
	*
	* Klasa implementuje metody dla plik�w dll.
	* \author Daniel Wojdak
	* \version 1
	* \date 09-07-2014
	*/
	class DllSkrypt
		: public Skrypt
	{
		friend class FabrykaSkryptow;
		friend class std::_Ref_count_obj<DllSkrypt>;
	public:

		/**
		* \brief Metoda rejestruj�ca klas� DllSkrypt w fabryce skryptu.
		*
		* Metoda rejestruje klas� DllSkrypt w fabryce skrypt�w podajen w parametrze metody.
		* \param[in] fabryka - Referencja do fabryki skrypt�w.
		* \return Zwracana jest warto�c true, je�eli operacja s� powiedzie lub false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		static bool Rejestruj(FabrykaSkryptow &fabryka);

		/**
		* \brief Metoda �aduj�ca skrypt.
		*
		* Metoda s�u��ca do ��dowania skryptu.
		* \param[in] lokalizacja - Napis lokalizuj�cy �r�d�o skryptu.
		* \return Zwracana jest warto�� true, je�eli uda si� za�adowa� skrypt lub false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		bool zaladuj(const std::string& lokalizacja) override;

		/**
		* \brief Metoda wykonuj�ca skrypt.
		*
		* Metoda s�u��ca do wykonywania skryptu.
		* \param[in] metoda - Nazwa metody.
		* \return Zwracana jest warto�� true, je�eli uda si� wykona� skrypt lub false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		bool wykonaj(const std::string& metoda = std::string()) override;

		/**
		* \brief Destruktor.
		*
		* Destruktor.
		*/
		virtual ~DllSkrypt();
	private:

		/**
		* \brief Metoda tworz�ca pusty obiekt.
		*
		* Metoda metoda tworzy pusty obiekt klasy DllSkrypt.
		* \param[in] wezel - Parametr nie u�ywany.
		* \return Zwracany jest wska�nik na nowo utworzony obiekt.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		static std::shared_ptr<Skrypt> Tworz(XmlBO::ElementWezla wezel);

		/**
		* \brief Konstruktor.
		*
		* Konstruktor.
		* \param[in] lokalizacja - Napis lokalizuj�cy �r�d�o skryptu.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		DllSkrypt(const std::string& lokalizacja = std::string());

		/**
		* \brief Metoda wczytuj�ca dane skryptu lua.
		*
		* Metoda wczytuje dane skryptu do pami�ciu z lokalizacji podanej w atrybucie plik_.
		* \return Zwracana jest warto�� true, je�eli uda si� za�adowa� skrypt lub false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		bool odczytaj();


		std::string plik_; /// Lokalizacja pliku dll.
		HMODULE handle_; /// Uchwyt do wczytanego modu�u dll.
	};
};
