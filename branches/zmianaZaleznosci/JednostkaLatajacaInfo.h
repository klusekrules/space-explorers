#pragma once
#include "Info.h"
#include "PodstawoweParametry.h"
#include "Zmiana\ZmianaInterfejs.h"

namespace SpEx{
	/**
	* \brief Klasa opisuj�ca statek pod k�tem przemieszczania si�.
	*
	* Przechowuje informacje odno�nie mocy silnika, zu�ycia paliwa przez statek, rodzaju nap�du statku, uk�adu nap�dowego statku.
	* \author Daniel Wojdak
	* \version 1
	* \date 24-07-2013
	*/
	class JednostkaLatajacaInfo :
		virtual public SLog::LoggerInterface
	{
	public:
		/**
		* Konstruktor parametryczny
		* \param[in] info - referencja do obiektu opisowego.
		* \param[in] klucz - Rodzaj nap�du ( silnika )
		* \param[in] mocSilnika - Moc silnika
		* \param[in] zuzyciePaliwa - Zu�ycia paliwa przez silnik
		* \param[in] masa - Masa uk�adu nap�dowego
		*/
		JednostkaLatajacaInfo(const STyp::Identyfikator& klucz, const STyp::Moc& mocSilnika, const STyp::ZuzyciePaliwa& zuzyciePaliwa, const STyp::Masa& masa);

		/**
		* Konstruktor tworz�cy obiekt na podstawie w�z�a xml.
		* \param[in] wezel - W�ze� na podstawie, kt�rego jest tworzony obiekt.
		*/
		explicit JednostkaLatajacaInfo(XmlBO::ElementWezla wezel);

		/**
		* \brief Konstruktor kopiuj�cy.
		*
		* \param[in] obiekt - Obiekt �r�d�owy.
		*/
		JednostkaLatajacaInfo(const JednostkaLatajacaInfo& obiekt);

		/**
		* \brief Destruktor.
		*/
		virtual ~JednostkaLatajacaInfo() = default;

		/**
		* \brief Metoda zwracaj�ca rodzaj nap�du jednostki.
		*
		* \return Rodzaj nap�du jednostki.
		*/
		const STyp::Identyfikator& pobierzRodzajNapedu() const;

		/**
		* \brief Metoda wyliczaj�ca moc silnika jednostki.
		*
		* \param[in] parametry - Parametry wymagane do policzenia atrybutu.
		* \return Moc silnika jednostki.
		*/
		STyp::Moc pobierzMocSilnika(const PodstawoweParametry& parametry) const;

		/**
		* \brief Metoda wyliczaj�ca zu�ycie paliwa jednostki.
		*
		* \param[in] parametry - Parametry wymagane do policzenia atrybutu.
		* \return Zu�ycie paliwa jednostki.
		*/
		STyp::ZuzyciePaliwa pobierzZuzyciePaliwa(const PodstawoweParametry& parametry) const;

		/**
		* Metoda wyliczaj�ca mas� nap�du jednostki.
		*
		* \param[in] parametry - Parametry wymagane do policzenia atrybutu.
		* \return Masa nap�du jednostki.
		*/
		STyp::Masa pobierzMasaNapedu(const PodstawoweParametry& parametry) const;

		/**
		* Metoda wyliczaj�ca sprawno�� silnika jednostki.
		*
		* \param[in] parametry - Parametry wymagane do policzenia atrybutu.
		* \return Sprawno�� silnika jednostki.
		*/
		STyp::Fluktuacja pobierzSprawnoscSilnika(const PodstawoweParametry& parametry) const;

		/**
		* Metoda generuj�ca opis klasy w postaci ci�gu znak�w.
		* \return Napis zwieraj�cy opis klasy.
		*/
		std::string napis() const override;
	private:

		STyp::Identyfikator	rodzajNapedu_; /// Rodzaj nap�dy statku
		STyp::Moc			mocSilnika_; /// Moc silnika statku
		STyp::ZuzyciePaliwa	zuzyciePaliwa_; /// Zu�ycie paliwa przez statek
		STyp::Masa			masaNapedu_; /// Masa uk�adu nap�dowego
		STyp::Fluktuacja	sprawnoscSilnika_; /// Sprawno�� silnika.


		std::shared_ptr<SZmi::ZmianaInterfejs>	przyrostMocySilnika_; /// Obiekt wyliczaj�cy zmian� mocy silnika
		std::shared_ptr<SZmi::ZmianaInterfejs>	przyrostSprawnosciSilnika_; /// Obiekt wyliczaj�cy zmian� sprawno�ci silnika
		std::shared_ptr<SZmi::ZmianaInterfejs>	przyrostZuzyciaPaliwa_; /// Obiekt wyliczaj�cy zmian� zu�ycia paliwa
		std::shared_ptr<SZmi::ZmianaInterfejs>	przyrostMasyNapedu_; /// Obiekt wyliczaj�cy zmian� masy nap�du
	};
}
