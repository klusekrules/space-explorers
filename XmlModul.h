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
		friend class std::_Ref_count_obj<XmlModul>;
		static const std::string NazwaTypu_;
		typedef std::shared_ptr<XmlModul> SharedPtr; /// Silny wska�nik na klas�.
		typedef std::weak_ptr<XmlModul> WeakPtr; /// S�aby wska�nik na klas�.
		static Zasob::SharedPtr Tworz(const ZarzadcaZasobow::Parametr& parametr, bool cache);

		virtual ~XmlModul() = default;

		bool inicjalizuj() override;

		inline std::shared_ptr<SPar::ParserDokumentXml> operator()() const{
			return handle_;
		}

		inline const std::string& pobierzPlik() const{
			return plik_;
		}

	private:
		XmlModul(const std::string& plik);


		std::string plik_; /// Lokalizacja pliku dll.
		std::shared_ptr<SPar::ParserDokumentXml> handle_; /// Uchwyt do wczytanego modu�u dll.
	};
}
