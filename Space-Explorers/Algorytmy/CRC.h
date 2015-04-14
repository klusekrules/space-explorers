#pragma once
template <class T>
class CRCInterface
{
public:
	virtual T calc(const char *data, unsigned int size) = 0;
	virtual ~CRCInterface() = default;
};

