
#include <iostream>

#include <src/util/globals.h>
#include <src/sdk/entities.h>


auto startup()
{
	AllocConsole();
	FILE* output;
	freopen_s(&output, "CONOUT$", "w", stdout);

	return output;
}

DWORD cleanup(HMODULE module, FILE* output)
{
	fclose(output);
	FreeConsole();
	FreeLibraryAndExitThread(module, 0);

	return 0;
}


DWORD WINAPI entry_point(HMODULE module)
{
	auto output{ startup() };

	api::init();
	printf("[memity] console started\n");


	printf("[memity] api initalized\n");

	globals::game = std::make_unique<Dumper>();

	const auto entitylist = EntityList::GetEntityList(globals::game);
	const auto lplayer = reinterpret_cast<BaseCombatEntity*>(entitylist->get_entity(1));
	if (lplayer)
	{
		const auto prefab = lplayer->get_prefab_name();
		const auto model = lplayer->get_model();
		if (model)
		{
			//const auto bone_transforms = model->get_bone_transforms();
			//const auto bone_names = model->get_bone_names();
			const auto bones = lplayer->get_bones();

			for (int i = 0; i < bones->count; ++i)
			{
				const auto bone = lplayer->get_bone(i);
				const auto name = bone->name;
	
				printf("[memity] bone: %ls\n", name->get_phrase()->text);

			}
			

			//Vector3 position;
			// reinterpret_cast<Transform*>(bone_transforms->buffer[0])->get_position(&position);
		}
	}
	


	Sleep(1600);
	return cleanup(module, output);
}

DWORD WINAPI DllMain(HINSTANCE module,
					 DWORD reason,
					 void* reserved
)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		const auto thread = CreateThread(nullptr, 0x0, reinterpret_cast<LPTHREAD_START_ROUTINE>(entry_point), module, 0x0, nullptr);
		if (thread)
		{
			DisableThreadLibraryCalls(module);
			CloseHandle(thread);
		}
	}
	return TRUE;
}


