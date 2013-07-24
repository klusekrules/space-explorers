#pragma once
#include "JednostkaLatajacaInfo.h"
#include "Fluktuacja.h"
#include "Predkosc.h"
#include "Dystans.h"
#include "NiezainicjalizowanaKlasa.h"
#include "PodstawoweParametry.h"

/**
* Klasa implementuj�ca interfejs, s�u��cy do lot�w statk�w.
* Pozwala na wyliczenie wszystkich parametr�w lotu.
* \author Daniel Wojdak
* \version 1
* \date 24-07-2013
*/
class JednostkaLatajaca :
	virtual public PodstawoweParametry,
	virtual public LoggerInterface
{
public:
	/**
	* \brief Konstruktor.
	*
	* \param[in] poziom - Poziom tworzonych obiekt�w.
	* \param[in] identyfikatorPlanety - Identyfikator planety rodzica obiektu.
	* \param[in] jednostkaLatajacaInfo - Referencja do obiektu opisuj�cego.
	*/
	JednostkaLatajaca( const Poziom& poziom, const Identyfikator& identyfikatorPlanety, const JednostkaLatajacaInfo& jednostkaLatajacaInfo );

	/**
	* \brief Konstruktor.
	*
	* \param[in] podstawoweParametry - Podstawowe parametry tworzonych obiekt�w.
	* \param[in] jednostkaLatajacaInfo - Referencja do obiektu opisuj�cego.
	*/
	JednostkaLatajaca( const PodstawoweParametry& podstawoweParametry, const JednostkaLatajacaInfo& jednostkaLatajacaInfo );
	
	/**
	* \brief Destruktor.
	*/
	virtual ~JednostkaLatajaca();

	/**
	* \brief Metoda wyliczaj�ca zy�ycie paliwa przez statek.
	*
	* Metoda wylicza zy�ycie paliwa przez statek na okre�lonym dystansie i przy okre�lonej pr�ko�ci.
	* \param[in] dystans - Dystans, na kt�rym ma porusza� si� statek.
	* \param[in] predkosc - Pr�dko��, kt�r� ma lecie� statek.
	* \return Paliwo zu�yte przez statek.
	*/
	virtual ZuzyciePaliwa wyliczZuzyciePaliwa( const Dystans& dystans , const Predkosc& predkosc ) const;

	/**
	* \brief Metoda wyliczaj�ca jednostkowe zu�ycie paliwa.
	*
	* \return Paliwo zu�yte przez statek.
	*/
	virtual ZuzyciePaliwa pobierzJednostkoweZuzyciePaliwa()const;

	/**
	* \brief Metoda wyliczaj�ca moc silnika.
	*
	* \return Moc silnika.
	*/
	virtual MocSilnika pobierzMocSilnika()const;

	/**
	* \brief Metoda wyliczaj�ca mas� silnika.
	*
	* \return Masa silnika.
	*/
	virtual Masa pobierzMasaSilnika()const;

	/**
	* \brief Metoda wyliczaj�ca sprawno�� silnika.
	*
	* \return Sprawno�� silnika.
	*/
	virtual Fluktuacja pobierzSprawnoscSilnika()const;

	/**
	* \brief Maksymalna pr�ko�� jak� mo�e rozwin�� statek.
	*
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
	*/
	Predkosc predkoscMaksymalna() const;
	
	/**
	* Metoda generuj�ca opis klasy w postaci ci�gu znak�w.
	* \return Napis zwieraj�cy opis klasy.
	*/
	string napis() const override;

protected:

	/**
	* \brief Metoda zwracaj�ca ca�kowit� mas� statku w raz z mas� �adowni.
	*
	* \return Ca�kowita masa statku.
	*/
	virtual Masa calkowitaMasaJednostki() const;
	
	const JednostkaLatajacaInfo& jednostkaLatajacaInfo_; /// Wska�nika na klase opisuj�c�.
	
};
