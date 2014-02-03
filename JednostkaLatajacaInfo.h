#pragma once
#include "Info.h"
#include "PodstawoweParametry.h"
#include "Zmiana\ZmianaInterfejs.h"

namespace SpEx{
	/**
	* \brief Klasa opisuj¹ca statek pod k¹tem przemieszczania siê.
	*
	* Przechowuje informacje odnoœnie mocy silnika, zu¿ycia paliwa przez statek, rodzaju napêdu statku, uk³adu napêdowego statku.
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
		* \param[in] klucz - Rodzaj napêdu ( silnika )
		* \param[in] mocSilnika - Moc silnika
		* \param[in] zuzyciePaliwa - Zu¿ycia paliwa przez silnik
		* \param[in] masa - Masa uk³adu napêdowego
		*/
		JednostkaLatajacaInfo(const STyp::Identyfikator& klucz, const STyp::Moc& mocSilnika, const STyp::ZuzyciePaliwa& zuzyciePaliwa, const STyp::Masa& masa);

		/**
		* Konstruktor tworz¹cy obiekt na podstawie wêz³a xml.
		* \param[in] wezel - Wêze³ na podstawie, którego jest tworzony obiekt.
		*/
		explicit JednostkaLatajacaInfo(XmlBO::ElementWezla wezel);

		/**
		* \brief Konstruktor kopiuj¹cy.
		*
		* \param[in] obiekt - Obiekt Ÿród³owy.
		*/
		JednostkaLatajacaInfo(const JednostkaLatajacaInfo& obiekt);

		/**
		* \brief Destruktor.
		*/
		virtual ~JednostkaLatajacaInfo() = default;

		/**
		* \brief Metoda zwracaj¹ca rodzaj napêdu jednostki.
		*
		* \return Rodzaj napêdu jednostki.
		*/
		const STyp::Identyfikator& pobierzRodzajNapedu() const;

		/**
		* \brief Metoda wyliczaj¹ca moc silnika jednostki.
		*
		* \param[in] parametry - Parametry wymagane do policzenia atrybutu.
		* \return Moc silnika jednostki.
		*/
		STyp::Moc pobierzMocSilnika(const PodstawoweParametry& parametry) const;

		/**
		* \brief Metoda wyliczaj¹ca zu¿ycie paliwa jednostki.
		*
		* \param[in] parametry - Parametry wymagane do policzenia atrybutu.
		* \return Zu¿ycie paliwa jednostki.
		*/
		STyp::ZuzyciePaliwa pobierzZuzyciePaliwa(const PodstawoweParametry& parametry) const;

		/**
		* Metoda wyliczaj¹ca masê napêdu jednostki.
		*
		* \param[in] parametry - Parametry wymagane do policzenia atrybutu.
		* \return Masa napêdu jednostki.
		*/
		STyp::Masa pobierzMasaNapedu(const PodstawoweParametry& parametry) const;

		/**
		* Metoda wyliczaj¹ca sprawnoœæ silnika jednostki.
		*
		* \param[in] parametry - Parametry wymagane do policzenia atrybutu.
		* \return Sprawnoœæ silnika jednostki.
		*/
		STyp::Fluktuacja pobierzSprawnoscSilnika(const PodstawoweParametry& parametry) const;

		/**
		* Metoda generuj¹ca opis klasy w postaci ci¹gu znaków.
		* \return Napis zwieraj¹cy opis klasy.
		*/
		std::string napis() const override;
	private:

		STyp::Identyfikator	rodzajNapedu_; /// Rodzaj napêdy statku
		STyp::Moc			mocSilnika_; /// Moc silnika statku
		STyp::ZuzyciePaliwa	zuzyciePaliwa_; /// Zu¿ycie paliwa przez statek
		STyp::Masa			masaNapedu_; /// Masa uk³adu napêdowego
		STyp::Fluktuacja	sprawnoscSilnika_; /// Sprawnoœæ silnika.


		std::shared_ptr<SZmi::ZmianaInterfejs>	przyrostMocySilnika_; /// Obiekt wyliczaj¹cy zmianê mocy silnika
		std::shared_ptr<SZmi::ZmianaInterfejs>	przyrostSprawnosciSilnika_; /// Obiekt wyliczaj¹cy zmianê sprawnoœci silnika
		std::shared_ptr<SZmi::ZmianaInterfejs>	przyrostZuzyciaPaliwa_; /// Obiekt wyliczaj¹cy zmianê zu¿ycia paliwa
		std::shared_ptr<SZmi::ZmianaInterfejs>	przyrostMasyNapedu_; /// Obiekt wyliczaj¹cy zmianê masy napêdu
	};
}
