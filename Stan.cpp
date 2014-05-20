#include "Stan.h"
#include "Zdarzenie.h"
namespace SpEx{
	Stan::Stan(std::shared_ptr<StanInfo> info)
		: info_(info), numer_(0), dt_(0)
	{
		if (info_)
			id_ = info_->pobierzIdentyfikator();
	}

	Stan::Stan(const Stan& stan, std::shared_ptr<StanInfo> info)
		: info_(info), id_(stan.id_), numer_(stan.numer_), dt_(stan.dt_)
	{
	}

	bool Stan::akcjaWejscia(){
		if (info_)
			return info_->wykonaj(StanInfo::AkcjaWejsciowa);
		else
			return false;
	}

	bool Stan::akcjaWewnetrzna(){
		if (info_)
			return info_->wykonaj(StanInfo::AkcjaWewnetrzna);
		else
			return false;
	}

	bool Stan::akcjaWyjscia(){
		if (info_)
			return info_->wykonaj(StanInfo::AkcjaWyjsciowa);
		else
			return false;
	}

	bool Stan::operator==(const Stan& s)const{
		return numer_ == s.numer_ && id_ == s.id_;
	}

	bool Stan::operator==(const Zdarzenie & s)const{
		return id_ == s.idStanu_;
	}

	std::shared_ptr<StanInfo> Stan::opisStanu() const{
		return info_;
	}
};
