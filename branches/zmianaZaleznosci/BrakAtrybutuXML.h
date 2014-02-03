#pragma once
#include "WyjatekParseraXML.h"

namespace SpEx{
	/**
	* Wyj¹tek s³u¿y do informowania, ¿e w pliku xml w aktualnej ga³êzi nie ma podanego atrybutu.
	*/
	class BrakAtrybutuXML :
		virtual public SLog::LoggerInterface,
		public WyjatekParseraXML
	{
	public:
		static const STyp::Identyfikator idBrakAtrybutuXML;

		BrakAtrybutuXML(const STyp::Tekst& tPlik, const STyp::Ilosc& iLinia, const STyp::Tekst& = STyp::Tekst());
		BrakAtrybutuXML(const BrakAtrybutuXML&);
		virtual ~BrakAtrybutuXML() = default;

		const STyp::Tekst& getAtrybut() const;
		void setAtrybut(const STyp::Tekst&);

		STyp::Tekst generujKomunikat() const override;

		std::string napis() const override;

	private:
		STyp::Tekst atrybut;

		static const STyp::Tekst tytulBrakAtrybutuXML;
		static const STyp::Tekst trescBrakAtrybutuXML;
	};
}
