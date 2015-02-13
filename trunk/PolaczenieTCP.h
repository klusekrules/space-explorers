#pragma once
#include "Logger\LoggerInterface.h"
#include "Klient.h"
namespace SpEx{
	class PolaczenieTCP :
		virtual public SLog::LoggerInterface
	{
	public:
		PolaczenieTCP(Klient&);
		~PolaczenieTCP() = default;
		bool wyslij(std::shared_ptr<const std::string>, std::shared_ptr<std::string>, int) const;
		std::string napis() const override;
	private:
		Klient& klient_;
	};
}
