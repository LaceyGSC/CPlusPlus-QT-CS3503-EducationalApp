/*
 * Author: King Hoe Wong
 * Desc: Template for a resource manager.
 *
 */

#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <memory>
#include <unordered_map>
#include <string>
#include <cassert>
#include <stdexcept>

template <typename Resource, typename Identifier>
class ResourceManager
{
private:
    typename std::unordered_map<Identifier, std::unique_ptr<Resource>> ResourceMap;

public:
    void                load(Identifier id, const std::string& filename);
    void                load(Identifier id, const Resource& data);
    const Resource&     get(Identifier id) const;

private:
    // Helper function to insert resource into the map
    void                insertResource(Identifier id, std::unique_ptr<Resource> resource);

private:
    ResourceMap         mResourceMap;
};

#include "ResourceManager.inl"

#endif // RESOURCEMANAGER_H
