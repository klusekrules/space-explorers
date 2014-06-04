#pragma once
#include <TGUI\TGUI.hpp>
#include <memory>
#include "KontrolkaObiektu.h"
#include <mutex>
#include <unordered_map>

namespace tgui{
	class ListaObiektowGui :
		public Panel
	{
	public:
		static Widget* createWidget(Container*, const std::string& name);

		typedef SharedWidgetPtr<ListaObiektowGui> Ptr;
		ListaObiektowGui();
		ListaObiektowGui(const ListaObiektowGui&);
		virtual ~ListaObiektowGui() = default;
		
		void refresh(bool pos = true);

		void aktualizacjaDanych(const SpEx::Planeta&, const std::vector<STyp::Identyfikator>&,
			const std::unordered_map<STyp::Identyfikator, std::shared_ptr<SpEx::ObiektInfo>, STyp::IdTypeHash >& );

		void setSize(float width, float hight) override;
		void setPosition(float x, float y) override;
		bool load(const std::string& configFileFilename);
		int getTypObiektu() const;
		virtual ListaObiektowGui* clone();
		const std::string& getLoadedConfigFile() const;
		virtual bool setProperty(std::string property, const std::string& value);
		virtual bool getProperty(std::string property, std::string& value) const;
		virtual std::list< std::pair<std::string, std::string> > getPropertyList() const;
	protected:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	private:
		void mouseWheelMoved(int delta, int x, int y) override;
		void scrollbarValueChanged(const tgui::Callback& callback);
		void przeliczPozycjeKontrolek(int delta, bool uaktualnijRozmiar = false);
		void uaktualnijSuwak(float hight, bool pos);
		virtual void initialize(Container *const container);

		std::string m_LoadedConfigFile;

		Scrollbar::Ptr scroll_;
		KontrolkaObiektu::Ptr template_;
		std::vector<KontrolkaObiektu::Ptr> objects_;
		std::shared_ptr<sf::Shader> shader_ = nullptr;
		mutable std::mutex zmianaDanych_;
		Borders insideBorders_;
		float scrollWidth_;
		float interspace_;
		int mnoznikRolki_ = 15;
		int idZdarzeniaBudowy_ = 0;
		int idZdarzeniaBurzenia_ = 0;
		int idZdarzeniaKlikniecia_ = 0;
		int typObiektu_ = 0;
		unsigned int zadanieRozbudowy_ = 0;
		unsigned int zadanieBurzenia_ = 0;
		bool pokazScrollBar_ = false;
		bool kontrolkaAutoSize_ = true;
	};
};
