#pragma once
#include <TGUI\Loading\DataIO.hpp>
#include "BazowyWidzet.h"
#include "SurowiecGui.h"
#include "KontrolkaObiektu.h"
#include "LogListGui.h"

namespace tgui {
	Widget::Ptr loadBazowyWidzet(std::shared_ptr<DataIO::Node>, Widget::Ptr);
	Widget::Ptr loadSurowiecGui(std::shared_ptr<DataIO::Node>, Widget::Ptr);
	Widget::Ptr loadKontrolkaObiektu(std::shared_ptr<DataIO::Node>, Widget::Ptr);
	Widget::Ptr loadLogListGui(std::shared_ptr<DataIO::Node>, Widget::Ptr);
};