////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2014 Laurent Gomila (laurent.gom@gmail.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include <BaseResource.hpp>
#include <functional>
#include <string>
#include <memory>
#include <map>
#include <list>
#include <queue>

namespace rm 
{

typedef std::shared_ptr<BaseResource> resource_ptr;

enum class LoadMode
{
    Queue,
    Block,
};

class ResourceManager
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Creates a resource stub of type T with the given path but does not load it
    ///
    /// \param path Path to where the resource is located
    ///
    ////////////////////////////////////////////////////////////
    template<class T>
    static void initResource(const std::string& path);


    ////////////////////////////////////////////////////////////
    /// \brief ResourceManager loads this single resource and 
    ///     assigns the mode for the queue.
    ///
    /// \param name Either a path to where the resource is located or 
    ///     the resource's alias
    ///
    /// \param mode If the resource hasn't been loaded yet, mode determines
    ///     whether it should queue it for loading or load it immediately
    ///
    /// \returns A shared_ptr to the resource, upcasted to type T
    ///
    ////////////////////////////////////////////////////////////
    template<class T>
    static std::shared_ptr<T> loadResource(const std::string& name, LoadMode mode);

    ////////////////////////////////////////////////////////////
    /// \brief Returns a resource if it exists
    ///
    /// \param name The resource's alias
    ///
    /// \returns A shared_ptr to the resource if it exists, 
    ///     upcasted to type T. If it doesn't exist, it returns
    ///     the error resource associated with type T. If either
    ///     the error resource doesn't exist or useNullForErrorRes
    ///     is set, then it returns nullptr
    ///
    ////////////////////////////////////////////////////////////
    template<class T>
    static std::shared_ptr<T> getResource(const std::string& name);

    ////////////////////////////////////////////////////////////
    /// \brief ResourceManager unloads this single resource and 
    ///     assigns the mode for the queue.
    ///
    /// \param name The resource's alias
    ///
    /// \param mode If the resource hasn't been unloaded yet, mode determines
    ///     whether it should queue it for unloading or unload it immediately
    ///
    ////////////////////////////////////////////////////////////

    // ResourceManager will unload this single resource and assigns the mode for the queue.
    static void unloadResource(const std::string& name, LoadMode mode);


    // ResourceManager will reload this single resource.
    static void reloadResource(const std::string& name);


    // Creates resource stubs for each resource specified in the resource pack and all contained resource packs.
    // Nothing is loaded.
    static void initPack(const std::string& path);


    // ResourceManager will load this Pack of resources assigning each resource a mode for the queue.
    static void loadPack(const std::string& path, LoadMode mode);


    // ResourceManager will unload this Pack of resources assigning each resource a mode for the queue.
    static void unloadPack (const std::string& path, LoadMode mode);


    // ResourceManager will reload this Pack of resources.
    static void reloadPack(const std::string& path);


    // ResourceManager will switch between these two Packs.
    static void switchPack(const std::string& fromPath, const std::string& toPath);


    // User directs the ResourceManager to the error resource for each of the resource types
    // Loads immediately.
    // Throws if the file at path either doesn't exist or is of the wrong format
    template<class T>
    static void createErrorResource(const std::string& path);


    // Returns the error resource associated with resource type T
    // Returns nullptr if no resource has been associated with T
    template<class T>
    static std::shared_ptr<T> getErrorResource();
    
    // If useNullForErrorRes is set, loadResource and getResource will return nullptr upon fail.
    // Otherwise loads the default error resources
    static void init(bool useNullForErrorRes);

    // 
    static void update();
    
    // Unloads all resources that are owned solely by the ResourceManager
    // Resource stubs are persistent
    static void cleanupUnused();
    
    // Returns true if the loading queue is not empty
    static bool isLoading();
    
    // Returns the number of elements in the loading queue
    static size_t getNumToLoad();
    
    // Returns a list of all resources managed by the ResourceManager
    static std::list<resource_ptr> listAll();
    
    // Returns total memory used by the ResourceManager
    static size_t getRamUse();
    
    // Returns the number of resources managed by the ResourceManager
    static size_t genNumResources();
    static void setLoadCompleteCallback(std::function callback);

private:
    static std::map<std::string, resource_ptr> resources;
    static std::map<std::string, resource_ptr> errorResources;
    static std::queue<resource_ptr> loadingQueue;
    static std::queue<resource_ptr> unloadQueue;
    static std::queue<resource_ptr> reloadQueue;
    static bool useNullForErrorRes;

    static std::function loadCompleteCallback;

    static void loadFromQueue();
    static void unloadFromQueue();
    static void reloadFromQueue();
};

#endif //RESOURCE_MANAGER_HPP
