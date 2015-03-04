#pragma once
#include "Parser\XmlBO.h"

namespace SpEx{
	/**
	* \brief Klasa traitowa.
	*
	* Klasa definiuje specjalne zachowanie w przypadku wyst�pienia b��du w metodach pomocniczych parsera.
	* \author Daniel Wojdak
	* \version 1
	* \date 08-07-2014
	*/
	class STACKTHROW {
	public:
		/**
		* \brief Metoda generuj�ca wyj�tek.
		*
		* Metoda generuj�ca wyj�tek z opisem b��du w�z�a.
		* \param[in] element - B��dny w�ze�.
		* \param[in] nazwaWezla - Nazwa szukanego w�z�a.
		* \return Nie u�ywane.
		* \author Daniel Wojdak
		* \version 1
		* \date 08-07-2014
		*/
		static XmlBO::ElementWezla bladWezla(XmlBO::ElementWezla element, const std::string& nazwaWezla);

		/**
		* \brief Metoda generuj�ca wyj�tek.
		*
		* Metoda generuj�ca wyj�tek z opisem b��du atrybutu.
		* \param[in] element - B��dny w�ze�.
		* \param[in] nazwaAtrybutu - Nazwa szukanego atrybutu.
		* \return Nie u�ywane.
		* \author Daniel Wojdak
		* \version 1
		* \date 08-07-2014
		*/
		static bool bladAtrybutu(XmlBO::ElementWezla element, const std::string& nazwaAtrybutu);

	};

}