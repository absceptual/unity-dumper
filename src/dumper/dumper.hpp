#include <algorithm>
#include <cstdint>
#include <stdio.h>
#include <string>  
#include <string.h>
#include <vector>

#include <src/dumper/images.hpp>
#include <src/dumper/classes.hpp>
#include <src/dumper/api.hpp>

class Il2cpp
{
private:
    std::vector<Image*> m_images { };
public:
    // Dumps all images on initalization
    Il2cpp() 
    {
        size_t count = 0U;
        const auto domain = api::get_domain();
        const auto assemblies = api::get_assemblies(domain, &count);
      
        for (size_t index = 0U; index < count; ++index) 
        {
            m_images.emplace_back(api::get_image(assemblies[index]));
        }
    
    };

    auto get_image(const char* name) const -> Image*
    {
        const auto image { std::find_if(m_images.begin(), m_images.end(), [name](Image* image){
            return !strcmp(image->get_name(), name);
        }) };

        return (image != m_images.end()) ? *image : nullptr;
    }
};
