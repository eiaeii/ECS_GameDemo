#pragma once

#include <type_traits>
#include "ecs_fwd.h"

namespace terra
{
	namespace details
	{
		template <typename F, typename Tuple, bool Done, size_t Total, size_t... N>
		struct apply_impl {
			static bool call(F f, Tuple&& t)
			{
				return apply_impl<F, Tuple, Total == 1 + sizeof...(N), Total, N..., sizeof...(N)>::call(
					f, std::forward<Tuple>(t));
			}
		};

		template <typename F, typename Tuple, size_t Total, size_t... N>
		struct apply_impl<F, Tuple, true, Total, N...> {
			static bool call(F f, Tuple&& t) { return f(std::get<N>(std::forward<Tuple>(t))...); }
		};

		// user invokes this
		template <typename F, typename Tuple>
		bool apply(F f, Tuple&& t)
		{
			typedef typename std::decay<Tuple>::type ttype;
			return details::apply_impl<F, Tuple, 0 == std::tuple_size<ttype>::value, std::tuple_size<ttype>::value>::call(
				f, std::forward<Tuple>(t));
		}

		//template <bool, typename... Ts>
		//struct TsTraitsImpl;

		//template<typename T>
		//struct TsTraitsImpl<true, T>
		//{
		//	using Type = T;
		//};

		//template<typename... Ts>
		//struct TsTraitsImpl<false, Ts...>
		//{
		//	using Type = std::tuple<Ts...>;
		//};

	}

	//template <typename... Ts>
	//struct TsTraits
	//{
	//	using Type = typename details::TsTraitsImpl<sizeof...(Ts) == 1, Ts...>::Type;
	//};

	template<typename T>
	struct IsEntity : std::integral_constant<bool, std::is_base_of_v<Entity, T> && !std::is_same_v<Entity, T>> {};
	template<typename T>
	constexpr bool IsEntity_v = IsEntity<T>::value;

	template<typename T>
	struct IsComponent : std::integral_constant<bool, std::is_base_of_v<BaseComponent, T> && !std::is_same_v<BaseComponent, T>> {};
	template<typename T>
	constexpr bool IsComponent_v = IsComponent<T>::value;

	template<typename T>
	struct IsComponentPointer : std::integral_constant<bool, IsComponent_v<std::remove_pointer<T>> && !std::is_pointer_v<T>> {};
	template<typename T>
	constexpr bool IsComponentPointer_v = IsComponentPointer<T>::value;

	template<typename T>
	struct IsSystem : std::integral_constant<bool, std::is_base_of_v<BaseSystem, T> && !std::is_same_v<BaseSystem, T>> {};
	template<typename T>
	constexpr bool IsSystem_v = IsSystem<T>::value;

	struct Type2Index
	{
		template <typename T>
		static int Index()
		{
			static int idx = count()++;
			return idx;
		}
		static int& count()
		{
			static int counter = 0;
			return counter;
		}
	};
}