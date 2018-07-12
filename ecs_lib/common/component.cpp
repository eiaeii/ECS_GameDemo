#include "entity.h"
#include "component.h"

using namespace terra;

BaseComponent* BaseComponent::SiblingComponent(const ClassId_t index)
{
	return ent_ ? ent_->GetComponent(index) : nullptr;
}

BaseComponent::BaseComponent()
{
}

BaseComponent::~BaseComponent()
{
}
