#pragma once
#include "lua.hpp"
#include "Skrypt.h"
#include "LuaState.h"
#include <memory>
#include "Parser\XmlBO.h"

#define XML_ATRYBUT_TYP_SKRYPT_LUA "lua"

namespace SpEx{

	/**
	* \brief Klasa implementuj�ca interfejs klasy Skrypt dla lua.
	*
	* Klasa implementuje metody dla skrypt�w lua.
	* \author Daniel Wojdak
	* \version 2
	* \date 05-08-2014
	*/
	class LuaSkrypt
		: public Skrypt
	{
		friend class FabrykaSkryptow;
		friend class std::_Ref_count_obj<LuaSkrypt>;
	public:
		/**
		* \brief Metoda rejestruj�ca klas� LuaSkrypt w fabryce skryptu.
		*
		* Metoda rejestruje klas� LuaSkrypt w fabryce skrypt�w podajen w parametrze metody.
		* \param[in] fabryka - Referencja do fabryki skrypt�w.
		* \return Zwracana jest warto�c true, je�eli operacja s� powiedzie lub false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		static bool Rejestruj(FabrykaSkryptow &fabryka);

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
		virtual ~LuaSkrypt() = default;

	private:

		/**
		* \brief Metoda tworz�ca pusty obiekt.
		*
		* Metoda metoda tworzy pusty obiekt klasy LuaSkrypt.
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
		* \param[in] stan - Stan skryptu lua.
		* \author Daniel Wojdak
		* \version 2
		* \date 05-08-2014
		*/
		LuaSkrypt(LuaState::SharedPtr stan);

		LuaState::SharedPtr L; /// Wska�nik na obiekt opisuj�cy stan skryptu.
	};
};
