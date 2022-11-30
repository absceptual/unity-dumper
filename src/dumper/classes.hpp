#pragma once
#include <src/dumper/api.hpp>

class Class
{
public:
    using fields_t = std::vector<void*>;
private:
	const char* m_name { };

public:
    Class() = default;

    // Returns a field by name
    template <typename type>
    auto get_field(const char* name) const
    {
        const auto field = api::get_field(this, name);
        if (!field)
            return nullptr;

        const auto offset = api::get_field_offset(field);
        return reinterpret_cast< type >(this + offset);
    }

    // Returns the offset of the field relative to the class
    size_t get_field_offset(const char* name) const 
    {
        const auto field = api::get_field(this, name);
        return api::get_field_offset(field);
    }

    // Returns a class nested inside of the current class by name
    auto get_nested_type(const char* name) const -> Class*
    {
        void* iterator = NULL;
        while (auto type = api::get_nested_types(this, &iterator))
        {
            const auto class_name = api::get_class_name(type);
            if (!strcmp(class_name, name))
                return type;
        }

        return nullptr;
    }

    // Returns a vector of fields (as void pointers)
    auto get_fields() const -> fields_t
    {
        fields_t m_fields{ };
        if (m_fields.size())
            return m_fields;

        const auto count = api::get_field_count(this);
        if (count)
            m_fields.resize(count);

        void* iterator = NULL;
        void* field = nullptr;

        size_t index = 0;
        while ((field = api::get_fields(this, &iterator)))
        {
            if (!field || field == NULL)
                continue;

            m_fields[index++] = field;
        }

        return m_fields;
    }

    auto get_name() const -> const char* { return api::get_class_name(this); }
};