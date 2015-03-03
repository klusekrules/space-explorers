#pragma once
#include "lua.hpp"
#include <string>
#include <memory>
#include "ZarzadcaZasobow.h"

#define XML_ATRYBUT_TYP_ZASOBU_LUA "lua"

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
		* \brief Metoda rejestruj�ca klas� LuaState w zarz�dcy zasob�w.
		*
		* Metoda rejestruje klas� LuaState w zarz�dcy zasob�w podanym w parametrze metody.
		* \param[in] fabryka - Referencja do zarz�dcy zasob�w.
		* \return Zwracana jest warto�c true, je�eli operacja s� powiedzie lub false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 06-08-2014
		*/
		static bool Rejestruj(ZarzadcaZasobow &fabryka);
		
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


		/**
		* \brief Metoda tworz�ca obiekt.
		*
		* Metoda tworzy obiekt na podstawie parametr�w.
		* \param[in] parametr - Adres do pliku.
		* \param[in] cache - Informacje czy zas�b jest przechowywany.
		* \return Zwracana jest wska�nik do zasobu.
		* \author Daniel Wojdak
		* \version 1
		* \date 05-08-2014
		*/
		static Zasob::SharedPtr Tworz(const ZarzadcaZasobow::Parametr& parametr, bool cache);

		std::string plik_; /// Lokalizacja skryptu.
		lua_State *L; /// Wska�nik na obiekt opisuj�cy stan skryptu.
	};
};

