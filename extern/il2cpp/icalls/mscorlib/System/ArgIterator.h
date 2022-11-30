#pragma once

#include <stdint.h>
#include "object-internals.h"

struct mscorlib_System_ArgIterator;

namespace il2cpp
{
namespace icalls
{
namespace mscorlib
{
namespace System
{

class ArgIterator
{
public:
	static void* /* System.TypedReference */ IntGetNextArg (ArgIterator self);
	static Il2CppTypedRef IntGetNextArg_mscorlib_System_TypedReference (mscorlib_System_ArgIterator * __this);
	static Il2CppTypedRef IntGetNextArg_mscorlib_System_TypedReference_mscorlib_System_IntPtr (mscorlib_System_ArgIterator * __this, Il2CppIntPtr rth);
	static void Setup (mscorlib_System_ArgIterator * __this, Il2CppIntPtr argsp, Il2CppIntPtr start);
	static Il2CppIntPtr IntGetNextArgType (mscorlib_System_ArgIterator * __this);
};

} /* namespace System */
} /* namespace mscorlib */
} /* namespace icalls */
} /* namespace il2cpp */
