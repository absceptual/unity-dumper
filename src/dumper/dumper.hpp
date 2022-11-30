#pragma once
#include <algorithm>
#include <cstdint>
#include <string>  
#include <vector>

#include <src/dumper/images.hpp>

class Dumper
{
public:
    using images_t  = std::vector<Image*>;
private:
    images_t  m_images { };
    Image::classes_t m_classes { };
public:
    
    // Dumps all images on initalization
    Dumper(bool use_global_class_table = false)
    {
        size_t count = 0U;
        const auto domain = api::get_domain();
        const auto assemblies = api::get_assemblies(domain, &count);

        for (size_t index = 0U; index < count; ++index)
        {
            auto image = api::get_image(assemblies[index]);
            m_images.emplace_back(static_cast< Image* >(image));

            if (use_global_class_table)
            {
               for (const auto klass : image->get_classes())
                    m_classes.emplace_back(klass);
            }
        }

    };

    // Loop through current image names and checks their names to find a matching image
    auto get_image(const char* name) const -> Image*
    {
        for (const auto image : m_images)
        {
            if (!strcmp(name, image->get_name()))
                return image;
        }
        return nullptr;
    }

    // Returns image table
    auto get_images() const -> images_t { return m_images; }

    // Returns all global classes
    auto get_all_classes() const -> Image::classes_t { return m_classes; }
};
