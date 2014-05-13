#pragma once
#include <TGUI\TGUI.hpp>
#include <memory>
#include "KontrolkaObiektu.h"

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
		
		void refresh();

		std::size_t addElement(const std::string& name);
		KontrolkaObiektu::Ptr getElement( std::size_t );
		void setSize(float width, float hight) override;
		void setPosition(float x, float y) override;
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
		void przeliczPozycjeKontrolek(int delta, bool uaktualnijRozmiar = false);
		void uaktualnijSuwak( float hight );
		virtual void initialize(Container *const container);

		std::string m_LoadedConfigFile;

		Scrollbar::Ptr scroll_;
		KontrolkaObiektu::Ptr template_;
		std::vector<KontrolkaObiektu::Ptr> objects_;
		std::shared_ptr<sf::Shader> shader_ = nullptr;

		Borders insideBorders_;
		float scrollWidth_;
		float interspace_;
		int mnoznikRolki_ = 15;
		int idZdarzeniaBudowy_ = 0;
		int idZdarzeniaBurzenia_ = 0;
		int idZdarzeniaKlikniecia_ = 0;
		unsigned int zadanieRozbudowy_ = 0;
		unsigned int zadanieBurzenia_ = 0;
		bool pokazScrollBar_ = false;
		bool kontrolkaAutoSize_ = true;
	};
};
