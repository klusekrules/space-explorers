#pragma once
#include <TGUI\Loading\DataIO.hpp>
#include "BazowyWidzet.h"
#include "SurowiecGui.h"
#include "KontrolkaObiektu.h"
#include "LogListGui.h"
#include "ListaSurowcowGui.h"
#include "ListaObiektowGui.h"

namespace tgui {
	std::shared_ptr<DataIO::Node> saveBazowyWidzet(BazowyWidzet::Ptr widget);
	std::shared_ptr<DataIO::Node> saveSurowiecGui(SurowiecGui::Ptr widget);
	std::shared_ptr<DataIO::Node> saveKontrolkaObiektu(KontrolkaObiektu::Ptr widget);
	std::shared_ptr<DataIO::Node> saveLogListGui(LogListGui::Ptr widget);
	std::shared_ptr<DataIO::Node> saveListaSurowcowGui(ListaSurowcowGui::Ptr widget);
	std::shared_ptr<DataIO::Node> saveListaObiektowGui(ListaObiektowGui::Ptr widget);
};