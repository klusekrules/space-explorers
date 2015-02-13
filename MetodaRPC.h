#pragma once
#include <string>
#include <vector>
#include "Parser\json\json.h"
#include "PolaczenieTCP.h"
#include "Logger\LoggerInterface.h"

namespace SpEx{
	class MetodaRPC :
		virtual public SLog::LoggerInterface
	{
	public:
		friend class Fabrykator;
		friend class Klient;

		typedef std::pair<std::string, std::string> Parametr;

		MetodaRPC(const PolaczenieTCP&);
		~MetodaRPC() = default;

		virtual void obslugaZadania(const Json::Value &, Json::Value&);
		
		bool operator()();

		virtual bool inicjalizacjaParametrow();

		virtual bool obslugaOdpowiedzi(const Json::Value &);

		bool operator<<(const Json::Value &);

		const MetodaRPC& operator>>(Json::Value &) const;

		int pobierzFlagi() const;

		std::string napis() const override;

		static int sprawdzCRC(Json::Value&);

		static void dodajCRC(Json::Value&);

		static int waliduj(Json::Value&);
				
	protected:
		std::string autoryzacja_;
		std::string instancja_;

		std::string nazwa_;
		std::string id_unikalne_;
		unsigned int powtorzenie_;
		std::string czas_wywolania_;
		std::string czas_odpowiedzi_;
		std::vector <Parametr> parametry_;
		int flagi_;
		PolaczenieTCP polaczenie_;

		static int sprawdzMetode(const Json::Value&);
		static int sprawdzMetodeUprzywilejowana(const Json::Value&);
		static int sprawdzAutoryzacje(const Json::Value&);


	};
}

