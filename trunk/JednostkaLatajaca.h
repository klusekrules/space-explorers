#pragma once
#include "Main.h"
#include "Fluktuacja.h"
#include "Predkosc.h"
#include "Dystans.h"
#include "JednostkaLatajacaInfo.h"
#include "NiezainicjalizowanaKlasa.h"
#include "PodstawoweParametry.h"
/**
* Klasa implementuj�ca interfejs, s�u��cy do lot�w statk�w kosmiczych.
* Pozwala na wyliczenie wszystkich parametr�w lotu.
*/
class JednostkaLatajaca :
	virtual public PodstawoweParametry,
	virtual public LoggerInterface
{
public:

	/**
	* Konstruktor parametryczny
	* \param jInfo - Wskazanie na klas� opisuj�c�
	* \param mocSilnika - Procentowa warto�� mocy w klasie opisuj�cej. Domy�lnie 1.0 
	* \param zuzyciePaliwa - Procentowa warto�� zu�ycia paliwa w klasie opisuj�cej. Domy�lnie 1.0 
	*/
	JednostkaLatajaca( const Poziom& p, const Identyfikator& idP, const JednostkaLatajacaInfo& jInfo );
	JednostkaLatajaca( const PodstawoweParametry& p , const JednostkaLatajacaInfo& jInfo );
	
	/**
	* Funkcja wyliczaj�ca zy�ycie paliwa przez statek na okre�lonym dystansie i przy okre�lonej pr�ko�ci.
	* \param d - Dystans, na kt�rym ma porusza� si� statek.
	* \param p - Pr�dko��, kt�r� ma lecie� statek.
	* \return Paliwo zu�yte przez statek.
	*/
	virtual ZuzyciePaliwa WyliczZuzyciePaliwa( const Dystans& d , const Predkosc& p) const;

	/**
	* Funkcja podaj�ca jednostkowe zu�ycie paliwa.
	* \param pz - Poziom dla kt�rego jest wyliczane zu�ycie.
	* \return Paliwo zu�yte przez statek.
	*/
	virtual ZuzyciePaliwa getJednostkoweZuzyciePaliwa()const;

	virtual MocSilnika getMocSilnika()const;

	virtual Masa getMasaSilnika()const;

	virtual Fluktuacja getSprawnoscSilnika()const;

	/**
	* Maksymalna pr�ko�� jak� mo�e rozwin�� statek.
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
	* \return pr�dko�� jak� mo�e rozwin�� statek.
	*/
	Predkosc PredkoscMaksymalna() const;
	
	/**
	* Metoda opisuj�ca zawarto�� klasy.
	* \return CI�g znak�w opisuj�cy klas�.
	*/
	string napis() const override;

protected:

	/**
	* Metoda zwracaj�ca ca�kowit� mas� statku w raz z mas� �adowni.
	* \return Ca�kowita masa statku
	*/
	virtual Masa CalkowitaMasaJednostki() const;
	
	const JednostkaLatajacaInfo& jednostkaLatajacaInfo; /// Wska�nika na klase opisuj�c�.
	
};

