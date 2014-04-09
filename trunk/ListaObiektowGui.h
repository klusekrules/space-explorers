#pragma once
#include <TGUI\TGUI.hpp>
namespace tgui{
	class ListaObiektowGui :
		public Panel
	{
	public:
		static Widget* createWidget(Container*, const std::string& name);

		typedef SharedWidgetPtr<ListaObiektowGui> Ptr;
		ListaObiektowGui();
		ListaObiektowGui(const ListaObiektowGui&);
		~ListaObiektowGui() = default;

		std::size_t addElement(const std::string& name);
		KontrolkaObiektu::Ptr getElement( std::size_t );
		void setSize(float width, float hight);
		bool load(const std::string& configFileFilename);
		virtual ListaObiektowGui* clone();
		void clear();
		const std::string& getLoadedConfigFile() const;
		virtual bool setProperty(std::string property, const std::string& value);
		virtual bool getProperty(std::string property, std::string& value) const;
		virtual std::list< std::pair<std::string, std::string> > getPropertyList() const;
	private:
		void mouseWheelMoved(int delta, int x, int y) override;
		void scrollbarValueChanged(const tgui::Callback& callback);

		virtual void initialize(Container *const container);

		std::string m_LoadedConfigFile;

		Panel::Ptr inside_;
		Scrollbar::Ptr scroll_;
		KontrolkaObiektu::Ptr template_;
		std::vector<KontrolkaObiektu::Ptr> objects_;
		Borders insideBorders_;
		float scrollWidth_;
		float interspace_;

	};
};
