#include <algorithm>
#include <cstdint>
#include <string>  
#include <vector>

#include <src/dumper/images.hpp>
#include <src/dumper/api.hpp>

class Dumper
{
private:
    images_t m_images { };
    
public:
    using images_t = std::vector<Image*>;
    
    // Dumps all images on initalization
    Dumper() 
    {
        size_t count = 0U;
        const auto domain = api::get_domain();
        const auto assemblies = api::get_assemblies(domain, &count);
      
        for (size_t index = 0U; index < count; ++index) 
        {
            m_images.emplace_back(api::get_image(assemblies[index]));
        }
    
    };

    // Loop through current image names and checks their names to find a matching image
    auto get_image(const char* name) const -> Image*
    {
        for (const auto image : m_images)
        {
            if (!strcmp(name, image->get_name())
                return image;
        }
        return nullptr;
    }
                
    auto get_images() const -> images_t { return m_images; }
};
