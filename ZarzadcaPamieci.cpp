#include "ZarzadcaPamieci.h"
#include "definicjeWezlowXML.h"
#include "XmlBO.h"


ZarzadcaPamieci::ZarzadcaPamieci(void)
{
}

ZarzadcaPamieci::~ZarzadcaPamieci(void)
{
}

shared_ptr< Planeta > ZarzadcaPamieci::pobierzPlanete( const Identyfikator& identyfikator ){
	auto planeta = planety_.find(identyfikator);
	if(planeta == planety_.end())
		return nullptr;
	if(!planeta->second.planeta_){
		wczytajUkladSloneczny(planeta->second.idUkladu_);
		return planety_[identyfikator].planeta_;
	}
	return planeta->second.planeta_;
}

int ZarzadcaPamieci::pobierzIloscGalaktyk() const{
	return static_cast<int>(galaktyki_.size());
}

bool ZarzadcaPamieci::generujNowaGalaktyke(){
	auto galaktyka = generator_.generujGalaktyke();
	vector< Identyfikator> listaUkladow;
	for(int n = galaktyka->iloscUkladow_; n > 0 ; --n ){
		auto uklad = generator_.generujUklad(galaktyka->pobierzIdentyfikator());
		vector< Identyfikator> listaPlanet;
		for( auto planeta : uklad->planety_ ){
			listaPlanet.push_back(planeta.first);
			struct ZarzadcaPamieci::ObjPlaneta nowaPlaneta = {uklad->pobierzIdentyfikator(),nullptr};
			planety_[planeta.first] = nowaPlaneta;
		}
		listaUkladow.push_back(uklad->pobierzIdentyfikator());
		struct ZarzadcaPamieci::ObjUklad nowyUklad = { galaktyka->pobierzIdentyfikator(), nullptr , listaPlanet };
		ukladySloneczne_[uklad->pobierzIdentyfikator()] = nowyUklad;
		zapiszUkladSloneczny(uklad);
	}
	struct ZarzadcaPamieci::ObjGalakatyka nowaGalaktyka = { nullptr, listaUkladow };
	galaktyki_[galaktyka->pobierzIdentyfikator()] = nowaGalaktyka;
	return true;
}

bool ZarzadcaPamieci::wczytajUkladSloneczny( const Identyfikator& identyfikator ){
	tinyxml2::XMLDocument dokument;
	string plik("save\\uklad\\");
	plik += identyfikator.napis();
	plik += ".xml";
	if(dokument.LoadFile(plik.c_str())!=tinyxml2::XML_NO_ERROR)
		return false;
	tinyxml2::XMLElement* root = dokument.RootElement();
	if(!root)
		return false;
	auto uklad = make_shared<UkladSloneczny>(Identyfikator(),Identyfikator());
	if(!uklad->odczytaj(root->FirstChildElement()))
		return false;
	ukladySloneczne_[uklad->pobierzIdentyfikator()].uklad_ = uklad;
	for( auto planeta : uklad->planety_){
		planety_[planeta.first].planeta_ = planeta.second;
	}
	return true;
}

bool ZarzadcaPamieci::zapiszUkladSloneczny( shared_ptr<UkladSloneczny> uklad ) const{
	tinyxml2::XMLDocument dokument;
	string plik("save\\uklad\\");
	plik += uklad->pobierzIdentyfikator().napis();
	plik += ".xml";

	tinyxml2::XMLElement* root = dokument.NewElement(WEZEL_XML_ROOT);
	if(!uklad->zapisz(root))
		return false;

	dokument.LinkEndChild(root);

	if(!dokument.SaveFile(plik.c_str()))
		return false;
	return true;
}

bool ZarzadcaPamieci::zapisz( tinyxml2::XMLElement* wezel ) const{
	if(!wezel)
		return false;
	tinyxml2::XMLElement* zarzadca =  wezel->GetDocument()->NewElement(WEZEL_XML_ZARZADCA);
	if(!generator_.zapisz(zarzadca))
		return false;
	for( auto galaktyka : galaktyki_ ){
		tinyxml2::XMLElement* wezelGalaktyka = wezel->GetDocument()->NewElement(WEZEL_XML_GALAKTYKA);
		wezelGalaktyka->SetAttribute(ATRYBUT_XML_IDENTYFIKATOR,galaktyka.first.napis().c_str());
		for( auto uklad : galaktyka.second.uklady_ ){
			tinyxml2::XMLElement* wezelUklad = wezel->GetDocument()->NewElement(WEZEL_XML_UKLAD_SLONECZNY);
			wezelUklad->SetAttribute(ATRYBUT_XML_IDENTYFIKATOR,uklad.napis().c_str());
			auto ukladSloneczny = ukladySloneczne_.find(uklad);	
			for( auto planeta : ukladSloneczny->second.planety_ ){
				tinyxml2::XMLElement* wezelPlaneta = wezel->GetDocument()->NewElement(WEZEL_XML_PLANETA);
				wezelPlaneta->SetAttribute(ATRYBUT_XML_IDENTYFIKATOR,planeta.napis().c_str());
				wezelUklad->LinkEndChild(wezelPlaneta);
			}
			if(ukladSloneczny->second.uklad_){
				zapiszUkladSloneczny(ukladSloneczny->second.uklad_);
			}
			wezelGalaktyka->LinkEndChild(wezelUklad);
		}
		zarzadca->LinkEndChild(wezelGalaktyka);
	}
	wezel->LinkEndChild(zarzadca);
	return true;
}

bool ZarzadcaPamieci::odczytaj( tinyxml2::XMLElement* wezel ){
	if(!wezel)
		return false;

	if(!generator_.odczytaj(XmlBO::ZnajdzWezel<NOTHROW>(wezel,WEZEL_XML_GENERATOR_UKLADOW)))
		return false;
	for(tinyxml2::XMLElement* galaktyka = wezel->FirstChildElement(WEZEL_XML_GALAKTYKA) ; galaktyka ; galaktyka = galaktyka->NextSiblingElement(WEZEL_XML_GALAKTYKA)){
		Identyfikator idGalaktyki;
		if(!XmlBO::WczytajAtrybut<NOTHROW>(galaktyka,ATRYBUT_XML_IDENTYFIKATOR,idGalaktyki))
			return false;

		vector<Identyfikator> listUkladow;

		for(tinyxml2::XMLElement* uklad = galaktyka->FirstChildElement(WEZEL_XML_UKLAD_SLONECZNY) ; uklad ; uklad = uklad->NextSiblingElement(WEZEL_XML_UKLAD_SLONECZNY)){
			Identyfikator idUklad;
			if(!XmlBO::WczytajAtrybut<NOTHROW>(uklad,ATRYBUT_XML_IDENTYFIKATOR,idUklad))
				return false;

			vector<Identyfikator> listPlanet;

			for(tinyxml2::XMLElement* planeta = uklad->FirstChildElement(WEZEL_XML_PLANETA) ; planeta ; planeta = planeta->NextSiblingElement(WEZEL_XML_PLANETA)){
				Identyfikator idPlanety;
				if(!XmlBO::WczytajAtrybut<NOTHROW>(planeta,ATRYBUT_XML_IDENTYFIKATOR,idPlanety))
					return false;

				listPlanet.push_back(idPlanety);
				struct ZarzadcaPamieci::ObjPlaneta nowaPlaneta = {idUklad,nullptr};
				planety_[idPlanety] = nowaPlaneta;

			}
			listUkladow.push_back(idUklad);
			struct ZarzadcaPamieci::ObjUklad nowyUklad = { idGalaktyki, nullptr , listPlanet };
			ukladySloneczne_[idUklad] = nowyUklad;
		}

		struct ZarzadcaPamieci::ObjGalakatyka nowaGalaktyka = { nullptr, listUkladow };
		galaktyki_[idGalaktyki] = nowaGalaktyka;
	}

	return true;
}
