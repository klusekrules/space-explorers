#pragma once
#include "lua.hpp"
#include <string>
#include <memory>
#include "ZarzadcaZasobow.h"

namespace SpEx{

	/**
	* \brief Klasa przechowuj�ca stan maszyny skrypt�w lua.
	*
	* Klasa przechowuje stan maszyny skrypt�w lua. Udost�pnia metody pozwalaj�ce na dost�p do stanu maszyny lua.
	* \author Daniel Wojdak
	* \version 2
	* \date 06-08-2014
	*/
	class LuaState
		: public Zasob
	{
	public:
		friend class std::_Ref_count_obj<LuaState>;
		static const std::string NazwaTypu_;
		typedef std::shared_ptr<LuaState> SharedPtr; /// Silny wska�nik na klas�.
		typedef std::weak_ptr<LuaState> WeakPtr; /// S�aby wska�nik na klas�.

		/**
		* \brief Destruktor.
		*
		* Destruktor.
		*/
		virtual ~LuaState();

		/**
		* \brief Metoda inicjalizuj�ca obiekt.
		*
		* Metoda inicjalizuje obiekt.
		* \return Zwraca warto�� true je�eli zostanie zainicjalizowany poprawnie. Zwraca warto�c false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 05-08-2014
		*/
		bool inicjalizuj() override;

		/**
		* \brief Operator zwracaj�cy wska�nik do obiektu stanu maszyny lua.
		*
		* Operator zwraca wska�nik do obiektu stanu maszyny lua.
		* \return Wska�nik do obiektu stanu maszyny lua.
		* \author Daniel Wojdak
		* \version 1
		* \date 06-08-2014
		*/
		inline lua_State* operator()() const{
			return L;
		}

	private:

		/**
		* \brief Konstruktor.
		*
		* Konstruktor.
		* \param[in] plik - Adres pliku, kt�ry ma zosta� wczytany.
		* \author Daniel Wojdak
		* \version 1
		* \date 05-08-2014
		*/
		LuaState(const std::string& plik);



		std::string plik_; /// Lokalizacja skryptu.
		lua_State *L; /// Wska�nik na obiekt opisuj�cy stan skryptu.
	};
};

