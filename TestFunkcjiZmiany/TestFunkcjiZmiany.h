// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the TESTFUNKCJIZMIANY_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// TESTFUNKCJIZMIANY_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef TESTFUNKCJIZMIANY_EXPORTS
#define TESTFUNKCJIZMIANY_API __declspec(dllexport)
#else
#define TESTFUNKCJIZMIANY_API __declspec(dllimport)
#endif

#include "..\FuncTransf\ZmianaFabryka.h"
#include "..\FuncTransf\ZmianaParametr.h"

class TESTFUNKCJIZMIANY_API ZmianaTest:
	public ZmianaInterfejs,
	virtual public LoggerInterface
{
private:
	static const int idKlasy;
	static ZmianaInterfejs* TworzZmianaTest( TiXmlElement* e ){
		return new ZmianaTest(e);
	}
public:	
	static bool RejestrujZmianaTest( ZmianaFabryka &ref );

private:
	ZmianaParametr parametr;
public:
	long double policzWartosc(long double wartosc, int poziom, int identyfikatorPlanety) const override;

	ZmianaTest* Kopia()const override;

	explicit ZmianaTest( TiXmlElement * e );
	virtual ~ZmianaTest(void);

	string toString () const override;

};

extern "C" bool TESTFUNKCJIZMIANY_API RejestrujZmiany ( ZmianaFabryka& fabryka , Log& logger );
