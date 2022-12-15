#pragma once
#include <cstdint>
#include <Windows.h>

#ifdef _WIN64
#define APICALL __fastcall
#else
#define APICALL __cdecl
#endif


class Class;
class Image;

namespace api
{
    inline bool initalized { false };


    using get_function_t                            = void* (APICALL*)(const char*);
    inline get_function_t get_function              = nullptr;

    // domain & assembly
    using get_domain_t                              = void* (APICALL*)(void);
    using get_assemblies_t                          = void** (APICALL*)(const void* domain, size_t* count);

    inline get_domain_t get_domain                  = nullptr;
    inline get_assemblies_t get_assemblies          = nullptr;

    // images
    using get_image_t                               = Image* (APICALL*)(const void* assembly);
    using get_image_name_t                          = const char* (APICALL*)(const void* image);
    using get_class_count_t                         = size_t (APICALL*)(const void* image);

    inline get_image_t get_image                    = nullptr;
    inline get_image_name_t get_image_name          = nullptr;
    inline get_class_count_t get_class_count        = nullptr;

    // class
    using get_class_t                               = Class* (APICALL*)(const void* image, const char* namespaze, const char* name);
    using get_class_from_id_t                       = Class* (APICALL*)(const void* image, size_t index);
    using get_class_name_t                          = const char* (APICALL*)(const void* klass);
   
    inline get_class_t get_class                    = nullptr;
    inline get_class_from_id_t get_class_from_id    = nullptr;
    inline get_class_name_t get_class_name          = nullptr;
  
    // types
    using get_nested_types_t                        = Class* (APICALL*)(const void* klass, void*);
    using get_type_class_t                          = Class* (APICALL*)(const void* type);
    using get_type_name_t                           = const char* (APICALL*)(const void* type);

    inline get_nested_types_t get_nested_types      = nullptr;
    inline get_type_class_t get_type_class          = nullptr;
    inline get_type_name_t get_type_name            = nullptr;
    
    // fields
    using get_field_t                               = void* (APICALL*)(const void* klass, const char* name);
    using get_field_offset_t                        = size_t (APICALL*)(const void* field);
    using get_field_count_t                         = size_t (APICALL*)(const void* klass);
    using get_fields_t                              = void* (APICALL*)(const void* klass, void* iter);
    using get_field_name_t                          = const char* (APICALL*)(const void* field);


    inline get_field_t get_field                    = nullptr;
    inline get_field_offset_t get_field_offset      = nullptr;
    inline get_field_count_t get_field_count        = nullptr;
    inline get_fields_t get_fields                  = nullptr;
    inline get_field_name_t get_field_name          = nullptr;

    // methods
    using get_method_from_name_t                       = void* (APICALL*)(void* klass, const char* name, int args);


    inline get_method_from_name_t get_method_from_name = nullptr;


    // Required to be called before initalization of the dumper for the rest of the dumper to work properly
    inline void init();
}

#pragma warning(disable : 6387)
void api::init()
{
    if (initalized)
        return;

    get_domain = reinterpret_cast< get_domain_t >(
        GetProcAddress(GetModuleHandle(L"GameAssembly.dll"), "il2cpp_domain_get")
    );

    get_assemblies = reinterpret_cast< get_assemblies_t >(
        GetProcAddress(GetModuleHandle(L"GameAssembly.dll"), "il2cpp_domain_get_assemblies")
    );

    get_image = reinterpret_cast< get_image_t >(
        GetProcAddress(GetModuleHandle(L"GameAssembly.dll"), "il2cpp_assembly_get_image")
    );


    get_image_name = reinterpret_cast< get_image_name_t >(
        GetProcAddress(GetModuleHandle(L"GameAssembly.dll"), "il2cpp_image_get_name")
    );

    get_class_count = reinterpret_cast< get_class_count_t >(
        GetProcAddress(GetModuleHandle(L"GameAssembly.dll"), "il2cpp_image_get_class_count")
    );

    get_class = reinterpret_cast< get_class_t >(
        GetProcAddress(GetModuleHandle(L"GameAssembly.dll"), "il2cpp_class_from_name")
    );

    get_class_from_id = reinterpret_cast< get_class_from_id_t >(
        GetProcAddress(GetModuleHandle(L"GameAssembly.dll"), "il2cpp_image_get_class")
    );

    get_class_name = reinterpret_cast< get_class_name_t >(
        GetProcAddress(GetModuleHandle(L"GameAssembly.dll"), "il2cpp_class_get_name")
    );

    get_type_name = reinterpret_cast< get_type_name_t >(
        GetProcAddress(GetModuleHandle(L"GameAssembly.dll"), "il2cpp_type_get_name")
    );

    get_type_class = reinterpret_cast< get_type_class_t >(
        GetProcAddress(GetModuleHandle(L"GameAssembly.dll"), "il2cpp_type_get_class_or_element_class")
    );

    get_field = reinterpret_cast< get_field_t >(
        GetProcAddress(GetModuleHandle(L"GameAssembly.dll"), "il2cpp_class_get_field_from_name")
    );

    get_field_offset = reinterpret_cast< get_field_offset_t >(
        GetProcAddress(GetModuleHandle(L"GameAssembly.dll"), "il2cpp_field_get_offset")
    );

    get_nested_types = reinterpret_cast< get_nested_types_t >(
        GetProcAddress(GetModuleHandle(L"GameAssembly.dll"), "il2cpp_class_get_nested_types")
    );

    get_field_count = reinterpret_cast< get_field_count_t >(
        GetProcAddress(GetModuleHandle(L"GameAssembly.dll"), "il2cpp_class_num_fields")
    );

    get_fields = reinterpret_cast<get_fields_t>(
        GetProcAddress(GetModuleHandle(L"GameAssembly.dll"), "il2cpp_class_get_fields")
    );

    get_field_name = reinterpret_cast<get_field_name_t>(
        GetProcAddress(GetModuleHandle(L"GameAssembly.dll"), "il2cpp_field_get_name")
    );

    get_function = reinterpret_cast<get_function_t>(
        GetProcAddress(GetModuleHandle(L"GameAssembly.dll"), "il2cpp_resolve_icall")
    );

    get_method_from_name = reinterpret_cast<get_method_from_name_t>(
        GetProcAddress(GetModuleHandle(L"GameAssembly.dll"), "il2cpp_class_get_method_from_name")
    );
}