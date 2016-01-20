#include "LogListGui.h"

namespace tgui {

	LogListGui::LogListGui() :
		ChatBox()
	{
	}

	LogListGui::LogListGui(const LogListGui& logList) :
		ChatBox{ logList }
	{
	}

	LogListGui& LogListGui::operator= (const LogListGui& right)
	{
		if (this != &right)
		{
			ChatBox::operator=(right);
		}

		return *this;
	}

	LogListGui::Ptr LogListGui::copy(LogListGui::ConstPtr logList)
	{
		if (logList)
			return std::make_shared<LogListGui>(*logList);
		else
			return nullptr;
	}

	bool LogListGui::addMessage(MessageType number, std::string text) {
		if (number >= opisTypowKomunikatow_.size())
			return false;

		auto & widgets = m_panel->getWidgets();
		auto size = widgets.size();
		for (decltype(size) n = 0; n < size; ++n) {
			auto label = std::static_pointer_cast<Label>(widgets[n]);
			MessageType position = powiazaniaKontrolek_[n];
			if (position < opisTypowKomunikatow_.size()){
				label->setTextColor(opisTypowKomunikatow_[position].drugiKolor_);
				label->setTextSize(opisTypowKomunikatow_[position].drugiRozmiarCzcionki_);
			}
		}

		addLine(text, opisTypowKomunikatow_[number].pierwszyKolor_, opisTypowKomunikatow_[number].pierwszyRozmiarCzcionki_);
		powiazaniaKontrolek_.push_back(number);
		if (powiazaniaKontrolek_.size() > m_panel->getWidgets().size()) {
			powiazaniaKontrolek_.erase(powiazaniaKontrolek_.begin());
		}
		return true;
	}

	void LogListGui::clear() {
		m_panel->removeAllWidgets();
	}
}