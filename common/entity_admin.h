#pragma once

#include "core.h"
#include "ecs_fwd.h"
#include "snowflake.h"
#include "entity.h"
#include "system.h"
#include "component_pool.h"

namespace terra
{
	class EntityAdmin : public UObject
	{
		DECALRE_TYPE(EntityAdmin)
	protected:
		std::unordered_map<Guid_t, std::unique_ptr<Entity>> entities_;
		ComponentPool component_pool_;

	public:
		EntityAdmin();
		virtual ~EntityAdmin();

		virtual bool Init() { return true; }
		virtual void Update(float time_step) {}
		virtual void Exit() {}

		template<typename E>
		auto SpawnEntity() -> std::enable_if_t<IsEntity_v<E>, E*>;
		template<typename E>
		auto SpawnEntity(Guid_t eid) -> std::enable_if_t<IsEntity_v<E>, E*>;
		Entity* FindEntity(Guid_t eid);
		void DestroyEntity(Guid_t eid);

		template<typename C, typename... Args>
		auto SpawnComponent(Entity* ent, Args&&... args) -> std::enable_if_t<IsComponent_v<C>, C*>;

		ComponentSet& GetComponentSet(int idx);
	private:
		void DestroyAllEntities();
	};

	template<typename E>
	auto EntityAdmin::SpawnEntity()->std::enable_if_t<IsEntity_v<E>, E*>
	{
		auto pair = entities_.insert({ Snowflake::NewGuid(), std::make_unique<E>(this, Snowflake::NewGuid()) });
		return pair.second ? static_cast<E*>(((pair.first)->second.get())) : nullptr;
	}
	template<typename E>
	auto EntityAdmin::SpawnEntity(Guid_t eid)->std::enable_if_t<IsEntity_v<E>, E*>
	{
		auto pair = entities_.insert({ Snowflake::NewGuid(), std::make_unique<E>(this, eid) });
		return pair.second ? static_cast<E*>(((pair.first)->second.get())) : nullptr;
	}
	template<typename C, typename ...Args>
	auto EntityAdmin::SpawnComponent(Entity* ent, Args&& ...args) -> std::enable_if_t<IsComponent_v<C>, C*>
	{
		return component_pool_.NewComponent<C>(std::forward<Args>(args)...);
	}
}