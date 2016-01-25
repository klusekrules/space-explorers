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

	bool parseBoolean(std::string str)
	{
		str = tgui::toLower(str);
		if (str == "true" || str == "yes" || str == "on" || str == "1")
			return true;
		else if (str == "false" || str == "no" || str == "off" || str == "0")
			return false;
		else
			throw tgui::Exception{ "Failed to parse boolean in '" + str + "'" };
	}

	tgui::Layout2d parseLayout(std::string str)
	{
		if (str.empty())
			throw tgui::Exception{ "Failed to parse layout. String was empty." };

		// Check if the layout is an (x, y) vector or a quoted string
		if ((str.front() == '(') && (str.back() == ')'))
		{
			str = str.substr(1, str.length() - 2);
			if (str.empty())
				return{ 0, 0 };

			tgui::Layout x;
			tgui::Layout y;

			auto commaPos = str.find(',');
			if (commaPos == std::string::npos)
				throw tgui::Exception{ "Failed to parse layout '" + str + "'. Expected numbers separated with a comma." };

			// Check if the first part is quoted
			auto openingQuotePos = str.find('"');
			if (commaPos > openingQuotePos)
			{
				auto closingQuotePos = str.find('"', openingQuotePos + 1);
				if (closingQuotePos == std::string::npos)
					throw tgui::Exception{ "Failed to parse layout '" + str + "'. Expected closing quote." };

				// Make sure we didn't select a quote inside the string
				if (commaPos < closingQuotePos)
				{
					commaPos = str.find(',', closingQuotePos + 1);
					if (commaPos == std::string::npos)
						throw tgui::Exception{ "Failed to parse layout '" + str + "'. Expected numbers separated with a comma." };
				}

				x = { str.substr(openingQuotePos + 1, closingQuotePos - openingQuotePos - 1) };
			}
			else // Normal value
				x = { tgui::stof(tgui::trim(str.substr(0, commaPos))) };

			// Check if the second part is quoted
			openingQuotePos = str.find('"', commaPos + 1);
			if (openingQuotePos != std::string::npos)
			{
				auto closingQuotePos = str.find('"', openingQuotePos + 1);
				if (closingQuotePos == std::string::npos)
					throw tgui::Exception{ "Failed to parse layout '" + str + "'. Expected closing quote." };

				y = { str.substr(openingQuotePos + 1, closingQuotePos - openingQuotePos - 1) };
			}
			else // Normal value
				y = { tgui::stof(tgui::trim(str.substr(commaPos + 1))) };

			return{ x, y };
		}
		else if ((str.front() == '"') && (str.back() == '"'))
		{
			str = str.substr(1, str.length() - 2);
			return{ str };
		}
		else
			throw tgui::Exception{ "Failed to parse layout '" + str + "'. Expected (x,y) or a quoted layout string." };
	}
};
