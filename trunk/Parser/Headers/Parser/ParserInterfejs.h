#pragma once
#include <memory>
#include <string>
#include <functional>
#include "ParserSymbol.h"

namespace SPar{
	class PARSER_API ParserAtrybut
	{
	public:
		ParserAtrybut() = default;
		virtual ~ParserAtrybut() = default;
		ParserAtrybut(const ParserAtrybut&) = default;
		ParserAtrybut& operator=(const ParserAtrybut&) = default;
		
		virtual std::shared_ptr<ParserAtrybut> pobierzNastepnyAtrybut() const  = 0;

		virtual bool ustawNazwe(const char*) = 0;
		virtual const char* pobierzNazwe() const = 0;

		virtual bool ustawWartosc(const char*) = 0;
		virtual const char* pobierzWartosc() const = 0;

		virtual bool ustawWartoscInt(int) = 0;
		virtual int pobierzWartoscInt() const = 0;

		virtual bool ustawWartoscUnsignedInt(unsigned int) = 0;
		virtual unsigned int pobierzWartoscUnsignedInt() const = 0;

		virtual bool ustawWartoscInt64(__int64) = 0;
		virtual __int64 pobierzWartoscInt64() const = 0;

		virtual bool ustawWartoscUnsignedInt64(unsigned __int64) = 0;
		virtual unsigned __int64 pobierzWartoscUnsignedInt64() const = 0;

		virtual bool ustawWartoscFloat(float) = 0;
		virtual float pobierzWartoscFloat() const = 0;

		virtual bool ustawWartoscDouble(double) = 0;
		virtual double pobierzWartoscDouble() const = 0;

		virtual bool ustawWartoscLongDouble(long double) = 0;
		virtual long double pobierzWartoscLongDouble() const = 0;

		virtual operator bool()const = 0;

		virtual std::string error()const = 0;

	};

	class PARSER_API ParserElement
	{
	public:
		ParserElement(void) = default;
		virtual ~ParserElement(void) = default;
		ParserElement(const ParserElement&) = default;
		ParserElement& operator=(const ParserElement&) = default;

		virtual bool ustawNazwe(const char*) = 0;
		virtual const char* pobierzNazwe() const = 0;

		virtual bool ustawTekst(const char*) = 0;
		virtual const char* pobierzTekst() const = 0;
		
		virtual std::shared_ptr<ParserAtrybut> pobierzAtrybut(const char*) = 0;
		virtual std::shared_ptr<ParserAtrybut> tworzAtrybut(const char*, const char*) = 0;
		virtual bool usunAtrybut(const char*) = 0;
		
		virtual std::shared_ptr<ParserElement> pobierzElement(const char*) = 0;
		virtual std::shared_ptr<ParserElement> pobierzNastepnyElement(const char*) const = 0;
		virtual std::shared_ptr<ParserElement> tworzElement(const char*) = 0;
		virtual bool usunElement() = 0;

		virtual operator bool()const = 0;

		virtual std::string error()const = 0;

	};

	class PARSER_API ParserDokument
	{
	public:
		ParserDokument(void) = default;
		virtual ~ParserDokument(void) = default;
		ParserDokument(const ParserDokument&) = default;
		ParserDokument& operator=(const ParserDokument&) = default;
		
		virtual std::shared_ptr<ParserElement> pobierzElement( const char* ) = 0;
		virtual std::shared_ptr<ParserElement> tworzElement(const char*) = 0;
		virtual bool usunElement(std::shared_ptr<ParserElement>) = 0;

		virtual bool odczytaj(const char*) = 0;
		virtual bool zapisz(const char*) = 0;

		virtual operator bool()const = 0;

		virtual std::string error()const = 0;

	};
};
