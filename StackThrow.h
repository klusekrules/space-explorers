#pragma once
#include "Parser\XmlBO.h"

namespace SpEx{
	/**
	* \brief Klasa traitowa.
	*
	* Klasa definiuje specjalne zachowanie w przypadku wyst¹pienia b³êdu w metodach pomocniczych parsera.
	* \author Daniel Wojdak
	* \version 1
	* \date 08-07-2014
	*/
	class STACKTHROW {
	public:
		/**
		* \brief Metoda generuj¹ca wyj¹tek.
		*
		* Metoda generuj¹ca wyj¹tek z opisem b³êdu wêz³a.
		* \param[in] element - B³êdny wêze³.
		* \param[in] nazwaWezla - Nazwa szukanego wêz³a.
		* \return Nie u¿ywane.
		* \author Daniel Wojdak
		* \version 1
		* \date 08-07-2014
		*/
		static XmlBO::ElementWezla bladWezla(XmlBO::ElementWezla element, const std::string& nazwaWezla);

		/**
		* \brief Metoda generuj¹ca wyj¹tek.
		*
		* Metoda generuj¹ca wyj¹tek z opisem b³êdu atrybutu.
		* \param[in] element - B³êdny wêze³.
		* \param[in] nazwaAtrybutu - Nazwa szukanego atrybutu.
		* \return Nie u¿ywane.
		* \author Daniel Wojdak
		* \version 1
		* \date 08-07-2014
		*/
		static bool bladAtrybutu(XmlBO::ElementWezla element, const std::string& nazwaAtrybutu);

	};

}