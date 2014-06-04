#pragma once
#include <TGUI\TGUI.hpp>
#include <memory>
#include "KontrolkaObiektu.h"
#include <mutex>
#include <unordered_map>

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
		void setTransparency(unsigned char transparency);
		void setSize(float width, float hight);
		bool load(const std::string& configFileFilename);
		virtual ListaSurowcowGui* clone();
		const std::string& getLoadedConfigFile() const;
		virtual bool setProperty(std::string property, const std::string& value);
		virtual bool getProperty(std::string property, std::string& value) const;
		virtual std::list< std::pair<std::string, std::string> > getPropertyList() const;

	private:
		virtual void initialize(Container *const container);

		class SurowiecGui :
			public Panel
		{
		public:
			typedef SharedWidgetPtr<SurowiecGui> Ptr;

			SurowiecGui() = default;
			SurowiecGui(const SurowiecGui&);
			virtual ~SurowiecGui() = default;
			void setTransparency(unsigned char transparency);
			void setSize(float width, float hight);
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
		};

		std::string m_LoadedConfigFile_;
		SurowiecGui::Ptr template_;
		std::vector<KontrolkaObiektu::Ptr> objects_;

	};
};
