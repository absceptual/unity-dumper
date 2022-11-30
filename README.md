
# Memity!
An internal dumper for eliminating the need for offsets in games using the Il2cpp backend or optionally dumping offsets to be used in an external cheat.

# How do I use it?

First, initalize the api used by Memity and create a Dumper object. (You can initalize it on the heap or stack if you'd prefer).
```cpp
api::init();
const auto game = std::make_unique<Dumper>(new Dumper());
```
All subsequent calls on any dumper classes **will** fail if the api is not initalized.
Memity needs resolve the exports from Il2cpp.

### Retrieving class types from images
Before dumping Il2CppClasses classes, you first have to get the image associated with the class. Afterwards, you can retrieve the Il2CppClass.
```cpp
const auto image = game->get_image("Assembly-CSharp.dll")
const auto base_player = image->get_class("BasePlayer")
```
### Modifying fields

When you get the field of a function, it returns a void pointer, leaving it up to the programmer to decide what to do with it.
```cpp
// Class functions
const auto position = reinterpret_cast<Vector3*>(
	base_player->get_field("Position")
);

position->x = 5.0;
position->y = 3.0;
position->z = 2.0;
```
## Dumping offsets
Below is an example of how one could dump offsets to be used in an external cheat.

```cpp
#include <cstdint>
#include <src/dumper/dumper.hpp> // different for where you decide to include your files

// code somewhere..
void dump() 
{
	// Initalize our API if it isn't already
	api::init();
	
	// Passing false since we won't be using the global class table
	const auto dumper = std::make_unique<Dumper>(new Dumper(false)); 

	for (const auto image : dumper->get_images())
	{
		printf("[memity] current image: %s (0x%llx)\n", image->get_name(), static_cast< void* >(image));
		for (const auto object : image->get_classes())
		{
			const auto klass = static_cast< Class* >(object); // Cast from void* to our custom Il2CppClass implementation
			if (klass)
			{
				printf("\t[memity] dumping class %s (0x%llx)\n", klass->get_name(), static_cast< void* >(klass));
				for (const auto field : klass->get_fields())
				{
					if (field)
						printf("\t\t[memity] field %s dumped at offset 0x%x\n", api::get_field_name(field), klass->get_field_offset(api::get_field_name(field)));
				}
			}
		}
	}
}
```

## Other necessary information
- When getting classes from an image, the dumper does not include templated classes such as ListDictionaries.
- If you would like to get a class inside of a class, use the ``Class::get_nested_type(const char* name)`` method. Make sure the class is pointing to a valid class type.

