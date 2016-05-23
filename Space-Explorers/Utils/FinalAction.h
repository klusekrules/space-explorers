#pragma once
namespace SpEx {
	template <typename F>
	struct FinalAction {
		FinalAction(F f) : clean_{ f } {}
		~FinalAction() { if (enabled_) clean_(); }
		void disable() { enabled_ = false; };
	private:
		F clean_;
		bool enabled_{ true };
	};

	template <typename F>
	SpEx::FinalAction<F> finally(F f) {
		return SpEx::FinalAction<F>(f);
	}
}
