#pragma once
#include "Logger\LoggerInterface.h"

namespace SpEx{
	class PolaczenieTCP :
		virtual public SLog::LoggerInterface
	{
	public:
		PolaczenieTCP();
		~PolaczenieTCP();
		bool wyslij(const std::string &, std::string&) const;
		std::string napis() const override;
	};
}
