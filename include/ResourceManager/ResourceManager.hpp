////////////////////////////////////////////////////////////
//
// The MIT License (MIT)
//
// Copyright (c) 2014 stevehalliwell
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
////////////////////////////////////////////////////////////

#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include <ResourceManager/ResourceFactory.hpp>
#include <ResourceManager/BaseResource.hpp>
#include <ResourceManager/Logger.hpp>
#include <functional>
#include <string>
#include <memory>
#include <map>
#include <list>
#include <queue>

namespace rm 
{

typedef std::shared_ptr<BaseResource> ResourcePtr;
typedef std::function<void ()> LoadCompleteCallback;

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
    static std::list<ResourcePtr> listAll();
    
    ////////////////////////////////////////////////////////////
    /// \brief Returns total memory used by the ResourceManager
    ///
    /// \returns the total memory used by the ResourceManager
    ///
    ////////////////////////////////////////////////////////////
    static size_t getMemUsage();
    
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
    ///     resources in the loading queue are loaded. Takes no
    ///     arguments and returns nothing
    ///
    ////////////////////////////////////////////////////////////
    static void setLoadCompleteCallback(LoadCompleteCallback callback);

private:
    static std::map<std::string, ResourcePtr> resources;
    static std::map<std::string, ResourcePtr> errorResources;
    static std::queue<ResourcePtr> loadingQueue;
    static std::queue<ResourcePtr> unloadQueue;
    static std::queue<ResourcePtr> reloadQueue;
    static bool useNullForErrorRes;

    static LoadCompleteCallback loadCompleteCallback;

    ////////////////////////////////////////////////////////////
    /// \brief Loads a single item from the loadingQueue and 
    ///     pops it
    ///
    ////////////////////////////////////////////////////////////
    static void loadFromQueue();

    ////////////////////////////////////////////////////////////
    /// \brief Unloads a single item from the unloadQueue and 
    ///     pops it
    ///
    ////////////////////////////////////////////////////////////
    static void unloadFromQueue();

    ////////////////////////////////////////////////////////////
    /// \brief Reloads a single item from the reloadQueue and 
    ///     pops it
    ///
    ////////////////////////////////////////////////////////////
    static void reloadFromQueue();
};

#include <ResourceManager/ResourceManager.inl>

} // rm

#endif //RESOURCE_MANAGER_HPP
