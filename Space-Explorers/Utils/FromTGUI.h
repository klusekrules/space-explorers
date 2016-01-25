#pragma once
#include <TGUI\Layout.hpp>
#include <TGUI\Loading\DataIO.hpp>

#define SET_PROPERTY(property, value) node->propertyValuePairs[property] = std::make_shared<DataIO::ValueNode>(node.get(), value)

#define DESERIALIZE_STRING(property) Deserializer::deserialize(ObjectConverter::Type::String, node->propertyValuePairs[property]->value).getString()

#define REMOVE_CHILD(childName) node->children.erase(std::remove_if(node->children.begin(), node->children.end(), \
                                        [](std::shared_ptr<DataIO::Node> child){ return toLower(child->name) == childName; }), node->children.end());

namespace tgui {
	std::string emitLayout(tgui::Layout2d layout);
	tgui::Layout2d parseLayout(std::string str);
	bool parseBoolean(std::string str);
};
