#pragma once
#include "NonMoveable.h"
#include "NonCopyable.h"
#include "Logger\Log.h"
#include <map>

namespace SpEx{
	/**
	* \brief Klasa przechowuj¹ca ustawienia
	*
	* Klasa s³u¿aca do wczytywania, przechowywyania, zarz¹dzania i zapisywania ustawieñ aplikacji.
	* \author Daniel Wojdak
	* \version 3
	* \date 20-10-2014
	*/
	class NARZEDZIA_API UstawieniaAplikacji :
		virtual public SLog::LoggerInterface,
		public se::NonCopyable,
		public se::NonMoveable
	{
	public:
		/**
		* \brief Konstruktor.
		*
		* Domyœlny konstruktor obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 01-07-2014
		*/
		UstawieniaAplikacji() = default;

		/**
		* \brief Destruktor.
		*
		* Domyœlny destruktor obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 01-07-2014
		*/
		virtual ~UstawieniaAplikacji() = default;

		/**
		* \brief Metoda wczytuj¹ca dane z pliku.
		*
		* Metoda wczytuj¹ca ustawienia w pliku, którego adres jest podany w parametrze.
		* \param[in] plik - Adres pliku.
		* \return Zwracana jest wartoœæ true, je¿eli wszystko siê powiedzie. Zwracana jest wartoœc false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 01-07-2014
		*/
		bool zaladuj(const std::string& plik);

		const std::string& operator[](const std::string& nazwa) const;

		std::string& operator[](const std::string& nazwa);

		/**
		* Metoda generuj¹ca opis klasy w postaci ci¹gu znaków.
		* \return Napis zwieraj¹cy opis klasy.
		* \author Daniel Wojdak
		* \version 1
		* \date 20-10-2014
		*/
		std::string napis() const override;
		
	private:
		mutable std::map<std::string, std::string> opcje_;

	};
};
