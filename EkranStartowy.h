#pragma once
#include "stdafx.h"
#include "EkranSzablon.h"


class EkranStartowy: 
	public EkranSzablon
{
public:
	EkranStartowy(  sf::RenderWindow& okno , TiXmlElement* wezel);
	virtual ~EkranStartowy(void);

	void uaktualnij( Stan& stan ) override;
	
protected:
	
	sf::WindowHandle okno_;

	const Stan::KrokCzasu czasWlaczania_;
	const Stan::KrokCzasu czasTrwalosci_;
	Stan::KrokCzasu czasChwilowy_;

	Identyfikator idStanuWejscia_;	
	Identyfikator idZdarzeniaWyjscia_;
};

