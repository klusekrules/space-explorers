#include "LogListGui.h"
#include "Parser\ParserDokumentXml.h"
#include "Utils\DefinicjeWezlowXML.h"
#include "Parser\XmlBO.h"

namespace tgui {

	LogListGui::LogListGui() 
		: ChatBox()
	{
		m_callback.widgetType = "LogListGui";
	}

	LogListGui::LogListGui(const LogListGui& logList) 		
		: ChatBox{ logList }
	{}

	LogListGui& LogListGui::operator= (const LogListGui& right) {
		if (this != &right){
			ChatBox::operator=(right);
		}

		return *this;
	}

	LogListGui::Ptr LogListGui::copy(LogListGui::ConstPtr logList) {
		if (logList)
			return std::make_shared<LogListGui>(*logList);
		else
			return nullptr;
	}

	bool LogListGui::addMessage(MessageType number, std::string text) {
		if (number >= opisTypowKomunikatow_.size())
			return false;

		auto & widgets = m_lines;
		auto size = widgets.size();
		for (decltype(size) n = 0; n < size; ++n) {
			auto& label = widgets[n];
			MessageType position = powiazaniaKontrolek_[ this->m_newLinesBelowOthers ? n : (size-1) - n ];
			if (position < opisTypowKomunikatow_.size()) {
				label.text.setFillColor(opisTypowKomunikatow_[position].drugiKolor_);
				label.text.setCharacterSize(opisTypowKomunikatow_[position].drugiRozmiarCzcionki_);
			}
		}

		addLine(text, opisTypowKomunikatow_[number].pierwszyKolor_, opisTypowKomunikatow_[number].pierwszyRozmiarCzcionki_);
		powiazaniaKontrolek_.push_back(number);
		if (powiazaniaKontrolek_.size() > m_lines.size()) {
			powiazaniaKontrolek_.erase(powiazaniaKontrolek_.begin());
		}
		return true;
	}

	void LogListGui::clear() {
		removeAllLines();
	}

	bool LogListGui::wczytajOpisyTypowKomunikatow(const std::string &plik) {
		plikOpisowTypowKomunikatow_ = plik;
		if (plikOpisowTypowKomunikatow_.empty()) {
			opisTypowKomunikatow_.clear();
			powiazaniaKontrolek_.clear();
			clear();
			return true;
		}
		else {
			auto dokumentGry = std::make_shared<SPar::ParserDokumentXml>();
			if (!dokumentGry->odczytaj(plikOpisowTypowKomunikatow_.c_str())) {
				return false;
			}
			return XmlBO::ForEach<NOTHROW>(dokumentGry->pobierzElement(WEZEL_XML_ROOT), WEZEL_XML_TYP, XmlBO::OperacjaWezla(
				[&](XmlBO::ElementWezla typ)->bool {
					MessageTypeDescription opis;
					opis.pierwszyKolor_ = XmlBO::WczytajAtrybut<std::string>(typ, ATRYBUT_XML_GLOWNY_KOLOR, std::string());
					opis.drugiKolor_ = XmlBO::WczytajAtrybut<std::string>(typ, ATRYBUT_XML_PODRZEDNY_KOLOR, std::string());
					opis.pierwszyRozmiarCzcionki_ = XmlBO::WczytajAtrybut<unsigned int>(typ, ATRYBUT_XML_GLOWNY_ROZMIAR_CZCIONKI, 0);
					opis.drugiRozmiarCzcionki_ = XmlBO::WczytajAtrybut<unsigned int>(typ, ATRYBUT_XML_PODRZEDNY_ROZMIAR_CZCIONKI, 0);
					if (opis.drugiRozmiarCzcionki_ != 0 && opis.pierwszyRozmiarCzcionki_ != 0) {
						opisTypowKomunikatow_.push_back(opis);
						return true;
					}
					return false;
				}
			));
		}
	}

	const std::string& LogListGui::pobierzPlikOpisowTypowKomunikatow() const {
		return plikOpisowTypowKomunikatow_;
	}
}