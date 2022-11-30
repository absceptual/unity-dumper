
#include <iostream>
#include <src/dumper/dumper.hpp>

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
	printf("[memity] console started\n");


	// Example for Rust (x64)
	api::init();
	printf("[memity] api initalized\n");

	const auto game = std::make_unique<Dumper>();
	printf("[memity] images dumped\n");

	const auto image = game->get_image("Assembly-CSharp.dll");
	printf("[memity] Assembly-CSharp -> %s (0x%llx)\n", image->get_name(), reinterpret_cast<uintptr_t>(image));

	const auto base_player = image->get_class("BasePlayer");
	printf("[memity] BasePlayer -> %s (0x%llx)\n", base_player->get_name(), reinterpret_cast<uintptr_t>(base_player));
	
	for (const auto field : base_player->get_fields())
	{
		const auto name = api::get_field_name(field);
		printf("\t[memity] %s (0x%zx)\n", name, base_player->get_field_offset(name));
	}
	
	Sleep(50000);
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


