#pragma once

struct Il2CppString;
struct mscorlib_System_Reflection_Emit_AssemblyBuilder;
struct mscorlib_System_Reflection_Module;

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
namespace Emit
{

class AssemblyBuilder
{
public:
	static void basic_init (mscorlib_System_Reflection_Emit_AssemblyBuilder* );
	static mscorlib_System_Reflection_Module* InternalAddModule (mscorlib_System_Reflection_Emit_AssemblyBuilder * __this, Il2CppString* fileName);
};
	
} /* namespace Emit */
} /* namespace Reflection */
} /* namespace System */
} /* namespace mscorlib */
} /* namespace icalls */
} /* namespace il2cpp */
