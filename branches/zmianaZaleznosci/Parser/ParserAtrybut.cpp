#include "ParserAtrybut.h"

namespace SPar{
	ParserAtrybut::ParserAtrybut()
	{
	}

	ParserAtrybut::~ParserAtrybut()
	{
	}

	bool ParserAtrybut::ustawNazwe(const char*){
		return false;
	}

	const char* ParserAtrybut::pobierzNazwe() const{
		return nullptr;
	}

	bool ParserAtrybut::ustawWartosc(const char*){
		return false;
	}

	const char* ParserAtrybut::pobierzWartosc() const{
		return nullptr;
	}

	bool ParserAtrybut::ustawWartoscInt(int){
		return false;
	}

	int ParserAtrybut::pobierzWartoscInt() const{
		return 0;
	}

	bool ParserAtrybut::ustawWartoscUnsignedInt(unsigned int){
		return false;
	}

	unsigned int ParserAtrybut::pobierzWartoscUnsignedInt() const{
		return 0;
	}

	bool ParserAtrybut::ustawWartoscInt64(__int64){
		return false;
	}

	__int64 ParserAtrybut::pobierzWartoscInt64() const{
		return 0;
	}

	bool ParserAtrybut::ustawWartoscUnsignedInt64(unsigned __int64){
		return false;
	}

	unsigned __int64 ParserAtrybut::pobierzWartoscUnsignedInt64() const{
		return 0;
	}

	bool ParserAtrybut::ustawWartoscFloat(float){
		return false;
	}

	float ParserAtrybut::pobierzWartoscFloat() const{
		return 0;
	}

	bool ParserAtrybut::ustawWartoscDouble(double){
		return false;
	}

	double ParserAtrybut::pobierzWartoscDouble() const{
		return 0;
	}

	bool ParserAtrybut::ustawWartoscLongDouble(long double){
		return false;
	}

	long double ParserAtrybut::pobierzWartoscLongDouble() const{
		return 0;
	}

	ParserAtrybut::operator bool()const{
		return false;
	}
}
