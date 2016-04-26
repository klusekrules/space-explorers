#pragma once
#include "Watek.h"
#include "Narzedzia\Singleton.h"
#include <list>
#include <vector>
#include <memory>

namespace SpEx {
	class ObserwatorWatkow
		: public Watek,
		public se::Singleton<ObserwatorWatkow>
	{
		friend class se::Singleton<ObserwatorWatkow>;
	public:

		template < class T, typename... Args>
		static std::shared_ptr<T> make_thread(Args&&... args) {
			auto ptr = std::make_shared<T>(std::move(args)...);
			ObserwatorWatkow::pobierzInstancje().dodajWatek(std::static_pointer_cast<Watek>(ptr));
			return ptr;
		}
		
	private:
		ObserwatorWatkow();
		virtual ~ObserwatorWatkow() = default;
		void wykonuj() override;
		void dodajWatek( std::shared_ptr<Watek> &watek);
		std::list<std::shared_ptr<Watek>> listaWatkow_;
		std::vector<std::shared_ptr<Watek>> doUsuniecia_;
		std::mutex synchronize_;
	};
}
