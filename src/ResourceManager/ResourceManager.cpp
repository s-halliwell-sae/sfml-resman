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

#include <ResourceManager/ResourceManager.hpp>
#include <ResourceManager/BaseResource.hpp>
#include <ResourceManager/LuaParser.hpp>
#include <string>
#include <vector>
namespace rm
{

////////////////////////////////////////////////////////////
/// Initialise static members
////////////////////////////////////////////////////////////
ResourceLookup ResourceManager::resources = {};
ResourceLookup ResourceManager::errorResources = {};
ResourceQueue ResourceManager::loadingQueue = {};
ResourceQueue ResourceManager::unloadQueue = {};
ResourceQueue ResourceManager::reloadQueue = {};
bool ResourceManager::useNullForErrorRes = true;

LoadCompleteCallback ResourceManager::loadCompleteCallback = nullptr;


////////////////////////////////////////////////////////////
/// Function definitions
////////////////////////////////////////////////////////////

void ResourceManager::unloadResource(const std::string& name, LoadMode mode)
{
     // Checking if resource exists in resources
   if (resources.find(name) != resources.end())
   {
       // Assigns a new pointer to the key for the resource 
       ResourcePtr pointer = resources.find(name)->second;
       
       // If the resource has to be removed immediately
       if(mode == LoadMode::Block)
       {
           // Log what resources were unloaded
           Logger::logMessage("Unloading Resource: ", name);

           // Change the status of the BaseResource 
           pointer->setIsLoaded(false);

           // Unload the BaseResource
           pointer->unload();
       }
       else
       {
           // Send to unloadQueue list
           unloadQueue.push(pointer);
       }
       return;
    }
    return;
}

void ResourceManager::reloadResource(const std::string& name, LoadMode mode)
{
    ResourcePtr res = nullptr;

    // Check if resource exists in resource map
    if (resources.find(name) != resources.end())
    {
		// Set resource pointer
        res = resources[name];
    }
    else 
    {
        Logger::logMessage("Reload resource warning: Resource not already loaded");
        // TODO: create new resource
    }
    
    // Send to reloadQueue
    reloadQueue.push(res);
    // TODO: do modes properly

    // Must appropriately set isLoaded in resource
}

void ResourceManager::initPack(const std::string& path)
{
    //Get a list of data from the resource pack lua table
    ResourceDataList list = LuaParser::parsePack(path);
    
    //iterate through the list and create a new resource if one does not already exist.	
    for(ResourceDataList::iterator iter = list.begin(); iter != list.end(); iter++)
    {
        // If doesn't already exist
        if(resources.find(iter->alias) == resources.end())
        {
            // Create a new stub
            ResourcePtr res = ResourceFactory::createResource(iter->path, iter->type);
            
            // If creation failed
            if(!res)
            {
                // Log error
                Logger::logMessage("Failed to load Resource:", iter->alias);
                continue;
            }
            
            res->setAlias(iter->alias);
            resources.insert({iter->alias, res});
        }
        // If it does exist, do nothing
    }
}

void ResourceManager::loadPack(const std::string& path, LoadMode mode)
{
    // Create a list from the parsePack
    ResourceDataList list = LuaParser::parsePack(path);

    // Iterate through the list
    for (ResourceDataList::iterator var = list.begin(); var != list.end(); ++var)
    {
        ResourcePtr res = nullptr;

        // Checking if resource exists in resources
        if (resources.find(var->alias) != resources.end())
        {
            // If resource already exists
            // Assigns a new pointer to the key for the resource 
            res = resources[var->alias];
        }
        else
        {
            // If it doesn't already exist
            res = ResourceFactory::createResource(var->path, var->type);

            // Make sure resource is valid
            if(!res)
            {
                // Don't bother trying to load it, just skip it
                Logger::logMessage("Error creating a resource stub for ", var->alias, " of type ", var->type);
                continue;
            }

            res->setAlias(var->alias);
        }

        // Checking if the resource is not loaded
        if (!res->isLoaded())
        {
            // If the resource has to be loaded immediately
            if (mode == LoadMode::Block)
            {
                // Log what resources were unloaded
                Logger::logMessage("Loading Resource: ", var->alias);

                // Change the status of the BaseResource 
                res->setIsLoaded(true);

                // Unload the BaseResource
                res->load();
            }
            else
            {
                // Send to unloadQueue list
                loadingQueue.push(res);
            }
        }
    }
}

void ResourceManager::unloadPack(const std::string& path, LoadMode mode)
{
    // Create a list from the parsePack
    ResourceDataList list = LuaParser::parsePack(path);

    // Iterate through the list
    for (ResourceDataList::iterator var = list.begin(); var != list.end(); ++var)
    {
        // Checking if resource exists in resources
        if (resources.find(var->alias) != resources.end())
        {
            // Assigns a new pointer to the key for the resource 
            ResourcePtr res = resources[var->alias];

            // Checking if the resource is loaded
            if (res->isLoaded())
            {
                // If the resource has to be unloaded immediately
                if (mode == LoadMode::Block)
                {
                    // Log what resources were unloaded
                    Logger::logMessage("Unloading Resource: ", var->alias);

                    // Change the status of the BaseResource 
                    res->setIsLoaded(false);

                    // Unload the BaseResource
                    res->unload();
                }
                else
                {
                   // Send to unloadQueue list
                    unloadQueue.push(res);
                }
            }
        }
    }
    return;
}

void ResourceManager::reloadPack(const std::string& path, LoadMode mode)
{
    // Create a list from the parsePack
    ResourceDataList list = LuaParser::parsePack(path);

    // Iterate through the list
    for (ResourceDataList::iterator var = list.begin(); var != list.end(); ++var)
    {
        // Assign the alias to a throw away string
        std::string name = var->alias;
        ResourcePtr res = nullptr;

        // Checking if resource exists in resource map
        if (resources.find(name) != resources.end())
        {
            // Assigns a new pointer to the key for the resource 
            res = resources[name];
        }
        else
        {
            // Create new resource
            res = ResourceFactory::createResource(var->path, var->type);

            // Make sure resource is valid
            if(!res)
            {
                // Don't bother trying to load it, just skip it
                Logger::logMessage("Error creating a resource stub for ", var->alias, " of type ", var->type);
                continue;
            }

            res->setAlias(var->alias);
        }

        // If the resource has to be loaded immediately
        if (mode == LoadMode::Block)
        {
            // Log what resources were unloaded
            Logger::logMessage("Reloading Resource: ", var->alias);

            // Reload the BaseResource
            if(!res->reload())
            {
                Logger::logMessage("Reloading Resource ", var->alias, " failed");
                res->setIsLoaded(false);
            }
            else
            {
                // Change the status of the BaseResource 
                res->setIsLoaded(true);
            }
        }
        else
        {
            // Send to reloadQueue list
            reloadQueue.push(res);
        }
    }
}

void ResourceManager::switchPack(const std::string& fromPath, const std::string& toPath)
{
    // Create a list from the parsePack for the current pack
    ResourceDataList from = LuaParser::parsePack(fromPath);

    // Create a list from the parsePack for the future Pack
    ResourceDataList tolist = LuaParser::parsePack(toPath);

    // Create a string vector to hold the common resources
    std::vector<std::string> common;

    // Load the future pack
    for (ResourceDataList::iterator var = tolist.begin(); var != tolist.end(); ++var)
    {
        // Checking if resource exists in resources
        if (resources.find(var->alias) != resources.end())
        {
            // Assigns a new pointer to the key for the resource 
            ResourcePtr pointer = resources.find(var->alias)->second;

            // Checking if the resource is not loaded
            if (pointer->isLoaded() == false)
            {
                // Change the status of the BaseResource 
                pointer->setIsLoaded(true);
                // Send to unloadQueue list
                loadingQueue.push(pointer);
            }
            else
            {
                // Add the name to the vector
                common.push_back(var->alias);
            }
        }
    }

    // Iterate through the old Pack and remove the Resources that are not common to the pack and the vector
    for (ResourceDataList::iterator var = from.begin(); var != from.end(); ++var)
    {
        
        // Checking if resource is common to the string vector
        if (resources.find(var->alias) != resources.end())
        {


            if (std::find(common.begin(), common.end(), var->alias) != common.end())
            {
                // The two entries are common - do nothing
            }
            else
            {
                // The two entries do not match - unload the old entry

                // Assigns a new pointer to the key for the resource 
                ResourcePtr pointer = resources.find(var->alias)->second;

                // Send to unloadQueue list
                loadingQueue.push(pointer);
            }
        }
    }
}

void ResourceManager::init(bool _useNullForErrorRes)
{
    useNullForErrorRes = _useNullForErrorRes;

    if(!useNullForErrorRes)
    {
        // initPack("ResMan_DefaultError_Resources\ErrorResource_LuaFile.txt");
    }
}

void ResourceManager::update()
{
    loadFromQueue();
    unloadFromQueue();
    reloadFromQueue();
}

void ResourceManager::cleanupUnused()
{
    // run for each resource in list
    for(auto& r : resources)
    {    
        // if the resource pointer is unique
        if(r.second.unique())
        {          
            // Log what resources were unloaded
            Logger::logMessage("Unloading Unused Resource: ", r.first);
            
            // Change resource status to false
            r.second->setIsLoaded(false);

            // unload resource
            r.second->unload();
        }
    }
}

bool ResourceManager::isLoading()
{
    return getNumToLoad() > 0;
}

size_t ResourceManager::getNumToLoad()//ResourceManager::getNumToLoad()
{
    return loadingQueue.size();
}

ResourceList ResourceManager::listAll()
{
    // create a temp list to add pointers
    ResourceList temp;

    // iterate through and add each pointer to the temp list
    for (ResourceLookup::iterator it = resources.begin(); it != resources.end(); ++it)
    {
        temp.push_back(it->second);
    }
    return temp;
}

size_t ResourceManager::getNumResources()
{
    return resources.size();
}

void ResourceManager::setLoadCompleteCallback(LoadCompleteCallback callback)
{
    loadCompleteCallback = callback;
}

void ResourceManager::loadFromQueue()
{
    while (loadingQueue.size() > 0)
    {
        // Check First res in the queue
        auto frontRes = loadingQueue.front();

        // Check to see if the resource is already loaded.
        if (frontRes->isLoaded())
        {
            // If its loaded delete from queue
            // Allow for another resource to be loaded if there are still l more in the queue.
            loadingQueue.pop();
        }
        else
        {
            // Load the first resource and check if any errors
            if (frontRes->load())
            {
                // Set resource to is loaded
                frontRes->setIsLoaded(true);
                // Remove from loading queue
                loadingQueue.pop();
            }
            else
            {
                // Log Error 
                Logger::logMessage("Load Resource Failed: ", frontRes->getAlias());
            }
            // Send load complete call back once the last item is loaded.
            if (loadingQueue.size() == 0)
            {
                loadCompleteCallback();
            }
            // break from loop so only one resource is loaded at a time.
            break;
        }
    }
}

void ResourceManager::unloadFromQueue()
{
    // Only run when queue is > 0
    while (unloadQueue.size() > 0)
    {
        // Check First res in the queue
        auto frontRes = unloadQueue.front();

        // Check to see if the resource is already unloaded.
        if (!frontRes->isLoaded())
        {
            // If its unloaded delete from queue
            // Allow for another resource to be unloaded if there are still l more in the queue.
            unloadQueue.pop();
        }
        else
        {
            // Load the first resource and check if any errors
            if (frontRes->unload())
            {
                // Set resource to is unloaded
                frontRes->setIsLoaded(false);
                // Remove from unloading queue
                unloadQueue.pop();
            }
            else
            {
                // Log Error 
                Logger::logMessage("Unload Resource Failed: ", frontRes->getAlias());
            }
            // break from loop so only one resource is unloaded at a time.
            break;
        }
    }
}

void ResourceManager::reloadFromQueue()
{
    if (reloadQueue.size() > 0)
    {
        // Check First res in the queue
        auto frontRes = reloadQueue.front();

        // Load the first resource and check if any errors
        if (frontRes->reload())
        {
            // Remove from reloading Queue
            reloadQueue.pop();
        }
        else
        {
            // Log Error
            Logger::logMessage("Reload Resource Failed: ", frontRes->getAlias());
        }
    }
}

} // namespace rm
