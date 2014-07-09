#pragma once
#include "lua.hpp"
#include "Skrypt.h"
#include <memory>
#include "Parser\XmlBO.h"

#define XML_ATRYBUT_TYP_SKRYPT_LUA "lua"

namespace SpEx{

	/**
	* \brief Klasa implementuj¹ca interfejs klasy Skrypt dla lua.
	*
	* Klasa implementuje metody dla skryptów lua.
	* \author Daniel Wojdak
	* \version 1
	* \date 09-07-2014
	*/
	class LuaSkrypt
		: public Skrypt
	{
		friend class FabrykaSkryptow;
		friend class std::_Ref_count_obj<LuaSkrypt>;
	public:
		/**
		* \brief Metoda rejestruj¹ca klasê LuaSkrypt w fabryce skryptu.
		*
		* Metoda rejestruje klasê LuaSkrypt w fabryce skryptów podajen w parametrze metody.
		* \param[in] fabryka - Referencja do fabryki skryptów.
		* \return Zwracana jest wartoœc true, je¿eli operacja sê powiedzie lub false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		static bool Rejestruj(FabrykaSkryptow &fabryka);

		/**
		* \brief Metoda ³aduj¹ca skrypt.
		*
		* Metoda s³u¿¹ca do ³¹dowania skryptu.
		* \param[in] lokalizacja - Napis lokalizuj¹cy Ÿród³o skryptu.
		* \return Zwracana jest wartoœæ true, je¿eli uda siê za³adowaæ skrypt lub false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		bool zaladuj(const std::string& lokalizacja) override;

		/**
		* \brief Metoda wykonuj¹ca skrypt.
		*
		* Metoda s³u¿¹ca do wykonywania skryptu.
		* \param[in] metoda - Nazwa metody.
		* \return Zwracana jest wartoœæ true, je¿eli uda siê wykonaæ skrypt lub false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		bool wykonaj(const std::string& metoda = std::string()) override;

		/**
		* \brief Destruktor.
		*
		* Destruktor.
		*/
		virtual ~LuaSkrypt();

	private:

		/**
		* \brief Metoda tworz¹ca pusty obiekt.
		*
		* Metoda metoda tworzy pusty obiekt klasy LuaSkrypt.
		* \param[in] wezel - Parametr nie u¿ywany.
		* \return Zwracany jest wskaŸnik na nowo utworzony obiekt.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		static std::shared_ptr<Skrypt> Tworz(XmlBO::ElementWezla wezel);

		/**
		* \brief Konstruktor.
		*
		* Konstruktor.
		* \param[in] lokalizacja - Napis lokalizuj¹cy Ÿród³o skryptu.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		LuaSkrypt(const std::string& lokalizacja = std::string());

		/**
		* \brief Metoda wczytuj¹ca dane skryptu lua.
		*
		* Metoda wczytuje dane skryptu do pamiêciu z lokalizacji podanej w atrybucie plik_.
		* \return Zwracana jest wartoœæ true, je¿eli uda siê za³adowaæ skrypt lub false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		bool odczytaj();

		std::string plik_; /// Lokalizacja skryptu.
		lua_State *L; /// WskaŸnik na obiekt opisuj¹cy stan skryptu.
	};
};
