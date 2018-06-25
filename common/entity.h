#pragma once

#include "core.h"
#include "snowflake.h"
#include "ecs_fwd.h"

#include "entity_admin.h"
namespace terra {
	class Entity {
	private:
		EntityAdmin* entity_admin_;
		Guid_t eid_;
		std::unordered_map<int, BaseComponent*> components_;

	public:
		Entity(EntityAdmin* entity_admin, Guid_t eid = Snowflake::NewGuid());
		virtual ~Entity();

		Guid_t GetEntityID() const { return eid_; }

		virtual void InitializeComponents() {}

		template <typename T, typename... TArgs>
		auto Add(TArgs&&... args)->Entity&;

		template <typename T>
		auto Get() const->T*;
		template <typename... Args>
		auto Get() const -> typename std::enable_if<(sizeof...(Args) != 1), std::tuple<Args*...> >::type;

		template <typename Arg>
		bool Has() const;
		template <typename Arg0, typename... Args>
		auto Has() const -> typename std::enable_if<sizeof...(Args) != 0, bool>::type;

		BaseComponent* GetComponent(const int index) const;
	private:
		Entity& AddComponent(const int index, BaseComponent* component);
		bool HasComponent(const int index) const;
		void Destroy();

		void DestroyAllComponent();
	};

	template <typename T, typename... TArgs>
	auto Entity::Add(TArgs&&... args) -> Entity& {
		return AddComponent(Type2Index::Index<T>(),
			entity_admin_->SpawnComponent<T>(this, std::forward<TArgs>(args)...));
	}

	template <typename T>
	auto Entity::Get() const -> T* {
		return static_cast<T*>(GetComponent(Type2Index::Index<T>()));
	}

	template<typename ...Args>
	auto Entity::Get() const -> typename std::enable_if<(sizeof ...(Args) != 1), std::tuple<Args *...>>::type
	{
		using ValueType = std::tuple<Args*...>;
		if (Has<Args...>()) {
			return ValueType(Get<Args>()...);
		}
		return ValueType();
	}

	template <typename Arg>
	bool Entity::Has() const {
		return HasComponent(Type2Index::Index<Arg>());
	}

	template <typename Arg0, typename... Args>
	auto Entity::Has() const ->
		typename std::enable_if<sizeof...(Args) != 0, bool>::type {
		return HasComponent(Type2Index::Index<Arg0>()) && Has<Args...>();
	}

}  // namespace ecs