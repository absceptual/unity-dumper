#pragma once

#include <stdint.h>
struct Il2CppString;
struct Il2CppArray;

namespace il2cpp
{
namespace icalls
{
namespace mscorlib
{
namespace System
{

class String
{
public:
	static void RedirectToCreateString();
	static Il2CppString* InternalAllocateStr (int length);
	static Il2CppString* InternalIntern (Il2CppString* str);
	static Il2CppArray* InternalSplit (Il2CppString *,Il2CppArray*,int,int);
	static Il2CppString* InternalIsInterned(Il2CppString* str);
};

} /* namespace System */
} /* namespace mscorlib */
} /* namespace icalls */
} /* namespace il2cpp */
