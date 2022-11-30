#pragma once

#include <stdint.h>

struct Il2CppDomain;

namespace il2cpp
{
namespace vm
{

class Environment
{
public:
	static char** GetMainArgs();
	static int GetNumMainArgs();
	static void SetMainArgs(char** args, int num_args);

private:
	static char **main_args;
	static int num_main_args;
};

} /* namespace vm */
} /* namespace il2cpp */
