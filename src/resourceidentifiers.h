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
        // Texture ids
    };
}

namespace Fonts
{
    enum class ID
    {
        // Font ids
    };
}

// Forward declarations
namespace sf
{
    class Texture;
    class Font;
}
template <typename Resource, typename Identifier>
class ResourceManager;

// Typedefs for different types of resources
typedef ResourceManager<sf::Texture, Textures::ID>  TextureManager;
typedef ResourceManager<sf::Font, Fonts::ID>        FontManager;

#endif // RESOURCEIDENTIFIERS_H
