#pragma once
#include <Windows.h>
#include "DllModule.h"
#include <memory>
#include "Parser\XmlBO.h"
#include "Skrypt.h"

#define XML_ATRYBUT_TYP_SKRYPT_DLL "dll"
namespace SpEx{

	/**
	* \brief Klasa implementuj¹ca interfejs klasy Skrypt dla plików dll.
	*
	* Klasa implementuje metody dla plików dll.
	* \author Daniel Wojdak
	* \version 3
	* \date 07-08-2014
	*/
	class DllSkrypt
		: public Skrypt
	{
		friend class Fabrykator;
		friend class std::_Ref_count_obj<DllSkrypt>;
	public:

		/**
		* \brief Metoda rejestruj¹ca klasê DllSkrypt w fabryce skryptu.
		*
		* Metoda rejestruje klasê DllSkrypt w fabryce skryptów podajen w parametrze metody.
		* \param[in] fabryka - Referencja do fabryki skryptów.
		* \return Zwracana jest wartoœc true, je¿eli operacja sê powiedzie lub false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		static bool Rejestruj(Fabrykator &fabryka);

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
		* \brief Domyœlny destruktor.
		*
		* Domyœlny destruktor.
		*/
		virtual ~DllSkrypt() = default;

	private:

		/**
		* \brief Metoda tworz¹ca pusty obiekt.
		*
		* Metoda metoda tworzy pusty obiekt klasy DllSkrypt.
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
		* \param[in] ptr - Modu³ dll.
		* \author Daniel Wojdak
		* \version 2
		* \date 07-08-2014
		*/
		DllSkrypt(DllModule::SharedPtr ptr);

		DllModule::SharedPtr modul_; /// WskaŸnik na obiekt z uchwytem do modu³u dll.  

	};
};
