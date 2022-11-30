
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

	api::init();
	const auto dumper = std::make_unique<Dumper>(new Dumper(false));

	for (const auto image : dumper->get_images())
	{
		if (strcmp(image->get_name(), "Facepunch.System.dll") != 0)
			continue;

		printf("[memity] current image: %s (0x%llx)\n", image->get_name(), static_cast<void*>(image));
		for (const auto object : image->get_classes())
		{
			const auto klass = static_cast<Class*>(object); // Cast from void* to our custom Il2CppClass implementation

			if (klass)
			{
				printf("\t[memity] dumping class %s (0x%llx)\n", klass->get_name(), static_cast<void*>(klass));
				for (const auto field : klass->get_fields())
				{
					if (field)
						printf("\t\t[memity] field %s dumped at offset 0x%x\n", api::get_field_name(field), klass->get_field_offset(api::get_field_name(field)));
				}
			}
		}
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


