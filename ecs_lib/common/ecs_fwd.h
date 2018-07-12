#pragma once

#include <cstdint>
#include <memory>

namespace terra
{
	using Guid_t = int64_t;
	using ClassId_t = uint32_t;

	class EntityAdmin;
	class Entity;
	class BaseComponent;
	class BaseSystem;

	using EntityPtr = Entity*;//std::shared_ptr<Entity>;
	using WeakEntityPtr = std::weak_ptr<Entity>;

}