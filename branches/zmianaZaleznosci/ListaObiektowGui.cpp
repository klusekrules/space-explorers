#include "ListaObiektowGui.h"

namespace tgui {

	void ListaObiektowGui::scrollbarValueChanged(const tgui::Callback& callback)
	{
		//template_->setPosition(0, -callback.value);
		inside_->setPosition(0, static_cast<float>(-callback.value));
	}

	Widget* ListaObiektowGui::createWidget(Container* container, const std::string& name){
		return ListaObiektowGui::Ptr(*container, name).get();
	}

	std::size_t ListaObiektowGui::addElement( const std::string& name ){
		auto widget = inside_->copy(template_, name);
		widget->show();
		objects_.push_back(widget);
		sf::Vector2f temp = getSize();
		setSize(temp.x, temp.y);
		return objects_.size() - 1;
	}

	KontrolkaObiektu::Ptr ListaObiektowGui::getElement(std::size_t pos){
		return objects_.at(pos);
	}

	ListaObiektowGui::ListaObiektowGui()
	{
		scrollWidth_ = 20;
	}

	ListaObiektowGui::ListaObiektowGui(const ListaObiektowGui& o)
		: Panel(o)
	{
		inside_ = this->get<Panel>("PanelWewnetrzny");
		template_ = this->get<KontrolkaObiektu>("Szablon");
		scroll_ = this->get<Scrollbar>("PasekPrzewijania");
		for (auto e : o.objects_ ){
			std::string nazwa;
			if (o.inside_->getWidgetName(e, nazwa)){
				if (!nazwa.empty()){
					objects_.push_back(inside_->get<KontrolkaObiektu>(nazwa));
				}
			}
		}
	}

	ListaObiektowGui* ListaObiektowGui::clone(){
		return new ListaObiektowGui(*this);
	}

	bool ListaObiektowGui::load(const std::string& configFileFilename){
		// Don't continue when the config file was empty
		if (configFileFilename.empty())
			return true;

		m_LoadedConfigFile = getResourcePath() + configFileFilename;

		// Open the config file
		ConfigFile configFile;
		if (!configFile.open(m_LoadedConfigFile))
		{
			TGUI_OUTPUT("TGUI error: Failed to open " + m_LoadedConfigFile + ".");
			return false;
		}

		// Read the properties and their values (as strings)
		std::vector<std::string> properties;
		std::vector<std::string> values;
		if (!configFile.read("ListaObiektowGui", properties, values))
		{
			TGUI_OUTPUT("TGUI error: Failed to parse " + m_LoadedConfigFile + ".");
			return false;
		}

		// Close the config file
		configFile.close();

		// Find the folder that contains the config file
		std::string configFileFolder = "";
		std::string::size_type slashPos = m_LoadedConfigFile.find_last_of("/\\");
		if (slashPos != std::string::npos)
			configFileFolder = m_LoadedConfigFile.substr(0, slashPos + 1);


		// Handle the read properties
		for (unsigned int i = 0; i < properties.size(); ++i)
		{
			std::string property = properties[i];
			std::string value = values[i];
			//setTextColor(extractColor(value));
			if (property == "templateconfig")
			{
				template_->load(configFileFolder + value);
			}
			else if (property == "scrollconfig")
			{
				scroll_->load(configFileFolder + value);
			}
			else if(property == "borders")
			{
				extractBorders(value, insideBorders_);
			}
			else if (property == "scrollwidth")
			{
				scrollWidth_ = std::strtof(value.c_str(),nullptr);
			}
			else if (property == "interspace")
			{
				interspace_ = std::strtof(value.c_str(), nullptr);
			}
			else
				TGUI_OUTPUT("TGUI warning: Unrecognized property '" + property + "' in section KontrolkaObiektu in " + m_LoadedConfigFile + ".");
		}
		sf::Vector2f temp = getSize();
		setSize(temp.x, temp.y);
		return true;
	}

	const std::string& ListaObiektowGui::getLoadedConfigFile() const{
		return m_LoadedConfigFile;
	}

	void ListaObiektowGui::setSize(float width, float hight){
		Panel::setSize(width, hight);
		template_->setSize(width - (scrollWidth_ + insideBorders_.left + insideBorders_.right), hight);
		int t = 0;
		auto size = template_->getSize();
		for (auto e : objects_){
			e->setSize(size.x, size.y);
			e->setPosition(static_cast<float>(insideBorders_.left), t*(size.y + interspace_) + insideBorders_.top);
			t++;
		}
		float insideHight = t*(size.y + interspace_) + insideBorders_.top + insideBorders_.bottom - interspace_;

		if (insideHight < 0)
			inside_->setSize(width - scrollWidth_, 0);
		else
			inside_->setSize(width - scrollWidth_, insideHight);

		if (insideHight <= hight){
			scroll_->setLowValue(0);
			scroll_->setMaximum(0);
		}
		else{
			scroll_->setLowValue(static_cast<unsigned int>(hight));
			scroll_->setMaximum(static_cast<unsigned int>(insideHight + 1.f));
		}

		scroll_->setPosition(width - scrollWidth_, 0);
		scroll_->setSize(scrollWidth_, hight);
	}

	void ListaObiektowGui::initialize(Container *const container){
		Panel::setGlobalFont(container->getGlobalFont());

		inside_ = Panel::Ptr(*this, "PanelWewnetrzny");

		template_ = KontrolkaObiektu::Ptr(*inside_.get(), "Szablon");
		template_->hide();

		scroll_ = Scrollbar::Ptr(*this, "PasekPrzewijania");
		scroll_->bindCallbackEx(std::bind(&ListaObiektowGui::scrollbarValueChanged, this, std::placeholders::_1), tgui::Scrollbar::ValueChanged);
		
		setSize(430.f, 350.f);
	}

	bool ListaObiektowGui::setProperty(std::string property, const std::string& value){
		if (property == "configfile"){
			return load(value);
		}
		else
			return Panel::setProperty(property, value);
	}

	bool ListaObiektowGui::getProperty(std::string property, std::string& value) const{
		if (property == "ConfigFile"){
			value = m_LoadedConfigFile;
			return true;
		}
		else
			return Panel::getProperty(property, value);
	}

	std::list< std::pair<std::string, std::string> > ListaObiektowGui::getPropertyList() const{
		auto list = Panel::getPropertyList();
		list.push_back(std::pair<std::string, std::string>("ConfigFile", "string"));
		return list;
	}

};
