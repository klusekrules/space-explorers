#pragma once
#include "stdafx.h"
#include "Watek.h"
#include "Logger\Log.h"

class OknoGry :
	public Watek
{
public:
	OknoGry( bool wstrzymany );
	virtual ~OknoGry(void);
private:
	sf::RenderWindow oknoGlowne_;
	sf::Shader testShadera_;
	
	void wykonuj() override;
	bool inicjalizacja();
};

