#pragma once

#include "core.h"

namespace terra
{
#define  DECALRE_TYPE(object_name) \
private: \
	static constexpr ClassId_t kClassId = CRC32_HASH(#object_name); \
public: \
	ClassId_t ClassID() const { return kClassId; } \
	virtual const char* ClassName() { return #object_name; }

	class UObject
	{
		DECALRE_TYPE(UObject)
	public:
		UObject();
		virtual ~UObject();
	};

}