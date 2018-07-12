#include "entity_admin.h"

using namespace terra;

EntityAdmin::EntityAdmin()
{
}

EntityAdmin::~EntityAdmin()
{
	DestroyAllEntities();
}


Entity* EntityAdmin::FindEntity(Guid_t eid)
{
	auto it = entities_.find(eid);
	return (it == entities_.end()) ? nullptr : (it->second).get();
}

void EntityAdmin::DestroyEntity(Guid_t eid)
{
	auto it = entities_.find(eid);
	if (it != entities_.end())
	{
		entities_.erase(it);
	}
}

void EntityAdmin::DestroyAllEntities()
{
	entities_.clear();
}

ComponentSet& EntityAdmin::GetComponentSet(int idx)
{
	return component_pool_.GetComponentSet(idx);
}
