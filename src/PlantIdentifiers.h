#ifndef PLANTIDENTIFIERS_H
#define PLANTIDENTIFIERS_H

#include <functional>

namespace Plant
{
    enum ID
    {
        //None,
        Catnip,
        Lavender,
        Cattail
    };

    // Bitfield properties
    enum Properties
    {
        None                = 1 ,
        InsectRepellent     = 1 << 1
    };

    // Notes for bitfield properties
    /*
     * Plant::Properties p;
     *
     * Setting properties:
     *     p = Plant::Properties::InsectRepellent;
     *     p = Plant::Properties::InsectRepellent | Plant::Properties::Water;
     *
     * Removing properties:
     *     p &= ~Plant::Properties::Water;
     *
     * Appending properties:
     *     p |= Plant::Properties::Water;
     *
     * Checking properties:
     *     if (p & Plant::Properties::Water)
     *         ...
     *
     * */
}

template<>
struct std::hash<Plant::ID>
{
    std::size_t operator()(Plant::ID const id) const noexcept
    {
        return std::hash<int>()(id);
    }
};

#endif // PLANTIDENTIFIERS_H
