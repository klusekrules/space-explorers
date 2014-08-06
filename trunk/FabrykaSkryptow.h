#pragma once
#include "NonCopyable.h"
#include "Skrypt.h"
#include "Parser\XmlBO.h"
#include "Logger\Log.h"
#include <map>

#define XML_ATRYBUT_TYP_SKRYPTU "typSkryptu"

namespace SpEx{

	/**
	* \brief Klasa fabryka tworz�ca instancj� skrypt�w.
	*
	* Klasa implementuj�ca wzorzec fabryki, tworz�ca instancje klas skrypt�w.
	* \author Daniel Wojdak
	* \version 2
	* \date 06-08-2014
	*/
	class FabrykaSkryptow
		: public se::NonCopyable
	{
	public:
		typedef STyp::Tekst Identyfikator; /// Typ skryptu.
		typedef std::shared_ptr<Skrypt>(*KreatorSkryptu)(XmlBO::ElementWezla wezel); /// Nag��wek metody tworz�cej skrypt.
		typedef bool(*RejestrujSkrypt)(FabrykaSkryptow& fabryka, SLog::Log& logger); /// Nag��wek metody rejestruj�cej skrypt w fabryce.

		/**
		* \brief Metoda tworz�ca skrypt.
		*
		* Metoda tworzy instancje skryptu na podstawie w�z�a przekazanego w parametrze.
		* \param[in] wezel - W�ze� z opisem skryptu.
		* \return Wska�nik do utworzonego skryptu.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		std::shared_ptr<Skrypt> Tworz(XmlBO::ElementWezla wezel) const;

		/**
		* \brief Metoda tworz�ca skrypt.
		*
		* Metoda tworzy instancje skryptu na podstawie idenntyfikatora oraz wez�a opisuj�cego.
		* \param[in] identyfikator - Identyfikator skryptu.
		* \param[in] wezel - W�ze� z opisem skryptu.
		* \return Wska�nik do utworzonego skryptu.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		std::shared_ptr<Skrypt> Tworz(const Identyfikator& identyfikator, XmlBO::ElementWezla wezel) const;
		
		/**
		* \brief Metoda tworz�ca skrypt.
		*
		* Metoda tworzy instancje skryptu na podstawie idenntyfikatora oraz wez�a opisuj�cego.
		* \param[in] plik - Adres pliku, kt�ry ma by� wczytany jako skrypt.
		* \return Wska�nik do utworzonego skryptu.
		* \author Daniel Wojdak
		* \version 1
		* \date 06-08-2014
		*/
		std::shared_ptr<Skrypt> Tworz(const std::string& plik) const;

		/**
		* \brief Metoda rejestruj�ca typ skryptu.
		*
		* Metoda zapisuje do kontenera metod� tworz�c� skrypt o podany typie.
		* \param[in] identyfikator - Identyfikator skryptu.
		* \param[in] funkcja - Metoda tworz�ca.
		* \return Zwracana jest warto�� true, je�eli uda si� zarejestrowa� metode lub false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		bool rejestracjaSkryptu(const Identyfikator& identyfikator, KreatorSkryptu funkcja);

		/**
		* \brief Domy�lny konstruktor.
		*
		* Domy�lny konstruktor.
		*/
		FabrykaSkryptow() = default;

		/**
		* \brief Destruktor.
		*
		* Domy��ny destruktor.
		*/
		virtual ~FabrykaSkryptow() = default;

	private:

		typedef std::map<Identyfikator, KreatorSkryptu> Callbacks; /// Typ kontenera przechowuj�cego metody tworz�ce instancje skrypt�w.

		Callbacks callbacks_; /// Kontener przechowuj�cy metody tworz�ce instancje skrypt�w.

	};
}
