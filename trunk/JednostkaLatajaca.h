#pragma once
#include "Main.h"
#include "Fluktuacja.h"
#include "Predkosc.h"
#include "Dystans.h"
#include "JednostkaLatajacaInfo.h"
#include "NiezainicjalizowanaKlasa.h"
#include "PodstawoweParametry.h"
/**
* Klasa implementuj¹ca interfejs, s³u¿¹cy do lotów statków kosmiczych.
* Pozwala na wyliczenie wszystkich parametrów lotu.
*/
class JednostkaLatajaca :
	virtual public PodstawoweParametry,
	virtual public LoggerInterface
{
public:

	/**
	* Konstruktor parametryczny
	* \param jInfo - Wskazanie na klasê opisuj¹c¹
	* \param mocSilnika - Procentowa wartoœæ mocy w klasie opisuj¹cej. Domyœlnie 1.0 
	* \param zuzyciePaliwa - Procentowa wartoœæ zu¿ycia paliwa w klasie opisuj¹cej. Domyœlnie 1.0 
	*/
	JednostkaLatajaca( const Poziom& p, const Identyfikator& idP, const JednostkaLatajacaInfo& jInfo );
	JednostkaLatajaca( const PodstawoweParametry& p , const JednostkaLatajacaInfo& jInfo );
	
	/**
	* Funkcja wyliczaj¹ca zy¿ycie paliwa przez statek na okreœlonym dystansie i przy okreœlonej prêkoœci.
	* \param d - Dystans, na którym ma poruszaæ siê statek.
	* \param p - Prêdkoœæ, któr¹ ma lecieæ statek.
	* \return Paliwo zu¿yte przez statek.
	*/
	virtual ZuzyciePaliwa WyliczZuzyciePaliwa( const Dystans& d , const Predkosc& p) const;

	/**
	* Funkcja podaj¹ca jednostkowe zu¿ycie paliwa.
	* \param pz - Poziom dla którego jest wyliczane zu¿ycie.
	* \return Paliwo zu¿yte przez statek.
	*/
	virtual ZuzyciePaliwa getJednostkoweZuzyciePaliwa()const;

	virtual MocSilnika getMocSilnika()const;

	virtual Masa getMasaSilnika()const;

	virtual Fluktuacja getSprawnoscSilnika()const;

	/**
	* Maksymalna prêkoœæ jak¹ mo¿e rozwin¹æ statek.
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
	* \return prêdkoœæ jak¹ mo¿e rozwin¹æ statek.
	*/
	Predkosc PredkoscMaksymalna() const;
	
	/**
	* Metoda opisuj¹ca zawartoœæ klasy.
	* \return CI¹g znaków opisuj¹cy klasê.
	*/
	string napis() const override;

protected:

	/**
	* Metoda zwracaj¹ca ca³kowit¹ masê statku w raz z mas¹ ³adowni.
	* \return Ca³kowita masa statku
	*/
	virtual Masa CalkowitaMasaJednostki() const;
	
	const JednostkaLatajacaInfo& jednostkaLatajacaInfo; /// WskaŸnika na klase opisuj¹c¹.
	
};

