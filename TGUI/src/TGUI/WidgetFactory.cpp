
#include <TGUI\TGUI.hpp>

namespace tgui{

	WidgetFactory& WidgetFactory::getInstance(){
		static WidgetFactory factory;
		return factory;
	}

	Widget* WidgetFactory::createWidget(const std::string& id, Container* kontener, const std::string& name){
		auto iter = callbacks_.find(id);
		if (iter == callbacks_.end())
			return nullptr;
		return iter->second(kontener, name);
	}

	bool WidgetFactory::RejestrujKreatorWidzetu(const std::string& id, KreatorWidzetu funckja){
		if (callbacks_.find(id) != callbacks_.end())
			return false;
		callbacks_.insert(std::make_pair(id, funckja));
		return true;
	}

	WidgetFactory::WidgetFactory()
	{
		callbacks_.insert(std::make_pair("tab", Tab::createWidget));
		callbacks_.insert(std::make_pair("grid", Grid::createWidget));
		callbacks_.insert(std::make_pair("panel", Panel::createWidget));
		callbacks_.insert(std::make_pair("label", Label::createWidget));
		callbacks_.insert(std::make_pair("button", Button::createWidget));
		callbacks_.insert(std::make_pair("slider", Slider::createWidget));
		callbacks_.insert(std::make_pair("picture", Picture::createWidget));
		callbacks_.insert(std::make_pair("listbox", ListBox::createWidget));
		callbacks_.insert(std::make_pair("editbox", EditBox::createWidget));
		callbacks_.insert(std::make_pair("textbox", TextBox::createWidget));
		callbacks_.insert(std::make_pair("chatbox", ChatBox::createWidget));
		callbacks_.insert(std::make_pair("menubar", MenuBar::createWidget));
		callbacks_.insert(std::make_pair("checkbox", Checkbox::createWidget));
		callbacks_.insert(std::make_pair("combobox", ComboBox::createWidget));
		callbacks_.insert(std::make_pair("slider2d", Slider2d::createWidget));
		callbacks_.insert(std::make_pair("scrollbar", Scrollbar::createWidget));
		callbacks_.insert(std::make_pair("loadingbar", LoadingBar::createWidget));
		callbacks_.insert(std::make_pair("spinbutton", SpinButton::createWidget));
		callbacks_.insert(std::make_pair("radiobutton", RadioButton::createWidget));
		callbacks_.insert(std::make_pair("childwindow", ChildWindow::createWidget));
		callbacks_.insert(std::make_pair("spritesheet", SpriteSheet::createWidget));
		callbacks_.insert(std::make_pair("animatedpicture", AnimatedPicture::createWidget));
		callbacks_.insert(std::make_pair("kontrolkaobiektu", KontrolkaObiektu::createWidget));
	}

}
