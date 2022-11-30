#pragma once

#include <stdint.h>
#include <vector>
#include <string>

struct Il2CppAssembly;
struct Il2CppAssemblyName;
struct Il2CppImage;

namespace il2cpp
{
namespace vm
{

typedef std::vector<const Il2CppAssembly*> AssemblyVector;

class Assembly
{
// exported
public:
	static Il2CppImage* GetImage (const Il2CppAssembly* assembly);
public:
	static AssemblyVector* GetAllAssemblies();
	static const Il2CppAssembly* GetLoadedAssembly(const char* name);
	static const Il2CppAssembly* Load (const char* name);
	static void Register (const Il2CppAssembly* assembly);
	static void Initialize ();
	static std::string AssemblyNameToString(const Il2CppAssemblyName& aname);

private:
};

} /* namespace vm */
} /* namespace il2cpp */
