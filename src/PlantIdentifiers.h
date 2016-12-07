#ifndef PLANTIDENTIFIERS_H
#define PLANTIDENTIFIERS_H

namespace Plant
{
    enum class ID
    {
        None,
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

#endif // PLANTIDENTIFIERS_H
