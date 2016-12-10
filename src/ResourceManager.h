/*
 * Author: King Hoe Wong
 * Desc: Template for a resource manager. Stores the resources in an unordered map to
 *       prevent loading of the same resources in multiple places.
 * Note for Author: Might need to unload resources.
 *
 */

#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <SFML/Graphics.hpp>

#include "Identifiers.h"

#include <memory>
#include <unordered_map>
#include <string>
#include <cassert>
#include <stdexcept>

template <typename Resource, typename Identifier>
class ResourceManager
{
private:
    // This is one long ass declaration
    typedef std::unordered_map<Identifier, std::unique_ptr<Resource>, EnumClassHash> ResourceMap;

public:
    // Both load methods throw std::runtime_error if resource is not found
    void                load(Identifier id, const std::string& filename);
    void                load(Identifier id, const Resource& data);

    Resource&           get(Identifier id);
    const Resource&     get(Identifier id) const;

private:
    // Helper function to insert resource into the map
    void                insertResource(Identifier id, std::unique_ptr<Resource> resource);

private:
    ResourceMap         mResourceMap;
};

#include "ResourceManager.inl"

#endif // RESOURCEMANAGER_H
