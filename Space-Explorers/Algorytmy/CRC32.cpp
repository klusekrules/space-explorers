#include "CRC32.h"
bool CRC32::calculated = false;
unsigned __int32 CRC32::crc_table[256];

CRC32::CRC32()
{
	if (!calculated)
	{
		calculated = true;
		calcCrcTable();
	}
}

unsigned __int32 CRC32::calc(const char *data, unsigned int size)
{
	unsigned __int32 crc = 0xFFFFFFFF;
	for (unsigned int i = 0; i < size; i++)
	{
		crc = crc_table[(crc ^ (data[i])) & 0xFF] ^ (crc >> 8);
	}
	crc = ~crc;
	return crc;
}

void CRC32::calcCrcTable()
{
	const unsigned __int32 CRCPOLY = 0xEDB88320;
	register unsigned __int32 t;
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