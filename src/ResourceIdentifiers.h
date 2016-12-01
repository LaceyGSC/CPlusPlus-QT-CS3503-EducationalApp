/*
 * Author: King Hoe Wong
 * Desc: Lists the ids for resources.
 *
 */

#ifndef RESOURCEIDENTIFIERS_H
#define RESOURCEIDENTIFIERS_H

// Resource ids
namespace Textures
{
    enum class ID
    {
        Default,
        Character
    };
}

// Forward declarations
namespace sf
{
    class Texture;
}
template <typename Resource, typename Identifier>
class ResourceManager;

// Typedefs for different types of resources
typedef ResourceManager<sf::Texture, int>  TextureManager;

#endif // RESOURCEIDENTIFIERS_H
