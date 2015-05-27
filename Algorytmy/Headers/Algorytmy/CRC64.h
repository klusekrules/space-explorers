#pragma once
#include "CRC.h"
class ALGORYTMY_API CRC64 : public CRCInterface<unsigned __int64>
{
public:
	CRC64();
	virtual ~CRC64() = default;
	unsigned __int64 calc(const char *data, unsigned int size) override;
private:
	static unsigned __int64 crc_table[256];
	static bool calculated;
	void calcCrcTable();
};
