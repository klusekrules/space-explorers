#pragma once
#include "CRC.h"
class ALGORYTMY_API CRC32 : public CRCInterface<unsigned __int32>
{
public:
	CRC32();
	virtual ~CRC32() = default;
	unsigned __int32 calc(const char *data, unsigned int size) override;
private:
	static unsigned __int32 crc_table[256];
	static bool calculated;
	void calcCrcTable();
};

