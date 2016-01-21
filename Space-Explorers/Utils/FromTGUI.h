#pragma once
#include <TGUI\Layout.hpp>
#include <TGUI\Loading\DataIO.hpp>

#define SET_PROPERTY(property, value) node->propertyValuePairs[property] = std::make_shared<DataIO::ValueNode>(node.get(), value)

namespace tgui {
	std::string emitLayout(tgui::Layout2d layout);
};
