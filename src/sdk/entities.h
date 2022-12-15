#pragma once

#include <src/sdk/classes.h>
#include <src/sdk/unity.h>
#include <src/dumper/dumper.hpp>


class Phrase;
class Model;
struct BoneProperty;

class SkeletonProperties
{
public:
	SkeletonProperties() = default;

	auto get_bone_property(std::int32_t id) -> BoneProperty*
	{
		static auto typeinfo = globals::game->get_image("Assembly-CSharp.dll")->get_class("SkeletonProperties");
		static auto offset = typeinfo->get_field_offset("bones");

		auto bones = *reinterpret_cast<Il2CppArray**>(uintptr_t(this) + offset);
		if (!bones->buffer || id >= bones->count)
			return nullptr;

		return reinterpret_cast<BoneProperty*>(bones->buffer[id]);
	}

	auto get_bones() const
	{
		static auto typeinfo = globals::game->get_image("Assembly-CSharp.dll")->get_class("SkeletonProperties");
		static auto offset = typeinfo->get_field_offset("bones");

		return *reinterpret_cast<Il2CppArray**>(uintptr_t(this) + offset);
	}
};

class BaseNetworkable
{
public:
	BaseNetworkable() = default;

	Il2CppString* get_prefab_name() const 
	{
		static auto typeinfo = globals::game->get_image("Assembly-CSharp.dll")->get_class("BaseNetworkable");
		static auto offset = typeinfo->get_field_offset("_prefabName");

		return *reinterpret_cast<Il2CppString**>(uintptr_t(this) + offset);
	}
};

class BaseEntity : public BaseNetworkable
{
public:
	BaseEntity() = default;

	auto get_model() const -> Model*
	{
		static auto typeinfo = globals::game->get_image("Assembly-CSharp.dll")->get_class("BaseEntity");
		static auto offset = typeinfo->get_field_offset("model");

	
		return *reinterpret_cast<Model**>(uintptr_t(this) + offset);
	}
};

class BaseCombatEntity : public BaseEntity
{
public:
	enum LifeState
	{
		Alive, 
		Dead,

		MAX_LIFESTATES
	};
	enum Faction
	{
		Default,
		Player,
		Bandit,
		Scientist,
		Horror,

		MAX_FACTIONS
	};

	auto get_health() const
	{
		static auto typeinfo = globals::game->get_image("Assembly-CSharp.dll")->get_class("BaseCombatEntity");
		static auto offset = typeinfo->get_field_offset("_health");

		return *reinterpret_cast<float*>(uintptr_t(this) + offset);
	}

	auto get_max_health() const
	{
		static auto typeinfo = globals::game->get_image("Assembly-CSharp.dll")->get_class("BaseCombatEntity");
		static auto offset = typeinfo->get_field_offset("_maxHealth");

		return *reinterpret_cast<float*>(uintptr_t(this) + offset);
	}

	auto get_life_state() const -> BaseCombatEntity::LifeState
	{
		static auto typeinfo = globals::game->get_image("Assembly-CSharp.dll")->get_class("BaseCombatEntity");
		static auto offset = typeinfo->get_field_offset("lifestate");

		return *reinterpret_cast<BaseCombatEntity::LifeState*>(uintptr_t(this) + offset);
	}

	auto get_faction() const 
	{
		static auto typeinfo = globals::game->get_image("Assembly-CSharp.dll")->get_class("BaseCombatEntity");
		static auto offset = typeinfo->get_field_offset("faction");

		return *reinterpret_cast<BaseCombatEntity::Faction*>(uintptr_t(this) + offset);
	}

	auto get_bone(std::int32_t id) const
	{
		static auto typeinfo = globals::game->get_image("Assembly-CSharp.dll")->get_class("BaseCombatEntity");
		static auto offset = typeinfo->get_field_offset("skeletonProperties");

		const auto skeleton = *reinterpret_cast<SkeletonProperties**>(uintptr_t(this) + offset);
		return skeleton->get_bone_property(id);
	}

	auto get_bones() const
	{
		static auto typeinfo = globals::game->get_image("Assembly-CSharp.dll")->get_class("BaseCombatEntity");
		static auto offset = typeinfo->get_field_offset("skeletonProperties");

		const auto skeleton = *reinterpret_cast<SkeletonProperties**>(uintptr_t(this) + offset);
		return skeleton->get_bones();
	}
};

class BasePlayer
{
private:
	std::uintptr_t m_instance { };

public:

	
};

enum class HitArea
{
	Head = 1,
	Chest = 2,
	Stomach = 4,
	Arm = 8,
	Hand = 16,
	Leg = 32,
	Foot = 64,

	MAX_HIT_AREAS
};

class EntityList
{
private:
	Il2CppArray* m_instance{ }; // Should be the address of the EntityRealm values buffer list

public:
	EntityList() = default;
	EntityList(void* instance) : m_instance{ reinterpret_cast<Il2CppArray*>(instance) } {}

	static auto GetEntityList(const std::unique_ptr<Dumper>& dumper) -> std::unique_ptr<EntityList>
	{
		const auto assembly{ dumper->get_image("Assembly-CSharp.dll") };
		if (!assembly)
			return nullptr;

		// ParentEntity contains an offset to the current BaseNetworkable from our TypeInfo
		const auto networkable = assembly->get_class("BaseNetworkable");
		auto offset = assembly->get_class("BaseEntity")->get_field_offset("addedToParentEntity");

		// Get our BaseNetworkable address then deference twice to get our EntityRealm
		const auto realm = **reinterpret_cast<Class***>(
			uintptr_t(networkable) + offset
			);

		if (!realm)
			return nullptr;

		// Access our ListDictionary structure
		offset = networkable->get_nested_type("EntityRealm")->get_field_offset("entityList");
		const auto entitylist = *reinterpret_cast<sdk::entitylist_t**>(
			uintptr_t(realm) + offset
			);

		if (!entitylist)
			return nullptr;


		// We only care about the values within the entitylist
		return std::make_unique<EntityList>(entitylist->values->array);
	}

	std::int32_t get_count() const { return m_instance->count; }

	// Gets the entity at index id (id - 1)
	auto get_entity(const std::int32_t id) const -> void*
	{
		if (!(&m_instance->buffer) || id >= m_instance->count)
			return nullptr;

		return m_instance->buffer[id - 1];
	}

	void* get_internal_list() const { return m_instance->buffer; }
};

struct BoneProperty
{
	std::uint8_t padding[0x10];
	GameObject* bone;
	Phrase* name;
	HitArea area;
};



class Model
{
public:
	Model() = default;

	auto get_bone_names() -> Il2CppArray*
	{
		static auto typeinfo = globals::game->get_image("Assembly-CSharp.dll")->get_class("Model");
		static auto offset = typeinfo->get_field_offset("boneNames");

		return *reinterpret_cast<Il2CppArray**>(uintptr_t(this) + offset);
	}

	auto get_bone_transforms() -> Il2CppArray*
	{
		static auto typeinfo = globals::game->get_image("Assembly-CSharp.dll")->get_class("Model");
		static auto offset = typeinfo->get_field_offset("boneTransforms");

		return *reinterpret_cast<Il2CppArray**>(uintptr_t(this) + offset);
	}

	auto get_bone(std::int32_t id) -> std::unique_ptr<Transform>
	{
		const auto transforms = get_bone_transforms();
		if (!transforms)
			return nullptr;

		if (!transforms->buffer || transforms->count >= id)
			return nullptr;

		return std::make_unique<Transform>(transforms->buffer[id]);
	}
};

class Phrase
{
public:
	Il2CppString* get_phrase() const
	{
		static auto typeinfo = globals::game->get_image("Rust.Localization.dll")->get_class("Translate")->get_nested_type("Phrase");
		static auto offset = typeinfo->get_field_offset("english");

		return *reinterpret_cast<Il2CppString**>(uintptr_t(this) + offset);
	}
};


 
