#pragma once

namespace terra
{
	static constexpr int INDEX_NONE = -1;

#define MAKE_INSTANCE(classname)    \
    \
public:                             \
    static classname* GetInstance() \
    {                               \
        static classname obj;       \
        return &obj;                \
    }


}