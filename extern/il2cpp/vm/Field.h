#pragma once

#include <stdint.h>

struct FieldInfo;
struct Il2CppType;
struct TypeInfo;
struct Il2CppObject;

namespace il2cpp
{
namespace vm
{

class Field
{
public:
	// exported
	static const Il2CppType* GetType (FieldInfo *field);
	static TypeInfo* GetParent (FieldInfo *field);
	static int GetFlags (FieldInfo *field);
	static const char* GetName (FieldInfo *field);
	static size_t GetOffset (FieldInfo *field);
	static void GetValue (Il2CppObject *obj, FieldInfo *field, void *value);
	static uint32_t GetToken (const FieldInfo *field);
	static Il2CppObject* GetValueObject (FieldInfo *field, Il2CppObject *obj);
	static bool HasAttribute (FieldInfo *field, TypeInfo *attr_class);
	static bool IsDeleted (FieldInfo *field);
	static void SetValue (Il2CppObject *obj, FieldInfo *field, void *value);
	static void StaticGetValue (FieldInfo *field, void *value);
	static void StaticSetValue (FieldInfo *field, void *value);

public:
	// internal
	static const char* GetData (FieldInfo *field);
	static void GetDefaultFieldValue (FieldInfo *field, void *value);

	static bool IsInstance (FieldInfo* field);
	static bool IsNormalStatic (FieldInfo* field);
	static bool IsThreadStatic (FieldInfo* field);
};

} /* namespace vm */
} /* namespace il2cpp */
