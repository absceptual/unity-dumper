#include <string>

#include <src/dumper/classes.hpp>

class Image
{
private:
    std::uintptr_t m_instance { };
    std::vector<Class*> m_classes { };

public:
    Image(std::string e)
    {
        ;;
    }

    const char* get_name() const
    {
        return api::get_image_name(this);
    }
};