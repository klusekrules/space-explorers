#pragma once
#include <map>
#include <memory>
#include "ZmianaSymbol.h"
#include "ZmianaInterfejs.h"
#include "Logger\Log.h"
#include "Parser\XmlBO.h"

namespace SZmi{
	/**
	* \brief Fabryka klas zmian
	*
	* Klasa tworz¹ca instacje klas zmian. Klasa implementuje wzorzec singleton.
	* \author Daniel Wojdak
	* \version 2
	* \date 26-11-2014
	*/
	class ZMIANA_API ZmianaFabryka :
		public virtual SLog::LoggerInterface
	{
	public:
		/**
		* Prototyp funkcji tworz¹cej instacjê obiektu danej klasy.
		* \param[in] wezel - Wezel na podstawie, którego tworzony jest obiekt.
		* \return WskaŸnik na obiekt pochodny po ZmianaInterfejs.
		*/
		typedef ZmianaInterfejs* (*KreatorZmiany)(XmlBO::ElementWezla wezel);

		/**
		* Prototyp funkcji rejestruj¹cej klasê zmiany w fabryce.
		* \param[in,out] fabryka - Instacja fabryki, w której nale¿y zarejestrowaæ zmianê, aby aplikacja potrafi³a utworzyæ obiekt zmiany.
		* \param[in,out] logger - Instacja loggera do wyœwietlania komunikatów o b³êdach.
		* \return Funkcja powinna zwracaæ true, jeœli rejestracja siê powiedzie lub false w przeciwnym wypadku.
		* \remark Funkcja powonna wywo³ywaæ na rzecz obiektu fabryka metodê RejestracjaZmiany.
		* \sa RejestracjaZmiany()
		*/
		typedef bool(*RejestrujZmiane)(ZmianaFabryka& fabryka, SLog::Log& logger);

		/**
		* Konstruktor bezparametrowy.
		*/
		ZmianaFabryka() = default;

		virtual ~ZmianaFabryka() = default;

		/**
		* Metoda tworz¹ca obiekt klasy zmiana zarejestrownej w fabryce, na podstawie wêz³a przekazanego przez parametr wezel. Wywo³uje ona funckjê zarejestrowan¹ przez metodê rejestracjaZmiany i przekazuje jej wezel.
		* \param[in] wezel - Wêze³ na podstawie, którego tworzony jest obiekt klasy zmiana.
		* \return Metoda zwraca inteligenty wskaŸnik na utworzony obiekt. Je¿eli operacja siê nie powiedzie zwracany jest wska¿nik na nullptr.
		* \pre Wêze³ powinien mieæ poprawny atrybut o nazwie zdefiniowanej przez ATRYBUT_XML_IDENTYFIKATOR zawieraj¹cy identyfikator podany podczas rejestracji w funkcji rejestracjaZmiany.
		* \sa rejestracjaZmiany(), ATRYBUT_XML_IDENTYFIKATOR
		*/
		std::shared_ptr<ZmianaInterfejs> tworz(XmlBO::ElementWezla wezel) const;

		/**
		* Metoda rejestruj¹ca funkcjê tworz¹c¹ obiekt pochodny po ZmianaInterfejs.
		* \param[in] identyfikator - Identyfikator funckji.
		* \param[in] funkcja - Funkcja tworz¹ca.
		* \return Metoda zwraca true, je¿eli rejestracja siê powiedzie lub false w przeciwnym wypadku.
		* \warning Zabronionym identyfikatorem jest 0. Je¿eli poda siê taki identyfikator to metoda zawsze zwróci wartoœæ false. Jest to podyktowane implementaj¹ metody. Inne warunki kiedy metoda zwróci false to: funkcja wskazuje na nullptr lub identyfikator zosta³ ju¿ u¿yty.
		*/
		bool rejestracjaZmiany(const STyp::Identyfikator& identyfikator, KreatorZmiany funkcja);

		/**
		* Funkcja s³u¿¹ca do tworzenia napisów z opisem klasy.
		* \return Napis zawieraj¹cy opis klasy.
		* \author Daniel Wojdak
		* \version 1
		* \date 26-11-2014
		*/
		std::string napis() const override;

	private:

		/**
		* Typ zbioru funkcji tworz¹cych obiekt.
		*/
		typedef std::map<STyp::Identyfikator, KreatorZmiany> Callbacks;

		Callbacks callbacks_; ///S³ownik funkcji tworz¹cych obiekty pochodzne po ZmianaInterfejs.

		ZmianaFabryka(const ZmianaFabryka&) = delete;

		ZmianaFabryka& operator=(const ZmianaFabryka&) = delete;

		ZmianaFabryka(ZmianaFabryka&&) = delete;

		ZmianaFabryka&& operator=(ZmianaFabryka&&) = delete;
	};
}
