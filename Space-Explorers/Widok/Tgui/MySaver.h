#pragma once
#include <TGUI\Loading\DataIO.hpp>
#include "BazowyWidzet.h"
#include "SurowiecGui.h"
#include "KontrolkaObiektu.h"
#include "LogListGui.h"

namespace tgui {
	std::shared_ptr<DataIO::Node> saveBazowyWidzet(BazowyWidzet::Ptr widget);
	std::shared_ptr<DataIO::Node> saveSurowiecGui(SurowiecGui::Ptr widget);
	std::shared_ptr<DataIO::Node> saveKontrolkaObiektu(KontrolkaObiektu::Ptr widget);
	std::shared_ptr<DataIO::Node> saveLogListGui(LogListGui::Ptr widget);
};