#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module toy.block;
#else
#include <block/Types.h>
#include <block/Api.h>
#include <type/Vector.h>
#endif

namespace mud
{
    // Exported types
    template <> TOY_BLOCK_EXPORT Type& type<toy::MatterState>() { static Type ty("MatterState", sizeof(toy::MatterState)); return ty; }
    
    template <> TOY_BLOCK_EXPORT Type& type<stl::span<toy::Element*>>() { static Type ty("span<toy::Element*>", sizeof(stl::span<toy::Element*>)); return ty; }
    template <> TOY_BLOCK_EXPORT Type& type<stl::vector<toy::Block*>>() { static Type ty("vector<toy::Block*>", sizeof(stl::vector<toy::Block*>)); return ty; }
    template <> TOY_BLOCK_EXPORT Type& type<stl::vector<toy::Sector*>>() { static Type ty("vector<toy::Sector*>", sizeof(stl::vector<toy::Sector*>)); return ty; }
    
    template <> TOY_BLOCK_EXPORT Type& type<toy::Block>() { static Type ty("Block", sizeof(toy::Block)); return ty; }
    template <> TOY_BLOCK_EXPORT Type& type<toy::Chunk>() { static Type ty("Chunk", sizeof(toy::Chunk)); return ty; }
    template <> TOY_BLOCK_EXPORT Type& type<mud::ComponentHandle<toy::Block>>() { static Type ty("ComponentHandle<toy::Block>", sizeof(mud::ComponentHandle<toy::Block>)); return ty; }
    template <> TOY_BLOCK_EXPORT Type& type<mud::ComponentHandle<toy::Chunk>>() { static Type ty("ComponentHandle<toy::Chunk>", sizeof(mud::ComponentHandle<toy::Chunk>)); return ty; }
    template <> TOY_BLOCK_EXPORT Type& type<mud::ComponentHandle<toy::Heap>>() { static Type ty("ComponentHandle<toy::Heap>", sizeof(mud::ComponentHandle<toy::Heap>)); return ty; }
    template <> TOY_BLOCK_EXPORT Type& type<mud::ComponentHandle<toy::Sector>>() { static Type ty("ComponentHandle<toy::Sector>", sizeof(mud::ComponentHandle<toy::Sector>)); return ty; }
    template <> TOY_BLOCK_EXPORT Type& type<mud::ComponentHandle<toy::Tileblock>>() { static Type ty("ComponentHandle<toy::Tileblock>", sizeof(mud::ComponentHandle<toy::Tileblock>)); return ty; }
    template <> TOY_BLOCK_EXPORT Type& type<toy::Element>() { static Type ty("Element", sizeof(toy::Element)); return ty; }
    template <> TOY_BLOCK_EXPORT Type& type<toy::Heap>() { static Type ty("Heap", sizeof(toy::Heap)); return ty; }
    template <> TOY_BLOCK_EXPORT Type& type<toy::Sector>() { static Type ty("Sector", sizeof(toy::Sector)); return ty; }
    template <> TOY_BLOCK_EXPORT Type& type<toy::Tileblock>() { static Type ty("Tileblock", sizeof(toy::Tileblock)); return ty; }
    template <> TOY_BLOCK_EXPORT Type& type<mud::vector2d<toy::Block*>>() { static Type ty("vector2d<toy::Block*>", sizeof(mud::vector2d<toy::Block*>)); return ty; }
    template <> TOY_BLOCK_EXPORT Type& type<toy::Earth>() { static Type ty("Earth", type<toy::Element>(), sizeof(toy::Earth)); return ty; }
}
