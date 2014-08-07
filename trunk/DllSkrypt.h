#pragma once
#include <Windows.h>
#include "DllModule.h"
#include <memory>
#include "Parser\XmlBO.h"
#include "Skrypt.h"

#define XML_ATRYBUT_TYP_SKRYPT_DLL "dll"
namespace SpEx{

	/**
	* \brief Klasa implementuj�ca interfejs klasy Skrypt dla plik�w dll.
	*
	* Klasa implementuje metody dla plik�w dll.
	* \author Daniel Wojdak
	* \version 3
	* \date 07-08-2014
	*/
	class DllSkrypt
		: public Skrypt
	{
		friend class Fabrykator;
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
		static bool Rejestruj(Fabrykator &fabryka);

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
		* \brief Domy�lny destruktor.
		*
		* Domy�lny destruktor.
		*/
		virtual ~DllSkrypt() = default;

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
		* \param[in] ptr - Modu� dll.
		* \author Daniel Wojdak
		* \version 2
		* \date 07-08-2014
		*/
		DllSkrypt(DllModule::SharedPtr ptr);

		DllModule::SharedPtr modul_; /// Wska�nik na obiekt z uchwytem do modu�u dll.  

	};
};
