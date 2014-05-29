#include "ListaObiektowGui.h"

#include <SFML\OpenGL.hpp>
namespace tgui {

	Widget* ListaObiektowGui::createWidget(Container* container, const std::string& name){
		return ListaObiektowGui::Ptr(*container, name).get();
	}

	void ListaObiektowGui::aktualizacjaDanych(const SpEx::Planeta& planeta, const std::vector<STyp::Identyfikator>& listaId,
		const std::unordered_map<STyp::Identyfikator, std::shared_ptr<SpEx::ObiektInfo>, STyp::IdTypeHash >& listaObj){
		if (objects_.size() == listaId.size()){ // Je�eli ilo�� kontrolek jest taka sama, jak ilo�� obiekt�w to tylko aktualizujemy dane.
			int n = 0;
			for (auto element : objects_)
				element->ustawDane(*listaObj.at(listaId[n++]), planeta);
		}else{

			// Usuni�cie niepotrzebnych okien
			for (auto iter = objects_.begin(); iter != objects_.end();){
				if (std::find(listaId.begin(), listaId.end(), (*iter)->pobierzIdObiektu()) != listaId.end()){
					++iter;
				}else{
					std::lock_guard<std::mutex> lock(zmianaDanych_);
					this->remove(*iter);
					iter= objects_.erase(iter);				
				}
			}

			// Dodanie brakuj�cych element�w oraz uaktualnienie obecnych.
			auto iter = objects_.begin();
			for (auto &id : listaId){
				if (iter == objects_.end() || (*iter)->pobierzIdObiektu() != id){
					std::lock_guard<std::mutex> lock(zmianaDanych_);
					auto widget = this->copy(template_, listaObj.at(id)->pobierzNazwe()());
					widget->show();
					iter = objects_.emplace(iter, widget);
					if (shader_)
						(*iter)->ustawShader(shader_.get());					
				}
				if (iter != objects_.end()){
					(*iter)->ustawDane(*listaObj.at(id), planeta);
					++iter;
				}
			}
		}
		refresh(false);
	}
	
	int ListaObiektowGui::getTypObiektu() const{
		return typObiektu_;
	}

	void ListaObiektowGui::refresh(bool pos){
		auto size = Panel::getSize();
		uaktualnijSuwak(size.y, pos);
		przeliczPozycjeKontrolek(scroll_->getValue(), true);
	}
	
	ListaObiektowGui::ListaObiektowGui()
	{
		scrollWidth_ = 20;
	}

	ListaObiektowGui::ListaObiektowGui(const ListaObiektowGui& o)
		: Panel(o)
	{
		template_ = this->get<KontrolkaObiektu>("Szablon");
		scroll_ = this->get<Scrollbar>("PasekPrzewijania");
		for (auto e : o.objects_){
			std::string nazwa;
			if (o.getWidgetName(e, nazwa)){
				if (!nazwa.empty()){
					objects_.push_back(this->get<KontrolkaObiektu>(nazwa));
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
			else if (property == "borders")
			{
				extractBorders(value, insideBorders_);
			}
			else if (property == "scrollwidth")
			{
				scrollWidth_ = std::strtof(value.c_str(), nullptr);
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
	
	void ListaObiektowGui::scrollbarValueChanged(const tgui::Callback& callback){
		przeliczPozycjeKontrolek(callback.value);
	}

	void ListaObiektowGui::przeliczPozycjeKontrolek(int delta, bool uaktualnijRozmiar){
		int t = 1;
		auto size = template_->getSize();
		auto upMargin = t*(size.y + interspace_) + insideBorders_.top - 50;
		auto downMargin = (t + 1)*(size.y + interspace_) + insideBorders_.top + 50;
		for (auto e : objects_){
			if (uaktualnijRozmiar)
				e->setSize(size.x, size.y);
			auto hight = t*(size.y + interspace_) + insideBorders_.top - delta;
			e->setPosition(static_cast<float>(insideBorders_.left), hight);
			t++;
		}
	}

	void ListaObiektowGui::uaktualnijSuwak(float hight, bool pos){
		auto size = template_->getSize();
		float insideHight = (objects_.size() + 2)*(size.y + interspace_) + insideBorders_.top + insideBorders_.bottom - interspace_;

		if (insideHight <= hight){
			scroll_->setLowValue(0);
			scroll_->setMaximum(0);
			scroll_->setValue(0);
		}
		else{
			scroll_->setLowValue(static_cast<unsigned int>(hight));
			scroll_->setMaximum(static_cast<unsigned int>(insideHight + 1.f));
			if (pos)
				scroll_->setValue(0);
			else{
				if (scroll_->getValue() > scroll_->getMaximum())
					scroll_->setValue(0);
			}
		}
	}

	void ListaObiektowGui::setPosition(float x, float y){
		Panel::setPosition(x,y);
		if (shader_){
			auto size = template_->getSize();
			auto pSize = Panel::getSize();
			auto pozycja = Panel::getPosition();
			GLint viewport[4];
			GLfloat upBorder, downBorder;
			glGetIntegerv(GL_VIEWPORT, viewport);
			downBorder = (float)viewport[3] - (pozycja.y + pSize.y);
			upBorder = (float)viewport[3] - pozycja.y;
			shader_->setParameter("zakres", size.y);
			shader_->setParameter("upMargin", upBorder - size.y);
			shader_->setParameter("downMargin", downBorder + size.y);
		}
	}

	void ListaObiektowGui::setSize(float width, float hight){
		Panel::setSize(width, hight);
		if (pokazScrollBar_){
			auto size = scroll_->getSize();
			scroll_->setPosition(width - size.x, 0);
			scroll_->setSize(size.x, hight);
			if (kontrolkaAutoSize_)
				template_->setSize(width - (insideBorders_.left + insideBorders_.right + size.x ), hight);
		}
		else{
			if (kontrolkaAutoSize_)
				template_->setSize(width - (insideBorders_.left + insideBorders_.right), hight);
		}
		
		przeliczPozycjeKontrolek(0,true);
		uaktualnijSuwak(hight,false);
		if (shader_){
			auto size = template_->getSize();
			auto pozycja = Panel::getPosition();
			GLint viewport[4];
			GLfloat upBorder, downBorder;
			glGetIntegerv(GL_VIEWPORT, viewport);
			downBorder = (float)viewport[3] - (pozycja.y + hight);
			upBorder = (float)viewport[3] - pozycja.y;
			shader_->setParameter("zakres", size.y);
			shader_->setParameter("upMargin", upBorder - size.y);
			shader_->setParameter("downMargin", downBorder + size.y);
		}
	}

	void ListaObiektowGui::initialize(Container *const container){
		Panel::setGlobalFont(container->getGlobalFont());
		if (sf::Shader::isAvailable()){
			shader_ = std::make_shared<sf::Shader>();
			shader_->loadFromFile("resource\\simple.frag", sf::Shader::Type::Fragment);
			shader_->setParameter("texture", sf::Shader::CurrentTexture);
		}
		template_ = KontrolkaObiektu::Ptr(*this, "Szablon");
		template_->hide();

		scroll_ = Scrollbar::Ptr(*this, "PasekPrzewijania");
		scroll_->bindCallbackEx(std::bind(&ListaObiektowGui::scrollbarValueChanged, this, std::placeholders::_1), tgui::Scrollbar::ValueChanged);
		if (pokazScrollBar_)
			scroll_->show();
		else
			scroll_->hide();

		setSize(430.f, 350.f);
	}

	void ListaObiektowGui::mouseWheelMoved(int delta, int x, int y){
		scroll_->mouseWheelMoved(delta*mnoznikRolki_,x,y);
	}

	bool ListaObiektowGui::setProperty(std::string property, const std::string& value){
		if (property == "mnoznikrolki"){
			mnoznikRolki_ = std::strtol(value.c_str(), nullptr, 10);
		}
		else if (property == "typobiektu"){
			typObiektu_ = std::strtol(value.c_str(), nullptr, 10);
		}
		else if (property == "idzdarzeniabudowy"){
			template_->setProperty(property, value);
		}
		else if (property == "idzdarzeniaburzenia"){
			template_->setProperty(property, value);
		}
		else if (property == "idzdarzeniaklikniecia"){
			template_->setProperty(property, value);
		}
		else if(property == "scrollbarpokaz"){
			if ((value == "true") || (value == "True"))
				pokazScrollBar_ = true;
			else if ((value == "false") || (value == "False"))
				pokazScrollBar_ = false;
			else
				TGUI_OUTPUT("TGUI error: Failed to parse 'Enabled' property.");
			
			if (pokazScrollBar_)
				scroll_->show();
			else
				scroll_->hide();
		}
		else if (property == "kontrolkaautosize"){
			if ((value == "true") || (value == "True"))
				kontrolkaAutoSize_ = true;
			else if ((value == "false") || (value == "False"))
				kontrolkaAutoSize_ = false;
			else
				TGUI_OUTPUT("TGUI error: Failed to parse 'Enabled' property.");
		}
		else if (property == "scrollbarszerokosc"){
			auto var = std::strtof(value.c_str(), nullptr);
			auto size = scroll_->getSize();
			scroll_->setSize(var,size.y);
		}
		else if (property == "configfile"){
			return load(value);
		}
		else
			return Panel::setProperty(property, value);
		return true;
	}

	bool ListaObiektowGui::getProperty(std::string property, std::string& value) const{
		if (property == "mnoznikrolki"){
			value = std::to_string(mnoznikRolki_);
		}
		else if (property == "typobiektu"){
			value = std::to_string(typObiektu_);
		}
		else if (property == "scrollbarpokaz"){
			value = std::string( pokazScrollBar_ ? "true" : "false" );
		}
		else if (property == "scrollbarszerokosc"){
			value = std::to_string(scroll_->getSize().x);
		}
		else if (property == "kontrolkaautosize"){
			value = std::string(kontrolkaAutoSize_ ? "true" : "false");
		}
		else if (property == "ConfigFile"){
			value = m_LoadedConfigFile;
		}
		else if (property == "IdZdarzeniaBudowy"){
			template_->getProperty(property, value);
		}
		else if (property == "IdZdarzeniaBurzenia"){
			template_->getProperty(property, value);
		}
		else if (property == "IdZdarzeniaKlikniecia"){
			template_->getProperty(property, value);
		}
		else
			return Panel::getProperty(property, value);
		return true;
	}

	std::list< std::pair<std::string, std::string> > ListaObiektowGui::getPropertyList() const{
		auto list = Panel::getPropertyList();
		list.push_back(std::pair<std::string, std::string>("ConfigFile", "string"));
		list.push_back(std::pair<std::string, std::string>("mnoznikrolki", "int"));
		list.push_back(std::pair<std::string, std::string>("scrollbarpokaz", "bool"));
		list.push_back(std::pair<std::string, std::string>("scrollbarszerokosc", "float"));
		list.push_back(std::pair<std::string, std::string>("kontrolkaautosize", "bool"));
		return list;
	}

	void ListaObiektowGui::draw(sf::RenderTarget& target, sf::RenderStates states) const{
		std::lock_guard<std::mutex> lock(zmianaDanych_);
		Panel::draw(target, states);
	}

};
