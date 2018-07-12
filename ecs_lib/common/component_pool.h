#pragma once

#include "core.h"
#include "component.h"

namespace terra
{
	using ComponentSet = std::unordered_set<std::unique_ptr<BaseComponent>>;
    class ComponentPool
    {
	private:
        std::unordered_map<ClassId_t, ComponentSet> component_pools_;
    public:
        template <class C, typename... Args>
        auto NewComponent(Args&&... args) -> std::enable_if_t<IsComponent_v<C>, C*>;
		void RemoveComponent(int idx, BaseComponent* component);

        ComponentSet& GetComponentSet(int idx);
    };

    template <class C, typename... Args>
	auto ComponentPool::NewComponent(Args&&... args) -> std::enable_if_t<IsComponent_v<C>, C*>
    {
        ComponentSet& component_set = GetComponentSet(Type2Index::Index<C>());
		auto pair = component_set.insert(std::make_unique<C>());
		if (pair.second)
		{
			C* c = static_cast<C*>((*(pair.first)).get());
			c->Reset(std::forward<Args>(args)...);
			return c;
		}
		return nullptr;
    }
}