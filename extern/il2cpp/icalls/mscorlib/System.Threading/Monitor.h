#pragma once

#include <stdint.h>

struct Il2CppObject;

namespace il2cpp
{
namespace icalls
{
namespace mscorlib
{
namespace System
{
namespace Threading
{

class Monitor
{
public:
	static void Enter (Il2CppObject *);
	static void Exit (Il2CppObject *);
	static void Monitor_pulse (Il2CppObject* obj);
	static void Monitor_pulse_all (Il2CppObject* obj);
	static bool Monitor_test_synchronised (Il2CppObject* obj);
	static bool Monitor_try_enter (Il2CppObject* obj, int32_t ms);
	static bool Monitor_wait (Il2CppObject* obj, int32_t ms);
};

} /* namespace Threading */
} /* namespace System */
} /* namespace mscorlib */
} /* namespace icalls */
} /* namespace il2cpp */
