#pragma once
#include "AlgorytmySymbol.h"

template <class T>
class ALGORYTMY_API CRCInterface
{
public:
	virtual T calc(const char *data, unsigned int size) = 0;
	virtual ~CRCInterface() = default;
};

