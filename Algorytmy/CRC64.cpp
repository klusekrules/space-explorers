#include "CRC64.h"
bool CRC64::calculated = false;
unsigned __int64 CRC64::crc_table[256];
CRC64::CRC64()
{
	if (!calculated)
	{
		calculated = true;
		calcCrcTable();
	}
}

unsigned __int64 CRC64::calc(const char *data, unsigned int size)
{
	unsigned __int64 crc = 0;
	for (unsigned int i = 0; i < size; i++)
	{
		crc = crc_table[(crc ^ (data[i])) & 0xFF] ^ (crc >> 8);
	}
	crc = ~crc;
	return crc;
}


void CRC64::calcCrcTable()
{
	const unsigned __int64 CRCPOLY = 0x42F0E1EBA9EA3693ULL;
	//0xd800000000000000ULL;
	register unsigned __int64 t;
	for (register unsigned int i = 0; i < 256; i++)
	{
		t = i;
		for (register int j = 8; j > 0; j--)
		{
			if (t & 1)
				t = (t >> 1) ^ CRCPOLY;
			else
				t >>= 1;
		}
		crc_table[i] = t;
	}
}