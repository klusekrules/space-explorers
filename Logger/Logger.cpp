#include "Logger.h"

namespace SLog{
	
	Logger::Logger(const std::string& nazwa){
		napis_ << nazwa << "[";
	}

	std::string Logger::napis() const{
		return std::move(napis_.str() + " ]");
	}

	void Logger::dodajKlase(const std::string& opisKlasy){
		napis_ << " " << opisKlasy;
	}

	void Logger::dodajPole(const std::string& nazwa, const LoggerInterface& obiekt){
		wstaw(nazwa, obiekt.napis());
	}

	void Logger::dodajPole(const std::string& nazwa, const std::shared_ptr<const LoggerInterface> obiekt){
		if (obiekt)
			wstaw(nazwa, obiekt->napis());
	}

	void Logger::dodajPole(const std::string& nazwa, const std::string& typ,const std::string& opisPola){
		wstaw(nazwa, typ + "[ \"" + opisPola + "\" ]");
	}

	void Logger::wstaw(const std::string& nazwa, const std::string& opisPola){
		napis_ << " " << nazwa << "=" << opisPola;
	}

	void Logger::rozpocznijPodKlase(const std::string& zmienna, const std::string& nazwa){
		napis_ << " " << zmienna << "=" << nazwa << "[";
	}

	void Logger::rozpocznijPodKlase(const std::string& nazwa){
		napis_ << " " << nazwa << "[";
	}

	void Logger::zakonczPodKlase(){
		napis_ << " ]";
	}
}
