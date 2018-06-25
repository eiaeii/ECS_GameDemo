#include "component_pool.h"
#include <algorithm>
using namespace terra;

void ComponentPool::RemoveComponent(int idx, BaseComponent* component)
{
	if (!component)
	{
		assert(false);
		return;
	}
	auto& component_set = GetComponentSet(idx);
	auto it = std::find_if(component_set.begin(), component_set.end(),
		[component](const auto& v) { return component == v.get(); });

	assert(it != component_set.end());
	if (it != component_set.end())
	{
		component_set.erase(it);
	}
}

ComponentSet& ComponentPool::GetComponentSet(int idx)
{
	return component_pools_[idx];
}
