#pragma once

#include <functional>
#include <tuple>
#include "ecs_type_traits.h"
#include "entity_admin.h"

namespace terra
{
	//{
	//	auto && __range = range_expression;
	//	for (auto __begin = begin_expr, __end = end_expr;
	//		__begin != __end; ++__begin) {
	//		range_declaration = *__begin;
	//		loop_statement
	//	}
	//}

	template <typename... Args>
	class ComponentItr
	{
		static_assert(std::conjunction_v<IsComponent<Args>... > && (sizeof...(Args) > 0), "invalid argument type!");
	private:
		class TupleIterator;
		using Iterator = TupleIterator;
		using TagDispatchType = std::conditional_t<(sizeof...(Args) == 1), std::true_type, std::false_type>;
		using Pr = typename std::function<bool(std::add_pointer_t<Args>...)>;

		EntityAdmin* admin_;
		Pr pred_;
		
	public:
		ComponentItr(EntityAdmin* admin)
			: admin_(admin)
		{
		}
		ComponentItr(EntityAdmin* admin, Pr&& pred)
			: admin_(admin), pred_(std::move(pred))
		{
		}

		Iterator begin() {
			return Iterator(admin_, pred_, true);
		}
		Iterator end() {
			return Iterator(admin_, pred_, false);
		}
	private:
		class TupleIterator
		{
		private:
			ComponentSet& component_set_;
			Pr pred_;
			ComponentSet::const_iterator it_;
			ComponentSet::const_iterator end_;
		public:
			TupleIterator(EntityAdmin* admin, Pr& pred, bool is_begin = true) 
				: pred_(pred)
				, component_set_(GetLeastComponentSet<Args...>(admin))
			{
				end_ = component_set_.end();
				if (is_begin) {
					it_ = component_set_.begin();
				}
				else
				{
					it_ = end_;
				}
				find_next(TagDispatchType());
			}

			bool operator!=(const TupleIterator& rhs) const { return It() != rhs.It(); }
			ComponentSet::const_iterator It() const
			{
				return it_;
			}

			decltype(auto) operator*() 
			{ 
				auto ent = (*it_)->Owner();
				assert(ent);
				return ent->Get<Args...>();
			}
			TupleIterator& operator++()
			{
				++it_;
				find_next(TagDispatchType());
				return *this;
			}

		private:
			template<typename U>
			ComponentSet& GetLeastComponentSet(EntityAdmin* admin, ComponentSet& compare_set)
			{
				auto& component_set = admin->GetComponentSet(Type2Index::Index<U>());
				return compare_set.size() <= component_set.size() ? compare_set : component_set;
			}

			template<typename U, typename... Us>
			auto GetLeastComponentSet(EntityAdmin* admin, ComponentSet& compare_set) -> std::enable_if_t<(sizeof...(Us)!=0), ComponentSet& >
			{
				auto& component_set = admin->GetComponentSet(Type2Index::Index<U>());
				return GetLeastComponentSet<Us...>(admin, compare_set.size() <= component_set.size() ? compare_set : component_set);
			}

			template<typename U, typename... Us>
			ComponentSet& GetLeastComponentSet(EntityAdmin* admin)
			{
				auto& component_set = admin->GetComponentSet(Type2Index::Index<U>());
				return GetLeastComponentSet<Us...>(admin, component_set);
			}
		private:
			void find_next(std::false_type&& t) {
				while (it_ != end_)
				{
					auto ent = (*it_)->Owner();
					if (ent && ent->Has<Args...>() && (!pred_ || (pred_ && details::apply(pred_, ent->Get<Args...>()))))
					{
						break;
					}
					++it_;
				}
			}

			void find_next(std::true_type&& t) {
				auto& ent = (*it_)->Owner();
				while (it_ != end_ && pred_ && !pred_(ent->Get<Args...>()))
				{
					++it_;
				}
			}
		};
	};


}