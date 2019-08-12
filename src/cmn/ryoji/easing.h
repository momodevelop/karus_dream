#ifndef __RYOJI_EASING_H__
#define __RYOJI_EASING_H__

#include <cmath>
#include <type_traits>
#include "fixed_floats.h"


namespace ryoji::easing {

	namespace _d {

		RYOJI_MAKE_CONSTEXPR_FP_NAMED(HALF_PI, 1.57079632725)
		RYOJI_MAKE_CONSTEXPR_FP_NAMED(PI, 3.1415926545)
		RYOJI_MAKE_CONSTEXPR_FP(1, 0)
		RYOJI_MAKE_CONSTEXPR_FP(2, 0)
		RYOJI_MAKE_CONSTEXPR_FP(4, 0)
		RYOJI_MAKE_CONSTEXPR_FP(6, 0)
		RYOJI_MAKE_CONSTEXPR_FP(7, 0)
		RYOJI_MAKE_CONSTEXPR_FP(8, 0)
		RYOJI_MAKE_CONSTEXPR_FP(9, 0)
		RYOJI_MAKE_CONSTEXPR_FP(16, 0)
		RYOJI_MAKE_CONSTEXPR_FP(255, 0)
		RYOJI_MAKE_CONSTEXPR_FP(510, 0)
		RYOJI_MAKE_CONSTEXPR_FP(0, 75)
		RYOJI_MAKE_CONSTEXPR_FP(2, 7)
		RYOJI_MAKE_CONSTEXPR_FP(1, 7)
		RYOJI_MAKE_CONSTEXPR_FP(2, 5)
		RYOJI_MAKE_CONSTEXPR_FP(4, 5)
		RYOJI_MAKE_CONSTEXPR_FP(0, 45)
		RYOJI_MAKE_CONSTEXPR_FP(0, 55)
		RYOJI_MAKE_CONSTEXPR_FP(3, 5)
		RYOJI_MAKE_CONSTEXPR_FP(0, 5)
	}

	template<typename T> static T easeInSine(T t) noexcept {
		static_assert(std::is_floating_point_v<T>);
		return sin(_d::HALF_PI<T> * t);
	}


	template<typename T> static T easeOutSine(T t) noexcept {
		static_assert(std::is_floating_point_v<T>);
		return _d::_1p0<T> + sin(_d::HALF_PI<T> * (--t));
	}


	template<typename T> static T easeInOutSine(T t) noexcept {
		static_assert(std::is_floating_point_v<T>);
		return _d::_0p5<T> * (_d::_1p0<T> + sin(_d::PI<T> * (t - _d::_0p5<T>)));
	}

	template<typename T> static T easeInQuad(T t) noexcept {
		static_assert(std::is_floating_point_v<T>);
		return t * t;
	}

	template<typename T> static T easeOutQuad(T t) noexcept {
		static_assert(std::is_floating_point_v<T>);
		return t * (_d::_2p0<T> - t);
	}

	template<typename T> static T easeInOutQuad(T t) noexcept {
		static_assert(std::is_floating_point_v<T>);
		return t < _d::_0p5<T> ? _d::_2p0<T> * t * t : t * (_d::_4p0<T> - _d::_2p0<T> * t) - _d::_1p0<T>;
	}

	template<typename T> static T easeInCubic(T t) noexcept {
		static_assert(std::is_floating_point_v<T>);
		return t * t * t;
	}

	template<typename T> static T easeOutCubic(T t) noexcept {
		static_assert(std::is_floating_point_v<T>);
		return _d::_1p0<T> + (--t) * t * t;
	}

	template<typename T> static T easeInOutCubic(T t) noexcept {
		static_assert(std::is_floating_point_v<T>);
		return t < _d::_0p5<T> ? _d::_4p0<T> * t * t * t : _d::_1p0<T> + (--t) * (_d::_2p0<T> * (--t)) * (_d::_2p0<T> * t);
	}

	template<typename T> static T easeInQuart(T t) noexcept {
		static_assert(std::is_floating_point_v<T>);
		t *= t;
		return t * t;
	}

	template<typename T> static T easeOutQuart(T t) noexcept {
		static_assert(std::is_floating_point_v<T>);
		t = (--t) * t;
		return _d::_1p0<T> - t * t;
	}

	template<typename T> static T easeInOutQuart(T t) noexcept {
		static_assert(std::is_floating_point_v<T>);
		if (t < _d::_0p5<T>) {
			t *= t;
			return _d::_8p0<T> * t * t;
		}
		else {
			t = (--t) * t;
			return _d::_1p0<T> - _d::_8p0<T> * t * t;
		}
	}

	template<typename T> static T easeInQuint(T t) noexcept {
		static_assert(std::is_floating_point_v<T>);
		T t2 = t * t;
		return t * t2 * t2;
	}

	template<typename T> static T easeOutQuint(T t) noexcept {
		static_assert(std::is_floating_point_v<T>);
		T t2 = (--t) * t;
		return _d::_1p0<T> + t * t2 * t2;
	}

	template<typename T> static T easeInOutQuint(T t) noexcept {
		static_assert(std::is_floating_point_v<T>);
		T t2;
		if (t < _d::_0p5<T>) {
			t2 = t * t;
			return _d::_16p0<T> * t * t2 * t2;
		}
		else {
			t2 = (--t) * t;
			return _d::_1p0<T> + _d::_16p0<T> * t * t2 * t2;
		}
	}

	template<typename T> static T easeInExpo(T t) noexcept {
		static_assert(std::is_floating_point_v<T>);
		return (pow(_d::_2p0<T>, _d::_8p0<T> * t) - _d::_1p0<T>) / _d::_255p0<T>;
	}

	template<typename T> static T easeOutExpo(T t) noexcept {
		static_assert(std::is_floating_point_v<T>);
		return _d::_1p0<T> - pow(_d::_2p0<T>, -_d::_8p0<T> * t);
	}

	template<typename T> static T easeInOutExpo(T t) noexcept {
		static_assert(std::is_floating_point_v<T>);
		if (t < _d::_0p5<T>) {
			return (pow(_d::_2p0<T>, _d::_16p0<T> * t) - _d::_1p0<T>) / _d::_510p0<T>;
		}
		else {
			return _d::_1p0<T> - _d::_0p5<T> * pow(_d::_2p0<T>, -_d::_16p0<T> * (t - _d::_0p5<T>));
		}
	}

	template<typename T> static T easeInCirc(T t) noexcept {
		static_assert(std::is_floating_point_v<T>);
		return _d::_1p0<T> - sqrt(_d::_1p0<T> - t);
	}

	template<typename T> static T easeOutCirc(T t) noexcept {
		static_assert(std::is_floating_point_v<T>);
		return sqrt(t);
	}

	template<typename T> static T easeInOutCirc(T t) noexcept {
		static_assert(std::is_floating_point_v<T>);
		if (t < _d::_0p5<T>) {
			return (_d::_1p0<T> - sqrt(_d::_1p0<T> - _d::_2p0<T> * t)) * _d::_0p5<T>;
		}
		else {
			return (_d::_1p0<T> + sqrt(_d::_2p0<T> * t - _d::_1p0<T>)) * _d::_0p5<T>;
		}
	}

	template<typename T> static T easeInBack(T t) noexcept {
		static_assert(std::is_floating_point_v<T>);
		return t * t * (_d::_2p7<T> * t - _d::_1p7<T>);
	}

	template<typename T> static T easeOutBack(T t) noexcept {
		static_assert(std::is_floating_point_v<T>);
		return _d::_1p0<T> + (--t) * t * (_d::_2p7<T> * t + _d::_1p7<T>);
	}

	template<typename T> static T easeInOutBack(T t) noexcept {
		static_assert(std::is_floating_point_v<T>);
		if (t < _d::_0p5<T>) {
			return t * t * (_d::_7p0<T> * t - _d::_2p5<T>) * _d::_2p0<T>;
		}
		else {
			return _d::_1p0<T> + (--t) * t * _d::_2p0<T> * (_d::_7p0<T> * t + _d::_2p5<T>);
		}
	}

	template<typename T> static T easeInElastic(T t) noexcept {
		static_assert(std::is_floating_point_v<T>);
		T t2 = t * t;
		return t2 * t2 * sin(t * _d::PI<T> * _d::_4p5<T>);
	}

	template<typename T> static T easeOutElastic(T t) noexcept {
		static_assert(std::is_floating_point_v<T>);
		T t2 = (t - _d::_1p0<T>) * (t - _d::_1p0<T>);
		return _d::_1p0<T> - t2 * t2 * cos(t * _d::PI<T> * _d::_4p5<T>);
	}

	template<typename T> static T easeInOutElastic(T t) noexcept {
		static_assert(std::is_floating_point_v<T>);
		T t2;
		if (t < _d::_0p45<T>) {
			t2 = t * t;
			return _d::_8p0<T> * t2 * t2 * sin(t * _d::PI<T> * _d::_9p0<T>);
		}
		else if (t < _d::_0p55<T>) {
			return _d::_0p5<T> + _d::_0p75<T> * sin(t * _d::PI<T> * _d::_4p0<T>);
		}
		else {
			t2 = (t - _d::_1p0<T>) * (t - _d::_1p0<T>);
			return _d::_1p0<T> - _d::_8p0<T> * t2 * t2 * sin(t * _d::PI<T> * _d::_9p0<T>);
		}
	}

	template<typename T> static T easeInBounce(T t) noexcept {
		static_assert(std::is_floating_point_v<T>);
		return pow(_d::_2p0<T>, _d::_6p0<T> * (t - _d::_1p0<T>)) * abs(sin(t * _d::PI<T> * _d::_3p5<T>));
	}

	template<typename T> static T easeOutBounce(T t) noexcept {
		static_assert(std::is_floating_point_v<T>);
		return _d::_1p0<T> - pow(_d::_2p0<T>, -_d::_6p0<T> * t) * abs(cos(t * _d::PI<T> * _d::_3p5<T>));
	}

	template<typename T> static T easeInOutBounce(T t) noexcept {
		static_assert(std::is_floating_point_v<T>);
		if (t < _d::_0p5<T>) {
			return _d::_8p0<T> * pow(_d::_2p0<T>, _d::_8p0<T> * (t - _d::_1p0<T>)) * abs(sin(t * _d::PI<T> * _d::_7p0<T>));
		}
		else {
			return _d::_1p0<T> - _d::_8p0<T> * pow(_d::_2p0<T>, -_d::_8p0<T> * t) * abs(sin(t * _d::PI<T> * _d::_7p0<T>));
		}
	}

	// Helper function
	template<typename T, typename U> static T ease(T start, T end, U time) {
		static_assert(std::is_floating_point_v<U>);
		return start + (end - start) * time;
	}
}


#endif