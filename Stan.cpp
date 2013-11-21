#include "Stan.h"


Stan::Stan(StanInfo& info)
	: info_(info)
{
}

Stan::~Stan(void)
{
}

bool Stan::akcjaWejscia(){
	return info_.wykonaj(StanInfo::AkcjaWejsciowa);
}

bool Stan::akcjaWewnetrzna(){
	return info_.wykonaj(StanInfo::AkcjaWewnetrzna);
}

bool Stan::akcjaWyjscia(){
	return info_.wykonaj(StanInfo::AkcjaWyjsciowa);
}
