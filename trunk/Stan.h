#pragma once
#include "stdafx.h"
#include "StanInfo.h"

class Stan
{
public:
	Stan(StanInfo&);
	~Stan();

	bool akcjaWejscia();
	bool akcjaWewnetrzna();
	bool akcjaWyjscia();

	Identyfikator id_;
	int numer_;
	std::vector< Identyfikator > listaEkranow_;

private:
	StanInfo& info_;
};

