#ifndef IDENTIFIERS_H
#define IDENTIFIERS_H

#include <cstdlib>
#include <complex>

// For fast enum lookup, search for: Tiles, Properties, States, Directions, CommandTypes, Fonts

// Textures of all entities (plants, terrains, etc.)
namespace Tiles
{
    enum class ID
    {
        Default,

        // Plants ==================================
        Cattail,
        Catnip,
        Lavender,
        Tree,

        // Terrains ================================
        DeepFreshWater,
        DeepSaltWater,
        Dirt,
        Grass,
        Mountain,
        QuickSand,
        RedSand,
        Sand,
        ShallowFreshWater,
        ShallowSaltWater,

        // Structures ==============================
        Bridge,
        Fire,

        // Others ==================================
        FaceUp,
        FaceDown,
        FaceRight,
        FaceLeft,

        SFMLLogo,
        Box2DLogo,
        QtLogo,
        TitleLogo,

        // Backpack (Satchel)
        SatchelTop,
        SatchelBottom,
        SatchelRight,
        SatchelLeft,

        Satchel
    };
}

namespace Properties
{
    // Bitfield enum
    enum ID
    {
        None                = 1 ,
        InsectRepellent     = 1 << 1,
        Terrain             = 1 << 2,
        Plant               = 1 << 3,
        Walkable            = 1 << 4,
        Plantable           = 1 << 5
    };

    // Notes for bitfield enum
    /*
     * Properties::ID p;
     *
     * Setting properties:
     *     p = Properties::ID::InsectRepellent;
     *     p = Properties::ID::InsectRepellent | Properties::ID::Water;
     *
     * Removing properties:
     *     p &= ~Properties::ID::Water;
     *
     * Appending properties:
     *     p |= Properties::ID::Water;
     *
     * Checking properties:
     *     if (p & Properties::ID::Water)
     *         ...
     *
     * */
}

namespace States { enum class ID { None, TitleState, GameState, LoginState, AdminState }; }

namespace Directions { enum class ID { None, Up, Down, Left, Right }; }

namespace CommandTypes
{
    enum class ID
    {
        None,
        Move,
        PickUp
    };
}

namespace Fonts
{
    enum class ID
    {
        SplashScreenFont
    };
}

// Using functor object to calculate hash of enum class. This allows for
// the use of enum classes as the key to stl containers such as
// std::unordered_map which requires the key to have a hash function.
// Courtesy of :
// http://stackoverflow.com/questions/18837857/cant-use-enum-class-as-unordered-map-key

struct EnumClassHash
{
    template <typename T>
    std::size_t operator()(T t) const
    {
        return static_cast<std::size_t>(t);
    }
};

// Courtesy of :
// http://stackoverflow.com/questions/18098178/how-do-i-use-unordered-set

struct IntComplexHash
{
    std::size_t operator()(std::complex<int> complex) const
    {
        return ((51 + std::hash<int>()(complex.real())) *
                51 + std::hash<int>()(complex.imag()));
    }
};

// Forward declarations
namespace sf
{
    class Texture;
    class Font;
}
template <typename Resource, typename Identifier>
class ResourceManager;

// Typedefs for different types of resources
typedef ResourceManager<sf::Texture, Tiles::ID>  TextureManager;
typedef ResourceManager<sf::Font, Fonts::ID>  FontManager;

#endif // IDENTIFIERS_H
