#include "entity.h"
#include "entity_admin.h"
#include "component.h"

using namespace terra;

Entity::Entity(EntityAdmin* entity_admin, Guid_t eid) : entity_admin_(entity_admin), eid_(eid)
{
}

Entity::~Entity()
{
	DestroyAllComponent();
}

Entity& Entity::AddComponent(const int index, BaseComponent* component) 
{
	//ECS_ASSERT(!HasComponent(index), "Error, cannot add component to entity, component already exists");
	components_[index] = component;
	component->SetOwner(this);
	return*this;
}

BaseComponent* Entity::GetComponent(const int index) const
{
	if (!HasComponent(index))
	{
		return nullptr;
	}

	return components_.at(index);
}

bool Entity::HasComponent(const int index) const 
{ 
	return (components_.find(index) != components_.end());
}

void Entity::Destroy() {}

void Entity::DestroyAllComponent()
{
	//for (const auto& kv : components_)
	//{
	//	//onRemove()
	//	pool_.RemoveComponent(kv.first, kv.second);
	//}
	//components_.clear();
}
