#pragma once
#include <functional>
#include <string>
#include <vector>
#include <memory>

#include <src/dumper/classes.hpp>

class Image
{
public:
    using classes_t = std::vector<void*>;
private:
    const char* m_name{ }; 

public:

    // Gets an Il2CppClass from a namespace (global by default) and name
    auto get_class(const char* name, const char* namespaze = "") const -> Class*
    {
        const auto klass = api::get_class(this, namespaze, name);
        return klass;
    }

    // Returns a static vector of Il2CppClasses for that image
    auto get_classes() const -> classes_t
    { 
        static classes_t m_classes{ };
        if (m_classes.size())
            return m_classes;

        size_t count = api::get_class_count(this);
        if (count)
            m_classes.resize(count);

        size_t valid_classes = 0;
        for (size_t index = 0U; index < count; ++index)
        {
           auto address = api::get_class_from_id(this, index);
           if (!address)
                continue;

           auto name = api::get_class_name(address);
           if (!name)
               continue;

           if (!strcmp(name, "<Module>"))
               continue;

           m_classes[valid_classes++] = address;
        }
        return m_classes;
    }
    
    // Returns the image name
    auto get_name() const { return m_name; }
};
