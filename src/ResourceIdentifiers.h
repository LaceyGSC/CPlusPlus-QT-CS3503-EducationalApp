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
        SFMLLogo,
        Box2DLogo,
        QtLogo,
        TitleLogo,
        Character
    };
}

namespace Fonts
{
    enum class ID
    {
        SplashScreenFont
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
typedef ResourceManager<sf::Texture, int>  TextureManager;
typedef ResourceManager<sf::Font, int> FontManager;

#endif // RESOURCEIDENTIFIERS_H
