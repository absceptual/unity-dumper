#include <array>
#include <iostream>
#include <fstream>
#include <unordered_set>

#include <src/dumper/dumper.hpp>

using q_classes = std::vector<std::string>;
using dump_t = std::pair<std::string, q_classes>;

static std::array dump_information{ std::to_array<dump_t>
({
	{"Assembly-CSharp.dll", 
		{
			"BasePlayer",
			"BaseNetworkable",
			"BaseEntity"
		}
	}
}) };

inline void dump()
{
	const auto dumper{ std::make_unique<Dumper>() };
	const auto images = dumper->get_images();
	std::ofstream outf("C:\\Users\\0xFF\\Desktop\\dump.txt");


	if (!outf)
		return;

	outf << "namespace sdk\n{\n";
	for (const auto image : images)
	{
		for (const auto& [q_image, q_classes] : dump_information)
		{
			if (strcmp(q_image.c_str(), image->get_name()) != 0)
				continue; // Not the image we are looking for in our dump
			for (const auto klass : image->get_classes())
			{
				if (klass)
				{
					for (const auto q_class : q_classes)
					{
						if (strcmp(q_class.c_str(), static_cast<Class*>(klass)->get_name()) != 0)
							continue; // Not the class we are looking for

						outf << "\tnamespace " << static_cast<Class*>(klass)->get_name() << "\n\t{\n";
						for (const auto field : static_cast<Class*>(klass)->get_fields())
						{
							if (field)
								outf << "\t\tinline std::size_t " << api::get_field_name(field) << " = 0x" << std::hex << api::get_field_offset(field) << ";\n";
						}

						outf << "\t}\n";
					}

				}	
			}
		}
	}
	outf << "}\n";
}

/*
const auto assembly = game->get_image("Assembly-CSharp.dll");
printf("[memity] assembly-csharp -> %s (0x%llx)\n", assembly->get_name(), reinterpret_cast<uintptr_t>(assembly));

const auto networkable_type = reinterpret_cast<void*>(uintptr_t(assembly->get_class("BaseNetworkable")) + sdk::BaseEntity::addedToParentEntity);
const auto realm_offset = assembly->get_class("BaseNetworkable")->get_nested_type("EntityRealm")->get_field_offset("entityList");

const auto networkable = *reinterpret_cast<uintptr_t**>(networkable_type);
auto realm = *reinterpret_cast<entitylist_t**>(*networkable + realm_offset);
auto keys = realm->keys;
auto values = realm->values;

using g_t = __int64(__fastcall*)(__int64);
g_t g = (g_t)api::get_function("UnityEngine.GameObject::get_tag()");
*/



// basenetworkable + 0xb8 (base_entity ref) + 0x0 (client entities) + 0x10 (entitylist) + 0x28 (bufferlist) + 0x18 (object list)