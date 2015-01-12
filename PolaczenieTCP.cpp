#include "PolaczenieTCP.h"
#include "Logger\Logger.h"
namespace SpEx{

	PolaczenieTCP::PolaczenieTCP()
	{
	}

	bool PolaczenieTCP::wyslij(const std::string &, std::string&) const{
		return false;
	}

	PolaczenieTCP::~PolaczenieTCP()
	{
	}

	std::string PolaczenieTCP::napis() const{
		SLog::Logger log(NAZWAKLASY(PolaczenieTCP));
		return log.napis();
	}
}
