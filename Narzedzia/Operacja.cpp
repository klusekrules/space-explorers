#include "Operacja.h"
#include "Logger\Logger.h"
namespace SpEx{
	bool Operacja::wykonaj(){
		return false;
	}

	bool Operacja::cofnij(){
		return false;
	}

	std::string Operacja::napis() const {
		SLog::Logger str(NAZWAKLASY(Operacja));
		return str.napis();
	}
};
