#include "ParserAtrybut.h"


se::ParserAtrybut::ParserAtrybut()
{
}

se::ParserAtrybut::~ParserAtrybut()
{
}

bool se::ParserAtrybut::ustawNazwe( const char* ){
	return false;
}

const char* se::ParserAtrybut::pobierzNazwe( ) const{
	return nullptr;
}

bool se::ParserAtrybut::ustawWartosc( const char* ){
	return false;
}

const char* se::ParserAtrybut::pobierzWartosc( ) const{
	return nullptr;
}

bool se::ParserAtrybut::ustawWartoscInt( int ){
	return false;
}

int se::ParserAtrybut::pobierzWartoscInt( ) const{
	return 0;
}

bool se::ParserAtrybut::ustawWartoscUnsignedInt( unsigned int ){
	return false;
}

unsigned int se::ParserAtrybut::pobierzWartoscUnsignedInt( ) const{
	return 0;
}

bool se::ParserAtrybut::ustawWartoscInt64( __int64 ){
	return false;
}

__int64 se::ParserAtrybut::pobierzWartoscInt64( ) const{
	return 0;
}

bool se::ParserAtrybut::ustawWartoscUnsignedInt64( unsigned __int64 ){
	return false;
}

unsigned __int64 se::ParserAtrybut::pobierzWartoscUnsignedInt64( ) const{
	return 0;
}

bool se::ParserAtrybut::ustawWartoscFloat( float ){
	return false;
}

float se::ParserAtrybut::pobierzWartoscFloat( ) const{
	return 0;
}

bool se::ParserAtrybut::ustawWartoscDouble( double ){
	return false;
}

double se::ParserAtrybut::pobierzWartoscDouble( ) const{
	return 0;
}

bool se::ParserAtrybut::ustawWartoscLongDouble( long double ){
	return false;
}

long double se::ParserAtrybut::pobierzWartoscLongDouble( ) const{
	return 0;
}

se::ParserAtrybut::operator bool()const{
	return false;
}
