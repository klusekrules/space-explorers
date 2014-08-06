#pragma once
#include "Zmiana\ZmianaFabryka.h"
#include "Skrypt.h"

namespace SpEx{

	/**
	* \brief Klasa przechowuj¹ca obiekty fabryk.
	*
	* Klasa przechowuje obiekty fabryk.
	* \author Daniel Wojdak
	* \version 3
	* \date 06-08-2014
	*/
	class Fabrykator
	{
	public:
		typedef STyp::Tekst IdentyfikatorSkryptu; /// Typ skryptu.
		typedef std::shared_ptr<Skrypt>(*KreatorSkryptu)(XmlBO::ElementWezla wezel); /// Nag³ówek metody tworz¹cej skrypt.
		typedef bool(*RejestrujSkrypt)(Fabrykator& fabryka, SLog::Log& logger); /// Nag³ówek metody rejestruj¹cej skrypt w fabryce.

		/**
		* \brief Konstruktor.
		*
		* Konstruktor.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2014
		*/
		Fabrykator();

		/**
		* \brief Domyœlny destruktor.
		*
		* Domyœlny destruktor.
		*/
		~Fabrykator() = default;

		/**
		* \brief Metoda tworzy skrypt.
		*
		* Metoda tworzy obiekt skryptu na podstawie danych przekazanych w wêŸle przez parametr.
		* \param[in] wezel - Wêze³ opisuj¹cy skrypt.
		* \return Zwracany jest wskaŸnik do skryptu, je¿eli operacja siê powiedzie lub nullptr w przypadku b³êdu.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2014
		*/
		std::shared_ptr<Skrypt> TworzSkrypt(XmlBO::ElementWezla wezel) const;

		/**
		* \brief Metoda tworzy skrypt.
		*
		* Metoda tworzy obiekt skryptu na podstawie danych przekazanych przez parametry.
		* \param[in] identyfikator - Identyfikator typu skryptu.
		* \param[in] wezel - Wêze³ opisuj¹cy skrypt.
		* \return Zwracany jest wskaŸnik do skryptu, je¿eli operacja siê powiedzie lub nullptr w przypadku b³êdu.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2014
		*/
		std::shared_ptr<Skrypt> TworzSkrypt(const IdentyfikatorSkryptu& identyfikator, XmlBO::ElementWezla wezel) const;

		/**
		* \brief Metoda tworzy skrypt.
		*
		* Metoda tworzy obiekt skryptu na podstawie danych przekazanych przez parametry.
		* \param[in] plik - Adres pliku, który ma byæ wczytany jako skrypt.
		* \return Zwracany jest wskaŸnik do skryptu, je¿eli operacja siê powiedzie lub nullptr w przypadku b³êdu.
		* \author Daniel Wojdak
		* \version 1
		* \date 06-08-2014
		*/
		std::shared_ptr<Skrypt> TworzSkrypt(const std::string& plik) const;

		/**
		* \brief Metoda tworz¹ca zmianê.
		*
		* Metoda tworzy obiekt zmiany na podstawie danych przekazanych przez parametry.
		* \param[in] wezel - Wêze³ opisuj¹cy zmianê.
		* \return Zwracany jest wskaŸnik do skryptu, je¿eli operacja siê powiedzie lub nullptr w przypadku b³êdu.
		* \throw Metoda generuje wyj¹tek, je¿eli wêze³ nie zawiera odpowiedniego atrybutu.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2014
		*/
		std::shared_ptr<SZmi::ZmianaInterfejs> TworzZmiane(XmlBO::ElementWezla wezel) const;

		/**
		* \brief Metoda pobieraj¹ca fabryke zmian.
		*
		* Meoda pobiera raferencje do fabryki zmian.
		* \return Referencja do fabryki zmian.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2014
		*/
		SZmi::ZmianaFabryka& pobierzFabrykeZmian();

		/**
		* \brief Metoda rejestruj¹ca typ skryptu.
		*
		* Metoda zapisuje do kontenera metodê tworz¹c¹ skrypt o podany typie.
		* \param[in] identyfikator - Identyfikator skryptu.
		* \param[in] funkcja - Metoda tworz¹ca.
		* \return Zwracana jest wartoœæ true, je¿eli uda siê zarejestrowaæ metode lub false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 06-08-2014
		*/
		bool rejestracjaSkryptu(const IdentyfikatorSkryptu& identyfikator, KreatorSkryptu funkcja);

	private:
		typedef std::map<IdentyfikatorSkryptu, KreatorSkryptu> ScriptCallbacks; /// Typ kontenera przechowuj¹cego metody tworz¹ce instancje skryptów.

		ScriptCallbacks callbacks_; /// Kontener przechowuj¹cy metody tworz¹ce instancje skryptów.

		SZmi::ZmianaFabryka fabrykaZmian_; /// Instancja fabryki zmian.
	};
};
