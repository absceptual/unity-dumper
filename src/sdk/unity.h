#pragma once
#include <src/dumper/api.hpp>

#define ZERO_ARRAY 0

// Il2Cpp internal types
struct Il2CppArray
{
	std::uint8_t padding[0x18];
	std::int32_t count;
	std::uint8_t padding_2[0x4];
	void* buffer[ZERO_ARRAY];
};

struct Il2CppString
{
	std::uint8_t padding[0x10];
	std::int32_t length;
	const wchar_t text[ZERO_ARRAY];
};


struct BufferList
{
	std::uint8_t padding[16];
	int count;
	Il2CppArray* array;
};

struct ListDictionary
{
	std::uint8_t padding[32]; 
	BufferList* keys; // 0x20
	BufferList* values; // 0x28
};

class GameObject;

struct Vector3 { float x, y, z; };

class Transform
{
private:
	void* m_instance{ };
	using get_position_t = Vector3* (APICALL*)(void* _this, Vector3* out);

public:
	Transform() = default;
	Transform(void* instance) : m_instance{ instance } { }

	void get_position(Vector3* out)
	{
		static auto get_position = reinterpret_cast<get_position_t>(
			api::get_function("UnityEngine.Transform::get_position_Injected(UnityEngine.Vector3&)")
		);
			
		get_position(this, out);
	}
};


