#pragma once
#include <Windows.h>
#include <string>
#include <memory>
#include "ZarzadcaZasobow.h"

#define XML_ATRYBUT_TYP_ZASOBU_DLL "dll"
namespace SpEx {

	/**
	* \brief Klasa przechowuj�ca uchwyt do modu�u dll.
	*
	* Klasa przechowuje uchwyt do modu�u dll. Udost�pnia metody pozwalaj�ce na dost�p do modu�u dll.
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
		typedef std::shared_ptr<DllModule> SharedPtr; /// Silny wska�nik na klas�.
		typedef std::weak_ptr<DllModule> WeakPtr; /// S�aby wska�nik na klas�.


		/**
		* \brief Metoda tworz�ca obiekt.
		*
		* Metoda tworzy obiekt na podstawie parametr�w.
		* \param[in] parametr - Adres do pliku.
		* \param[in] cache - Informacje czy zas�b jest przechowywany.
		* \return Zwracana jest wska�nik do zasobu.
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
		* \brief Metoda inicjalizuj�ca obiekt.
		*
		* Metoda inicjalizuje obiekt.
		* \return Zwraca warto�� true je�eli zostanie zainicjalizowany poprawnie. Zwraca warto�c false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 07-08-2014
		*/
		bool inicjalizuj() override;

		/**
		* \brief Operator zwracaj�cy uchwyt modu�u dll.
		*
		* Operator zwraca uchwyt modu�u dll.
		* \return Uchwyt modu�u dll.
		* \author Daniel Wojdak
		* \version 1
		* \date 07-08-2014
		*/
		inline HMODULE operator()() const{
			return handle_;
		}

		/**
		* \brief Metoda zwracaj�ca adres pliku.
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
		* \param[in] plik - Adres pliku, kt�ry ma zosta� wczytany.
		* \author Daniel Wojdak
		* \version 1
		* \date 07-08-2014
		*/
		DllModule(const std::string& plik);

		
		std::string plik_; /// Lokalizacja pliku dll.
		HMODULE handle_; /// Uchwyt do wczytanego modu�u dll.
	};
};
