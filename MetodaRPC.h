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

		typedef std::pair<std::string, std::string> Parametr;

		MetodaRPC( const PolaczenieTCP& );
		~MetodaRPC() = default;

		virtual void operator()(const Json::Value &, Json::Value&);

		bool operator()();

		virtual bool inicjalizacjaParametrow();

		virtual bool obslugaOdpowiedzi(const Json::Value &);

		bool operator<<(const Json::Value &);

		const MetodaRPC& operator>>(Json::Value &) const;

		std::string napis() const override;

	protected:
		std::string autoryzacja_;
		std::string instancja_;

		std::string id_;
		std::string nazwa_;
		std::string id_unikalne_;
		unsigned int powtorzenie_;
		std::string czas_wywolania_;
		std::string czas_odpowiedzi_;
		std::vector <Parametr> parametry_;
		PolaczenieTCP polaczenie_;

	};
}

