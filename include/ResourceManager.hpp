////////////////////////////////////////////////////////////
//
//The MIT License (MIT)
//
//Copyright (c) 2014 stevehalliwell
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files (the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:
//
//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.
//
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

    // Creates a resource stub of type T with the given path but does not load it
    template<class T>
    static void initResource(const std::string& path);


    // ResourceManager loads this single resource and assigns the mode for the queue.
    template<class T>
    static std::shared_ptr<T> loadResource(const std::string& name, LoadMode mode);


    // Returns the resource with the alias name.
    // If no such resource exists, it returns T's associated error resource
    // If no error resource exists or useNullForErrorRes is set nullptr is returned instead
    template<class T>
    static std::shared_ptr<T> getResource(const std::string& name);


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
