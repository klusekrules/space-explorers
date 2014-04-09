#pragma once
#include <map>
#include <string>

namespace tgui{
	class Widget;
	class Container;

	class WidgetFactory
	{
	public:

		typedef Widget* (*KreatorWidzetu)(Container*, const std::string&);

		Widget* createWidget(const std::string& id , Container*, const std::string& name);

		bool RejestrujKreatorWidzetu(const std::string& id, KreatorWidzetu funckja);
		
		~WidgetFactory() = default;

		WidgetFactory();

	private:

		typedef std::map<std::string, KreatorWidzetu> Callbacks;

		Callbacks callbacks_; 

		WidgetFactory(const WidgetFactory&) = delete;
		WidgetFactory& operator=(const WidgetFactory&) = delete;
	};

};
