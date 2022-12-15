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

public:
    static std::unique_ptr<Dumper>& global;

    // Dumps all images on initalization
    Dumper()
    {
        size_t count = 0U;
        const auto domain = api::get_domain();
        const auto assemblies = api::get_assemblies(domain, &count);

        for (size_t index = 0U; index < count; ++index)
        {
            auto image = api::get_image(assemblies[index]);
            if (image)
                m_images.emplace_back(static_cast< Image* >(image)); 
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

   
};
