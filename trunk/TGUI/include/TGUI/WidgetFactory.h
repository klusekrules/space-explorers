#pragma once
#include <TGUI\Widget.hpp>

namespace tgui{

	class WidgetFactory
	{
	public:

		typedef Widget* (*KreatorWidzetu)(Container*, const std::string&);

		Widget* createWidget(const std::string& id , Container*, const std::string& name);

		bool RejestrujKreatorWidzetu(const std::string& id, KreatorWidzetu funckja);
		
		~WidgetFactory() = default;
		static WidgetFactory& getInstance();
	private:

		typedef std::map<std::string, KreatorWidzetu> Callbacks;

		Callbacks callbacks_; 

		WidgetFactory();
		WidgetFactory(const WidgetFactory&) = delete;
		WidgetFactory& operator=(const WidgetFactory&) = delete;
	};

};
