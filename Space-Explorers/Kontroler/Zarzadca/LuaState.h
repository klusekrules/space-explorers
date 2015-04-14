#pragma once
#include "lua.hpp"
#include <string>
#include <memory>
#include "ZarzadcaZasobow.h"

namespace SpEx{

	/**
	* \brief Klasa przechowuj¹ca stan maszyny skryptów lua.
	*
	* Klasa przechowuje stan maszyny skryptów lua. Udostêpnia metody pozwalaj¹ce na dostêp do stanu maszyny lua.
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
		typedef std::shared_ptr<LuaState> SharedPtr; /// Silny wskaŸnik na klasê.
		typedef std::weak_ptr<LuaState> WeakPtr; /// S³aby wskaŸnik na klasê.

		/**
		* \brief Destruktor.
		*
		* Destruktor.
		*/
		virtual ~LuaState();

		/**
		* \brief Metoda inicjalizuj¹ca obiekt.
		*
		* Metoda inicjalizuje obiekt.
		* \return Zwraca wartoœæ true je¿eli zostanie zainicjalizowany poprawnie. Zwraca wartoœc false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 05-08-2014
		*/
		bool inicjalizuj() override;

		/**
		* \brief Operator zwracaj¹cy wskaŸnik do obiektu stanu maszyny lua.
		*
		* Operator zwraca wskaŸnik do obiektu stanu maszyny lua.
		* \return WskaŸnik do obiektu stanu maszyny lua.
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
		* \param[in] plik - Adres pliku, który ma zostaæ wczytany.
		* \author Daniel Wojdak
		* \version 1
		* \date 05-08-2014
		*/
		LuaState(const std::string& plik);



		std::string plik_; /// Lokalizacja skryptu.
		lua_State *L; /// WskaŸnik na obiekt opisuj¹cy stan skryptu.
	};
};

