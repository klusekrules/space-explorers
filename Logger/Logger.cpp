#include "Logger.h"

namespace SLog{

	Logger::Logger(const std::string& nazwa){
		napis_ << nazwa << "[";
	}

	std::string&& Logger::napis() const{
		return std::move(napis_.str() + " ]");
	}

	void Logger::dodajKlase(const std::string& opisKlasy){
		testPierwszegoPola();
		napis_ << " " << opisKlasy;
	}

	std::string&& Logger::tworzPole(const std::string& nazwa, const LoggerInterface& obiektPierwszy, const LoggerInterface& obiektDrugi){
		return std::move(nazwa + " { " + obiektPierwszy.napis() + " , " + obiektDrugi.napis() + " }");
	}

	std::string&& Logger::tworzKlase(const std::string& nazwaKlasy, const std::string& opisKlasy){
		return std::move(nazwaKlasy + "[ " + opisKlasy + " ]");
	}

	void Logger::dodajPole(const std::string& nazwa, const LoggerInterface& obiekt){
		dodajPole(nazwa, obiekt.napis());
	}

	void Logger::dodajPole(const std::string& nazwa, const std::shared_ptr<LoggerInterface> obiekt){
		if (obiekt)
			dodajPole(nazwa, obiekt->napis());
	}

	void Logger::dodajPole(const std::string& nazwa, const std::string& opisPola){
		testPierwszegoPola();
		napis_ << " " << nazwa << "=" << opisPola;
	}

	void Logger::dodajPole(const std::string& nazwa, const LoggerInterface& obiektPierwszy, const LoggerInterface& obiektDrugi){
		testPierwszegoPola();
		napis_ << nazwa << " { " << obiektPierwszy.napis() << " , " << obiektDrugi.napis() << " }";
	}

	void Logger::rozpocznijPodKlase(const std::string& nazwa){
		testPierwszegoPola();
		napis_ << nazwa << "[ ";
		stos_.push(true);
	}

	void Logger::zakonczPodKlase(){
		stos_.pop();
		napis_ << " ]";
	}

	void Logger::testPierwszegoPola(){
		if (!stos_.top())
			napis_ << ", ";
		else
			stos_.top() = false;
	}
}
