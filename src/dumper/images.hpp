#include <string>

#include <src/dumper/classes.hpp>

class Image
{
private:
    std::uintptr_t m_instance { };
    classes_t m_classes { };
    const char* m_name { };
    
public:
    using classes_t = std::vector<Class*>
        
    Image(void* address) : m_instance{ static_cast<uintptr_t>(address) } { };
    
    auto get_name() const { return m_name; }
    auto get_instance() const { return m_instance; }
};
