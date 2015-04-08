#pragma once
#include "JednostkaLatajacaInfo.h"
#include "PodstawoweParametry.h"

namespace SpEx{
	/**
	* Klasa implementuj�ca interfejs, s�u��cy do lot�w statk�w.
	* Pozwala na wyliczenie wszystkich parametr�w lotu.
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
		* \param[in] poziom - Poziom tworzonych obiekt�w.
		* \param[in] identyfikatorPlanety - Identyfikator planety rodzica obiektu.
		* \param[in] jednostkaLatajacaInfo - Referencja do obiektu opisuj�cego.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		JednostkaLatajaca(const STyp::Poziom& poziom, const STyp::Identyfikator& identyfikatorPlanety, const JednostkaLatajacaInfo& jednostkaLatajacaInfo);

		/**
		* \brief Konstruktor.
		*
		* Konstruktor.
		* \param[in] podstawoweParametry - Podstawowe parametry tworzonych obiekt�w.
		* \param[in] jednostkaLatajacaInfo - Referencja do obiektu opisuj�cego.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		JednostkaLatajaca(const PodstawoweParametry& podstawoweParametry, const JednostkaLatajacaInfo& jednostkaLatajacaInfo);

		/**
		* \brief Dommy�lny destruktor.
		*
		* Domy�lny destruktor.
		*/
		virtual ~JednostkaLatajaca() = default;

		/**
		* \brief Metoda wyliczaj�ca zy�ycie paliwa przez statek.
		*
		* Metoda wylicza zy�ycie paliwa przez statek na okre�lonym dystansie i przy okre�lonej pr�ko�ci.
		* \param[in] dystans - Dystans, na kt�rym ma porusza� si� statek.
		* \param[in] predkosc - Pr�dko��, kt�r� ma lecie� statek.
		* \return Paliwo zu�yte przez statek.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		virtual STyp::ZuzyciePaliwa wyliczZuzyciePaliwa(const STyp::Dystans& dystans, const STyp::Predkosc& predkosc) const;

		/**
		* \brief Metoda wyliczaj�ca jednostkowe zu�ycie paliwa.
		*
		* Metoda oblicza jednostkowe zu�ycie paliwa.
		* \return Paliwo zu�yte przez statek.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		virtual STyp::ZuzyciePaliwa pobierzJednostkoweZuzyciePaliwa()const;

		/**
		* \brief Metoda wyliczaj�ca moc silnika.
		*
		* Metoda oblicza moc silnika.
		* \return Moc silnika.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		virtual STyp::Moc pobierzMocSilnika()const;

		/**
		* \brief Metoda wyliczaj�ca mas� silnika.
		*
		* Metoda oblicza mas� silnika.
		* \return Masa silnika.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		virtual STyp::Masa pobierzMasaSilnika()const;

		/**
		* \brief Metoda wyliczaj�ca sprawno�� silnika.
		*
		* Metoda oblicza sprawno�� silnika.
		* \return Sprawno�� silnika.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		virtual STyp::Fluktuacja pobierzSprawnoscSilnika()const;

		/**
		* \brief Maksymalna pr�ko�� jak� mo�e rozwin�� statek.
		*
		* Metoda wyliczaj�ca maksymaln� pr�dko�� jak� mo�e rozwin�� statek.
		* Kod pomocniczy w dobraniu wsp�czynnik�w wzoru.
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
		* \return pr�dko�� jak� mo�e rozwin�� statek.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		STyp::Predkosc predkoscMaksymalna() const;

		/**
		* Metoda generuj�ca opis klasy w postaci ci�gu znak�w.
		* \return Napis zwieraj�cy opis klasy.
		*/
		std::string napis() const override;

	protected:

		/**
		* \brief Metoda zwracaj�ca ca�kowit� mas� statku w raz z mas� �adowni.
		*
		* Metoda obliczaj�ca ca�kowit� mas� jednostki lataj�cej.
		* \return Ca�kowita masa statku.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		virtual STyp::Masa calkowitaMasaJednostki() const;

		const JednostkaLatajacaInfo& jednostkaLatajacaInfo_; /// Wska�nika na klase opisuj�c�.

	};
}
