#pragma once
#include <string>
#include <memory>
#include "ZarzadcaZasobow.h"
#include "Parser\ParserDokumentXml.h"
#define XML_ATRYBUT_TYP_ZASOBU_XML "xml"
namespace SpEx {
	class XmlModul
		: public Zasob
	{
	public:
		typedef std::shared_ptr<XmlModul> SharedPtr; /// Silny wskaŸnik na klasê.
		typedef std::weak_ptr<XmlModul> WeakPtr; /// S³aby wskaŸnik na klasê.

		XmlModul(const std::string& plik);
		virtual ~XmlModul();

		bool inicjalizuj() override;
		static bool Rejestruj(ZarzadcaZasobow &fabryka);

		inline std::shared_ptr<SPar::ParserDokumentXml> operator()() const{
			return handle_;
		}

		inline const std::string& pobierzPlik() const{
			return plik_;
		}

	private:

		static Zasob::SharedPtr Tworz(const ZarzadcaZasobow::Parametr& parametr, bool cache);

		std::string plik_; /// Lokalizacja pliku dll.
		std::shared_ptr<SPar::ParserDokumentXml> handle_; /// Uchwyt do wczytanego modu³u dll.
	};
}
