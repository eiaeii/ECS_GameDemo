#pragma once

#include "ecs_fwd.h"

namespace terra
{
    class BaseComponent
    {
    protected:
		EntityPtr ent_;

    public:
		BaseComponent();
        virtual ~BaseComponent();

		void SetOwner(EntityPtr ent) { ent_ = ent; }
		EntityPtr Owner() { return ent_; }

        template <typename C, typename = std::enable_if_t<IsComponent_v<C>>>
        C* As();
        template <typename C, typename = std::enable_if_t<IsComponent_v<C>>>
        C const* As() const;

		template<class C, typename = std::enable_if_t<IsComponent_v<C>>>
		C* Sibling();

	private:
		BaseComponent* SiblingComponent(const ClassId_t index);
    };

	template <typename C, typename >
	C* BaseComponent::As()
	{
		return static_cast<C*>(this);
	}

	template <typename C, typename >
	C const* BaseComponent::As() const
	{
		return static_cast<C*>(this);
	}

	template<typename C, typename >
	C* BaseComponent::Sibling()
	{
		BaseComponent* component = SiblingComponent(Type2Index::Index<C>());
		return component ? component->As<C>() : nullptr;
	}
}
