#pragma once
#include <string>
#include <memory>
#include "ZarzadcaZasobow.h"
#include "Parser\ParserDokumentXml.h"

namespace SpEx {
	class NARZEDZIA_API XmlModul
		: public Zasob
	{
	public:
		friend class std::_Ref_count_obj<XmlModul>;
		static const std::string NazwaTypu_;
		typedef std::shared_ptr<XmlModul> SharedPtr; /// Silny wskaŸnik na klasê.
		typedef std::weak_ptr<XmlModul> WeakPtr; /// S³aby wskaŸnik na klasê.

		virtual ~XmlModul() = default;

		bool inicjalizuj() override;

		inline std::shared_ptr<SPar::ParserDokumentXml> operator()() const{
			return handle_;
		}

		const std::string& nazwa() override{
			return NazwaTypu_;
		}

	private:
		XmlModul(const std::string& plik);


		std::shared_ptr<SPar::ParserDokumentXml> handle_; /// Uchwyt do wczytanego modu³u dll.
	};
}
