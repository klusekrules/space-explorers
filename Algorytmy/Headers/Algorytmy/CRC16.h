#pragma once
#include "CRC.h"

class ALGORYTMY_API CRC16 : public CRCInterface<unsigned __int16>
{
public:
	CRC16() = default;
	virtual ~CRC16() = default;
	unsigned __int16 calc(const char *data, unsigned int size) override;
private:
	static unsigned __int16 crc_table[256];
};

