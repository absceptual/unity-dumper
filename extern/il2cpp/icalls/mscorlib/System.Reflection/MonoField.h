#pragma once

#include <stdint.h>
#include "object-internals.h"

struct mscorlib_System_Reflection_FieldInfo;
struct mscorlib_System_Reflection_Emit_UnmanagedMarshal;

namespace il2cpp
{
namespace icalls
{
namespace mscorlib
{
namespace System
{
namespace Reflection
{

class MonoField
{
public:
	static int32_t GetFieldOffset (Il2CppReflectionField * __this);
	static Il2CppReflectionType * GetParentType (Il2CppReflectionField * field, bool declaring);
	static Il2CppObject* GetRawConstantValue (Il2CppReflectionField* field);
	static Il2CppObject * GetValueInternal (Il2CppReflectionField * __this, Il2CppObject * obj);
	static void SetValueInternal (Il2CppReflectionField * fi, Il2CppObject * obj, Il2CppObject * value);
};
	
} /* namespace Reflection */
} /* namespace System */
} /* namespace mscorlib */
} /* namespace icalls */
} /* namespace il2cpp */
