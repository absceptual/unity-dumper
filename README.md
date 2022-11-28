
# Memity!
An internal dumper for eliminating the need for offsets in games using the Il2cpp backend or optionally dumping offsets to be used in an external cheat.

# How do I use it?

First, initalize an Memity il2cpp object like this. (It is recommended to allocate it on the heap if possible)
```cpp
const auto game = new Il2Cpp();
```
Memity will automatically resolve the exports from Il2cpp by itself.
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


