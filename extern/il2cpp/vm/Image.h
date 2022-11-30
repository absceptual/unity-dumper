#pragma once

#include <stdint.h>
#include <string>

struct TypeInfo;
struct MethodInfo;
struct Il2CppAssembly;
struct Il2CppDelegate;
struct Il2CppImage;
struct Il2CppType;
struct Il2CppGenericContext;
struct Il2CppGenericContainer;
struct Il2CppReflectionAssembly;
class AssemblyVector;

namespace il2cpp
{
namespace vm
{

class TypeNameParseInfo;

struct EmbeddedResourceRecord
{
	EmbeddedResourceRecord(const Il2CppImage* image, const std::string& name, uint32_t offset, uint32_t size)
		: image(image), name(name), offset(offset), size(size)
	{}

	const Il2CppImage* image;
	std::string name;
	uint32_t offset;
	uint32_t size;
};

class Image
{
// exported
public:
	static Il2CppImage* GetCorlib ();

public:
	static const char * GetName (const Il2CppImage* image);
	static const char * GetFileName (const Il2CppImage* image);
	static const Il2CppAssembly* GetAssembly(const Il2CppImage* image);
	static const MethodInfo* GetEntryPoint (const Il2CppImage* image);
	static const Il2CppImage* GetExecutingImage();
	static const Il2CppImage* GetCallingImage();
	static size_t GetNumTypes(const Il2CppImage* image);
	static const TypeInfo* GetType(const Il2CppImage* image, size_t index);
	static TypeInfo* FromTypeNameParseInfo (const Il2CppImage* image, const TypeNameParseInfo &info, bool ignoreCase);
	static TypeInfo* ClassFromName (Il2CppImage* image, const char* namespaze, const char *name);

	struct EmbeddedResourceData
	{
		EmbeddedResourceData(EmbeddedResourceRecord record, void* data)
			: record(record), data(data)
		{}

		EmbeddedResourceRecord record;
		void* data;
	};

	static void CacheMemoryMappedResourceFile(Il2CppReflectionAssembly* assembly, void* memoryMappedFile);
	static void* GetCachedMemoryMappedResourceFile(Il2CppReflectionAssembly* assembly);
	static void CacheResourceData(EmbeddedResourceRecord record, void* data);
	static void* GetCachedResourceData(const Il2CppImage* image, const std::string& name);
	static void ClearCachedResourceData();
};

} /* namespace vm */
} /* namespace il2cpp */
