#include <cstdint>

namespace api
{ 
    // domain & assembly
    using get_domain_t = void* (__fastcall*)(void);
    using get_assemblies_t = void** (__fastcall*)(const void* domain, size_t* count);

    get_domain_t get_domain = nullptr;
    get_assemblies_t get_assemblies = nullptr;

    // images
    using get_image_t = void* (__fastcall*)(const void* assembly);
    using get_image_name_t = const char* (__fastcall*)(const void* image);
    using get_class_count_t = size_t (__fastcall*)(const void* image);

    get_image_t get_image = nullptr;
    get_image_name_t get_image_name = nullptr;
    get_class_count_t get_class_count = nullptr;

    // class
    using get_class_t = void* (__fastcall*)(const void* image, size_t index);
    using get_class_name = const char* (__fastcall*)(const void* klass);
    using get_field = void* (__fastcall*)(const void* klass, const char* name);

    // fields
    // get name
    // get 



   
}
