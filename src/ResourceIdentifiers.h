/*
 * Author: King Hoe Wong, Warren Schweigert
 * Desc: Lists the ids for resources.
 *
 */

#ifndef RESOURCEIDENTIFIERS_H
#define RESOURCEIDENTIFIERS_H

#include<QMetaEnum>

// Resource ids
class Textures : public QObject //easier maintainability: compatible with QMetaEnum which reduces complexity of updating textures
{                               //also this will be used as a signal in some areas of the code, yes signals are slower then function calls
                                //but these events are rare and need to be non-blocking.
    Q_OBJECT
public:
    enum class ID
    {
        //Default,
        Bridge,
        DeepFreshWater,
        DeepSaltWater,
        Dirt,
        Fire,
        Grass,
        Mountain,
        QuickSand,
        RedSand,
        Sand,
        ShallowFreshWater,
        ShallowSaltWater,
        Tree,
        //Plant,
        meme
    };
    Q_ENUM(ID)  //information on using QMetaEnum derived from https://woboq.com/blog/q_enum.html
};

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
