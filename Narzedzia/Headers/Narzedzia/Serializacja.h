#pragma once
#pragma warning( disable : 4290 )
#include "Parser\XmlBO.h"

namespace SpEx{
	/**
	* \brief Klasa abstrakcyjna dodaj¹ca interfejs serializacji.
	*
	* Rozsze¿a interfejs o zapis i odczyt danych z pliku xml.
	* \author Daniel Wojdak
	* \version 1
	* \date 22-07-2013
	*/
	class Serializacja
	{
	public:
		/**
		* \brief Metoda zapisuj¹ca.
		*
		* Metoda s³u¿¹ca do zapisu danych do wêz³a xml podanego jako parametr.
		* \param[out] wezel - Wêze³ do którego s¹ zapisywane dane.
		* \return Zwracana jest wartoœæ true, je¿eli zapisano obiekt poprawnie. False, je¿eli zapis siê nie powiód³.
		* \warning Je¿eli zwrócono wartoœæ false wêze³ przekazany jako parametr nie jest zmodyfokowany.
		*/
		virtual bool zapisz(XmlBO::ElementWezla wezel) const = 0;

		/**
		* \brief Metoda odczytuj¹ca.
		*
		* Metoda s³u¿¹ca do odczytu danych z wêz³a xml podanego jako parametr.
		* \param[in] wezel - Wêze³ z którego s¹ odczytywane dane.
		* \return Zwracana jest wartoœæ true, je¿eli odczytano obiekt poprawnie. False, je¿eli odczyt siê nie powiód³.
		* \warning Metoda nie modyfikuje wêz³a.
		* \warning Je¿eli metoda zwróci wartoœæ false, obiekt mo¿e znajdowaæ siê w stanie nieustalonym. Nie jest zalecane u¿ywanie takiego obiektu.
		*/
		virtual bool odczytaj(XmlBO::ElementWezla wezel) = 0;
	};
}