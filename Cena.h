#pragma once
#include "Main.h"
#include "CenaInterfejs.h"
#include "LoggerInterface.h"

class Cena :
	public CenaInterfejs,
	public LoggerInterface < Cena >
{
public:
	typedef LoggerInterface < Cena > LogCena;

	Cena();
	Cena( const Zbiornik& );
	Cena( const Cena& );
	Cena& operator=(const Cena&);
	virtual ~Cena();

	Cena* Kopia() const override;

	Zbiornik PobierzKoszty( ) const override;

	bool czySpelniaWymagania( const Zbiornik& ) const override;

	const Zbiornik& getKoszty() const;
	void setKoszty( const Zbiornik& );

	string toString() const override;

private:
	Zbiornik obiekty;
};

