#pragma once
#include "stdafx.h"
#include "EkranSzablon.h"

class EkranStartowy: 
	public EkranSzablon
{
public:
	EkranStartowy(  sf::RenderWindow& okno , XmlBO::ElementWezla wezel);
	virtual ~EkranStartowy(void) = default;

	void uaktualnij( Stan& stan ) override;
	
protected:
	
	sf::WindowHandle okno_;

	const Stan::KrokCzasu czasWlaczania_;
	const Stan::KrokCzasu czasTrwalosci_;
	Stan::KrokCzasu czasChwilowy_;

	STyp::Identyfikator idStanuWejscia_;	
	STyp::Identyfikator idZdarzeniaWyjscia_;
};

