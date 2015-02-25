#pragma once
#include <string>
#include <vector>
#include "Parser\json\json.h"
#include "Klient.h"
#include "Logger\LoggerInterface.h"

namespace SpEx{
	class MetodaRPC :
		virtual public SLog::LoggerInterface
	{
	public:
		friend class std::_Ref_count_obj<MetodaRPC>;
		friend class Fabrykator;
		friend class Klient;

		typedef std::pair<std::string, std::string> Parametr;

		static int sprawdzCRC(Json::Value&);
		static void dodajCRC(Json::Value&);
		static int waliduj(Json::Value&, bool);


		~MetodaRPC() = default;

		int pobierzFlagi() const;

		int wykonajMetode();

		void dodajParametr(const std::string&, std::string&);

		bool obsluzMetode(Json::Value&);

		std::string napis() const override;
				
	protected:
		MetodaRPC(Klient&);

		std::string autoryzacja_;
		std::string instancja_;

		std::string nazwa_;
		std::string id_unikalne_;
		unsigned int powtorzenie_;
		std::string czas_wywolania_;
		std::string czas_odpowiedzi_;
		std::vector <Parametr> parametry_;
		int flagi_;
		Klient& klient_;
		
		int wykonajMetode_impl();

		int obslugaWyjatku(const Json::Value&);

		static int sprawdzMetode(const Json::Value&, bool);
		static int sprawdzMetodeUprzywilejowana(const Json::Value&);
		static int sprawdzAutoryzacje(const Json::Value&);
		
		virtual void obslugaZadania(const Json::Value &, Json::Value&);
		virtual bool przygotowanieDoWyslania();
		virtual bool obslugaOdpowiedzi(const Json::Value &);
		virtual bool operator<<(const Json::Value &);
		virtual const MetodaRPC& operator>>(Json::Value &) const;

	};
}

