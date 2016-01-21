#include "FromTGUI.h"
#include <TGUI\Global.hpp>

namespace tgui {
	std::string emitLayout(tgui::Layout2d layout)
	{
		std::string str;
		str += "(";

		if (layout.x.getImpl()->operation == tgui::LayoutImpl::Operation::String)
			str += "\"" + layout.x.getImpl()->stringExpression + "\"";
		else
			str += tgui::to_string(layout.x.getValue());

		str += ", ";

		if (layout.y.getImpl()->operation == tgui::LayoutImpl::Operation::String)
			str += "\"" + layout.y.getImpl()->stringExpression + "\"";
		else
			str += tgui::to_string(layout.y.getValue());

		str += ")";
		return str;
	}
};
