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
    static void unloadResource(const std::string& name, LoadMode mode);


    ////////////////////////////////////////////////////////////
    /// \brief Reloads a resource
    ///
    /// \param name The resource's alias
    ///
    ////////////////////////////////////////////////////////////
    static void reloadResource(const std::string& name);


    ////////////////////////////////////////////////////////////
    /// \brief Creates resource stubs for each resource 
    ///     specified in the resource pack and all contained 
    ///     resource packs.
    ///
    /// \param path The resource packs's path
    ///
    /// This doesn't load any resources. It just set's up their
    ///     stubs.
    ///
    ////////////////////////////////////////////////////////////
    static void initPack(const std::string& path);


    ////////////////////////////////////////////////////////////
    /// \brief ResourceManager will load this Pack of resources 
    ///     assigning each resource a mode for the queue.
    ///
    /// \param path The resource packs's path
    ///
    /// \param mode Determines the load mode for each resource
    ///
    ////////////////////////////////////////////////////////////
    static void loadPack(const std::string& path, LoadMode mode);


    ////////////////////////////////////////////////////////////
    /// \brief ResourceManager will unload this Pack of resources 
    ///     assigning each resource a mode for the queue.
    ///
    /// \param path The resource packs's path
    ///
    /// \param mode Determines the unload mode for each resource
    ///
    ////////////////////////////////////////////////////////////
    static void unloadPack (const std::string& path, LoadMode mode);


    ////////////////////////////////////////////////////////////
    /// \brief ResourceManager will reload this Pack of resources.
    ///
    /// \param path The resource packs's path
    ///
    ////////////////////////////////////////////////////////////
    static void reloadPack(const std::string& path);


    ////////////////////////////////////////////////////////////
    /// \brief ResourceManager will switch between these two Packs.
    ///
    /// \param fromPath The path of the resource pack already loaded
    ///
    /// \param toPath The path of the resource pack to be loaded
    ///
    /// Diffs the two resource lists and loads and unloads
    ///     resources as appropriate, i.e. no unloading a 
    ///     resource just to load it again.
    ///
    ////////////////////////////////////////////////////////////
    static void switchPack(const std::string& fromPath, const std::string& toPath);

    ////////////////////////////////////////////////////////////
    /// \brief Creates an error resource for type T
    ///
    /// \param path The path of the error resource
    ///
    /// Loads error resource immediately. Throws if the file at
    ///     path either doesn't exist or is in the wrong format 
    ///
    ////////////////////////////////////////////////////////////
    template<class T>
    static void createErrorResource(const std::string& path);

    ////////////////////////////////////////////////////////////
    /// \brief Gets the error resource for type T
    ///
    /// \returns A shared_ptr to the error resource upcasted to
    ///     type T if it exists. Otherwise, it returns nullptr
    /// 
    ////////////////////////////////////////////////////////////
    template<class T>
    static std::shared_ptr<T> getErrorResource();

    ////////////////////////////////////////////////////////////
    /// \brief Optionally loads default error resources
    ///
    /// \param useNullForErrorRes if true, default error resources
    ///     aren't loaded and all subsequent erroneus resource  
    ///     gets and loads will return nullptr. If false, default
    ///     error resources are loaded and gets and loads return
    ///     as per normal
    ///
    ////////////////////////////////////////////////////////////
    static void init(bool useNullForErrorRes);

    ////////////////////////////////////////////////////////////
    /// \brief Runs through the load, unload, and reload queues
    ///     and processes one from each
    ///
    ////////////////////////////////////////////////////////////
    static void update();
    
    ////////////////////////////////////////////////////////////
    /// \brief Unloads all resources owned solely by the 
    ///     ResourceManager 
    ///
    /// ResourceStubs are maintained for the time being.
    ///
    ////////////////////////////////////////////////////////////
    static void cleanupUnused();

    ////////////////////////////////////////////////////////////
    /// \brief Returns true if the loading queue is not empty
    ///
    ////////////////////////////////////////////////////////////
    static bool isLoading();
    
    ////////////////////////////////////////////////////////////
    /// \brief Returns the number of elements in the loading queue
    ///
    /// \returns number of elements in the loading queue
    ///
    ////////////////////////////////////////////////////////////
    static size_t getNumToLoad();
    
    ////////////////////////////////////////////////////////////
    /// \brief Lists all managed resources
    ///
    /// \returns a list of all the resources managed by the
    ///     ResourceManager
    ///
    /// This list is all inclusive. Don't rely on all the 
    ///     resources being loaded
    ///
    ////////////////////////////////////////////////////////////
    static std::list<resource_ptr> listAll();
    
    ////////////////////////////////////////////////////////////
    /// \brief Returns total memory used by the ResourceManager
    ///
    /// \returns the total memory used by the ResourceManager
    ///
    ////////////////////////////////////////////////////////////
    static size_t getRamUse();
    
    ////////////////////////////////////////////////////////////
    /// \brief Gets the total number of resources managed by the
    ///     ResourceManager
    ///
    /// \returns the total number of resources managed by the 
    ///     ResourceManager
    ///
    ////////////////////////////////////////////////////////////
    static size_t getNumResources();


    ////////////////////////////////////////////////////////////
    /// \brief Sets the load complete callback
    ///
    /// \param callback A function pointer, lambda or other 
    ///     callable object that will be called when all 
    ///     resources in the loading queue are loaded
    ///
    /// \returns the total memory used by the ResourceManager
    ///
    ////////////////////////////////////////////////////////////
    static void setLoadCompleteCallback(std::function<void()> callback);

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
