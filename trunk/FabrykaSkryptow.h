#pragma once
#include "NonCopyable.h"
#include "Skrypt.h"
#include "Parser\XmlBO.h"
#include "Logger\Log.h"
#include <map>

#define XML_ATRYBUT_TYP_SKRYPTU "typSkryptu"

namespace SpEx{

	/**
	* \brief Klasa fabryka tworz¹ca instancjê skryptów.
	*
	* Klasa implementuj¹ca wzorzec fabryki, tworz¹ca instancje klas skryptów.
	* \author Daniel Wojdak
	* \version 2
	* \date 06-08-2014
	*/
	class FabrykaSkryptow
		: public se::NonCopyable
	{
	public:
		typedef STyp::Tekst Identyfikator; /// Typ skryptu.
		typedef std::shared_ptr<Skrypt>(*KreatorSkryptu)(XmlBO::ElementWezla wezel); /// Nag³ówek metody tworz¹cej skrypt.
		typedef bool(*RejestrujSkrypt)(FabrykaSkryptow& fabryka, SLog::Log& logger); /// Nag³ówek metody rejestruj¹cej skrypt w fabryce.

		/**
		* \brief Metoda tworz¹ca skrypt.
		*
		* Metoda tworzy instancje skryptu na podstawie wêz³a przekazanego w parametrze.
		* \param[in] wezel - Wêze³ z opisem skryptu.
		* \return WskaŸnik do utworzonego skryptu.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		std::shared_ptr<Skrypt> Tworz(XmlBO::ElementWezla wezel) const;

		/**
		* \brief Metoda tworz¹ca skrypt.
		*
		* Metoda tworzy instancje skryptu na podstawie idenntyfikatora oraz wez³a opisuj¹cego.
		* \param[in] identyfikator - Identyfikator skryptu.
		* \param[in] wezel - Wêze³ z opisem skryptu.
		* \return WskaŸnik do utworzonego skryptu.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		std::shared_ptr<Skrypt> Tworz(const Identyfikator& identyfikator, XmlBO::ElementWezla wezel) const;
		
		/**
		* \brief Metoda tworz¹ca skrypt.
		*
		* Metoda tworzy instancje skryptu na podstawie idenntyfikatora oraz wez³a opisuj¹cego.
		* \param[in] plik - Adres pliku, który ma byæ wczytany jako skrypt.
		* \return WskaŸnik do utworzonego skryptu.
		* \author Daniel Wojdak
		* \version 1
		* \date 06-08-2014
		*/
		std::shared_ptr<Skrypt> Tworz(const std::string& plik) const;

		/**
		* \brief Metoda rejestruj¹ca typ skryptu.
		*
		* Metoda zapisuje do kontenera metodê tworz¹c¹ skrypt o podany typie.
		* \param[in] identyfikator - Identyfikator skryptu.
		* \param[in] funkcja - Metoda tworz¹ca.
		* \return Zwracana jest wartoœæ true, je¿eli uda siê zarejestrowaæ metode lub false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		bool rejestracjaSkryptu(const Identyfikator& identyfikator, KreatorSkryptu funkcja);

		/**
		* \brief Domyœlny konstruktor.
		*
		* Domyœlny konstruktor.
		*/
		FabrykaSkryptow() = default;

		/**
		* \brief Destruktor.
		*
		* Domyœ³ny destruktor.
		*/
		virtual ~FabrykaSkryptow() = default;

	private:

		typedef std::map<Identyfikator, KreatorSkryptu> Callbacks; /// Typ kontenera przechowuj¹cego metody tworz¹ce instancje skryptów.

		Callbacks callbacks_; /// Kontener przechowuj¹cy metody tworz¹ce instancje skryptów.

	};
}
