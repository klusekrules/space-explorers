#pragma once
#include <TGUI\TGUI.hpp>
#include <memory>
#include <mutex>
#include <unordered_map>
#include "ObiektInfo.h"

namespace tgui{
	class ListaSurowcowGui :
		public Panel
	{
	public:
		static Widget* createWidget(Container*, const std::string& name);

		typedef SharedWidgetPtr<ListaSurowcowGui> Ptr;

		ListaSurowcowGui() = default;
		ListaSurowcowGui(const ListaSurowcowGui&);
		virtual ~ListaSurowcowGui() = default;
		void ustawDane(const SpEx::Planeta&);
		void setTransparency(unsigned char transparency);
		void setSize(float width, float hight);
		bool load(const std::string& configFileFilename);
		virtual ListaSurowcowGui* clone();
		const std::string& getLoadedConfigFile() const;
		virtual bool setProperty(std::string property, const std::string& value);
		virtual bool getProperty(std::string property, std::string& value) const;
		virtual std::list< std::pair<std::string, std::string> > getPropertyList() const;
	protected:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	private:
		virtual void initialize(Container *const container);
		void refreshPosition();
		class SurowiecGui :
			public Panel
		{
		public:
			typedef SharedWidgetPtr<SurowiecGui> Ptr;

			SurowiecGui() = default;
			SurowiecGui(const SurowiecGui&);
			virtual ~SurowiecGui() = default;
			const STyp::Identyfikator& pobierzIdObiektu() const;
			void ustawDane(const SpEx::Obiekt&);
			void setTransparency(unsigned char transparency);
			void setTextSize(unsigned int size);
			void setTextColor(sf::Color color);
			bool load(const std::string& configFileFilename);
			virtual SurowiecGui* clone();
			const std::string& getLoadedConfigFile() const;
			virtual bool setProperty(std::string property, const std::string& value);
			virtual bool getProperty(std::string property, std::string& value) const;
			virtual std::list< std::pair<std::string, std::string> > getPropertyList() const;
		private:

			virtual void initialize(Container *const container);

			std::string m_LoadedConfigFile_;
			Label::Ptr tekst_;
			STyp::Identyfikator idObiektu_;
		};

		mutable std::mutex zmianaDanych_;
		std::string m_LoadedConfigFile_;
		SurowiecGui::Ptr template_;
		std::vector<SurowiecGui::Ptr> objects_;

	};
};
