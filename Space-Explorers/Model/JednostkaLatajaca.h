#pragma once
#include "JednostkaLatajacaInfo.h"
#include "PodstawoweParametry.h"

namespace SpEx{
	/**
	* Klasa implementuj¹ca interfejs, s³u¿¹cy do lotów statków.
	* Pozwala na wyliczenie wszystkich parametrów lotu.
	* \author Daniel Wojdak
	* \version 1
	* \date 24-07-2013
	*/
	class JednostkaLatajaca :
		virtual public PodstawoweParametry,
		virtual public SLog::LoggerInterface
	{
	public:
		/**
		* \brief Konstruktor.
		*
		* Konstruktor.
		* \param[in] poziom - Poziom tworzonych obiektów.
		* \param[in] identyfikatorPlanety - Identyfikator planety rodzica obiektu.
		* \param[in] jednostkaLatajacaInfo - Referencja do obiektu opisuj¹cego.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		JednostkaLatajaca(const STyp::Poziom& poziom, const STyp::Identyfikator& identyfikatorPlanety, const JednostkaLatajacaInfo& jednostkaLatajacaInfo);

		/**
		* \brief Konstruktor.
		*
		* Konstruktor.
		* \param[in] podstawoweParametry - Podstawowe parametry tworzonych obiektów.
		* \param[in] jednostkaLatajacaInfo - Referencja do obiektu opisuj¹cego.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		JednostkaLatajaca(const PodstawoweParametry& podstawoweParametry, const JednostkaLatajacaInfo& jednostkaLatajacaInfo);

		/**
		* \brief Dommyœlny destruktor.
		*
		* Domyœlny destruktor.
		*/
		virtual ~JednostkaLatajaca() = default;

		/**
		* \brief Metoda wyliczaj¹ca zy¿ycie paliwa przez statek.
		*
		* Metoda wylicza zy¿ycie paliwa przez statek na okreœlonym dystansie i przy okreœlonej prêkoœci.
		* \param[in] dystans - Dystans, na którym ma poruszaæ siê statek.
		* \param[in] predkosc - Prêdkoœæ, któr¹ ma lecieæ statek.
		* \return Paliwo zu¿yte przez statek.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		virtual STyp::ZuzyciePaliwa wyliczZuzyciePaliwa(const STyp::Dystans& dystans, const STyp::Predkosc& predkosc) const;

		/**
		* \brief Metoda wyliczaj¹ca jednostkowe zu¿ycie paliwa.
		*
		* Metoda oblicza jednostkowe zu¿ycie paliwa.
		* \return Paliwo zu¿yte przez statek.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		virtual STyp::ZuzyciePaliwa pobierzJednostkoweZuzyciePaliwa()const;

		/**
		* \brief Metoda wyliczaj¹ca moc silnika.
		*
		* Metoda oblicza moc silnika.
		* \return Moc silnika.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		virtual STyp::Moc pobierzMocSilnika()const;

		/**
		* \brief Metoda wyliczaj¹ca masê silnika.
		*
		* Metoda oblicza masê silnika.
		* \return Masa silnika.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		virtual STyp::Masa pobierzMasaSilnika()const;

		/**
		* \brief Metoda wyliczaj¹ca sprawnoœæ silnika.
		*
		* Metoda oblicza sprawnoœæ silnika.
		* \return Sprawnoœæ silnika.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		virtual STyp::Fluktuacja pobierzSprawnoscSilnika()const;

		/**
		* \brief Maksymalna prêkoœæ jak¹ mo¿e rozwin¹æ statek.
		*
		* Metoda wyliczaj¹ca maksymaln¹ prêdkoœæ jak¹ mo¿e rozwin¹æ statek.
		* Kod pomocniczy w dobraniu wspó³czynników wzoru.
		* \code {.cpp}
		* locale pl ("Polish");
		* locale::global (pl);
		* cout.imbue(pl);
		* long double P = 50000000 , eta_m = 0.80 , m = 1000000, a = 0.01 , V = 0, rs=9500000000000;
		* for(double i = 10 ;  i < 30 ; i+=0.5){
		* 	double j = 0.00005;
		* 	for( int c = 1 ;  c <=5; c++ ){
		* 		j*=(double)c / 10;
		* 	V = ((P*i)*eta_m)/(m*a);
		* 	cout << "\nWspolczynnik zakrzywienia przestrzeni: "<< setprecision(10)<< fixed<< j << endl;
		* 	cout << "Moc: " << setw(10) <<(long long)((P*i)/735.5) << " KM, Vmax: " << setw(10)<< (long long) (V * 3.6)
		* 		<<" km/h, Czas lotu rs: "<< setw(8) << ((100*rs*j)/(V*3.6)) << " h"<< endl;
		* 	}
		* }
		* \endcode
		* \return prêdkoœæ jak¹ mo¿e rozwin¹æ statek.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		STyp::Predkosc predkoscMaksymalna() const;

		/**
		* Metoda generuj¹ca opis klasy w postaci ci¹gu znaków.
		* \return Napis zwieraj¹cy opis klasy.
		*/
		std::string napis() const override;

	protected:

		/**
		* \brief Metoda zwracaj¹ca ca³kowit¹ masê statku w raz z mas¹ ³adowni.
		*
		* Metoda obliczaj¹ca ca³kowit¹ masê jednostki lataj¹cej.
		* \return Ca³kowita masa statku.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		virtual STyp::Masa calkowitaMasaJednostki() const;

		const JednostkaLatajacaInfo& jednostkaLatajacaInfo_; /// WskaŸnika na klase opisuj¹c¹.

	};
}
