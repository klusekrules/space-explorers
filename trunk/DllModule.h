#pragma once
#include <Windows.h>
#include <string>
#include <memory>
#include "ZarzadcaZasobow.h"

#define XML_ATRYBUT_TYP_ZASOBU_DLL "dll"
namespace SpEx {

	/**
	* \brief Klasa przechowuj¹ca uchwyt do modu³u dll.
	*
	* Klasa przechowuje uchwyt do modu³u dll. Udostêpnia metody pozwalaj¹ce na dostêp do modu³u dll.
	* \author Daniel Wojdak
	* \version 1
	* \date 07-08-2014
	*/
	class DllModule
		: public Zasob
	{
	public:
		friend class std::_Ref_count_obj<DllModule>;
		static const std::string NazwaTypu_;
		typedef std::shared_ptr<DllModule> SharedPtr; /// Silny wskaŸnik na klasê.
		typedef std::weak_ptr<DllModule> WeakPtr; /// S³aby wskaŸnik na klasê.


		/**
		* \brief Metoda tworz¹ca obiekt.
		*
		* Metoda tworzy obiekt na podstawie parametrów.
		* \param[in] parametr - Adres do pliku.
		* \param[in] cache - Informacje czy zasób jest przechowywany.
		* \return Zwracana jest wskaŸnik do zasobu.
		* \author Daniel Wojdak
		* \version 1
		* \date 07-08-2014
		*/
		static Zasob::SharedPtr Tworz(const ZarzadcaZasobow::Parametr& parametr, bool cache);
		
		/**
		* \brief Destruktor.
		*
		* Destruktor.
		*/
		virtual ~DllModule();

		/**
		* \brief Metoda inicjalizuj¹ca obiekt.
		*
		* Metoda inicjalizuje obiekt.
		* \return Zwraca wartoœæ true je¿eli zostanie zainicjalizowany poprawnie. Zwraca wartoœc false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 07-08-2014
		*/
		bool inicjalizuj() override;

		/**
		* \brief Operator zwracaj¹cy uchwyt modu³u dll.
		*
		* Operator zwraca uchwyt modu³u dll.
		* \return Uchwyt modu³u dll.
		* \author Daniel Wojdak
		* \version 1
		* \date 07-08-2014
		*/
		inline HMODULE operator()() const{
			return handle_;
		}

		/**
		* \brief Metoda zwracaj¹ca adres pliku.
		*
		* Metoda zwraca adres pliku dll.
		* \return Adres pliku dll.
		* \author Daniel Wojdak
		* \version 1
		* \date 07-08-2014
		*/
		inline const std::string& pobierzPlik() const{
			return plik_;
		}

	private:

		/**
		* \brief Konstruktor.
		*
		* Konstruktor.
		* \param[in] plik - Adres pliku, który ma zostaæ wczytany.
		* \author Daniel Wojdak
		* \version 1
		* \date 07-08-2014
		*/
		DllModule(const std::string& plik);

		
		std::string plik_; /// Lokalizacja pliku dll.
		HMODULE handle_; /// Uchwyt do wczytanego modu³u dll.
	};
};
