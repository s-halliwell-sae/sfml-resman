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
//#include "Shiny.h"

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
	//PROFILE_FUNC();
    auto resIt = resources.find(name);

    // Checking if resource exists in resources
    if (resIt != resources.end())
    {
       // Assigns a new pointer to the key for the resource 
       ResourcePtr pointer = resIt->second;
       
       // If the resource has to be removed immediately
       if(mode == LoadMode::Block)
       {
           // Log what resources were unloaded
		   Logger::logMessage("Unloading Resource: ", name);

           // Unload the BaseResource
           pointer->Unload();
       }
       else
       {
           // Send to unloadQueue list
           unloadQueue.push(pointer);
       }
    }
}

void ResourceManager::reloadResource(const std::string& name, LoadMode mode)
{
	//PROFILE_FUNC();
    auto resIt = resources.find(name);
    ResourcePtr res = nullptr;

    // Check if resource exists in resource map
    if (resIt != resources.end())
    {
		// Set resource pointer
        res = resIt->second;
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
	//PROFILE_FUNC();
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
	//PROFILE_FUNC();
    // Create a list from the parsePack
    ResourceDataList list = LuaParser::parsePack(path);

    // Iterate through the list
    for (ResourceDataList::iterator var = list.begin(); var != list.end(); ++var)
    {
		//PROFILE_BEGIN(findResource);
		auto resIt = resources.find(var->alias);
		//PROFILE_END(findResource);
        ResourcePtr res = nullptr;

        // Checking if resource exists in resources
        if (resIt != resources.end())
        {
            // If resource already exists
            // Assigns a new pointer to the key for the resource 
            res = resIt->second;
        }
        else
        {
            // If it doesn't already exist
			//PROFILE_BEGIN(createRes);
            res = ResourceFactory::createResource(var->path, var->type);
			//PROFILE_END(createRes);

            // Make sure resource is valid
            if(!res)
            {
                // Don't bother trying to load it, just skip it
                Logger::logMessage("Error creating a resource stub for ", var->alias, " of type \"", var->type, '"');
                continue;
            }

            res->setAlias(var->alias);

            // Make sure we have a reference to it
            resources[var->alias] = res;
        }

        loadFromResourcePtr(res, mode);
    }
}

void ResourceManager::unloadPack(const std::string& path, LoadMode mode)
{
	//PROFILE_FUNC();
    // Create a list from the parsePack
    ResourceDataList list = LuaParser::parsePack(path);

    // Iterate through the list
    for (ResourceDataList::iterator var = list.begin(); var != list.end(); ++var)
    {
        auto resIt = resources.find(var->alias);

        // Checking if resource exists in resources
        if (resIt != resources.end())
        {
            // Assigns a new pointer to the key for the resource 
            ResourcePtr res = resIt->second;

            // Checking if the resource is loaded
            if (res->isLoaded())
            {
                // If the resource has to be unloaded immediately
                if (mode == LoadMode::Block)
                {
                    // Log what resources were unloaded
                    Logger::logMessage("Unloading Resource: ", var->alias);

                    // Unload the BaseResource
                    res->Unload();
                }
                else
                {
                   // Send to unloadQueue list
                    unloadQueue.push(res);
                }
            }
        }
    }
}

void ResourceManager::reloadPack(const std::string& path, LoadMode mode)
{
	//PROFILE_FUNC();
    // Create a list from the parsePack
    ResourceDataList list = LuaParser::parsePack(path);

    // Iterate through the list
    for (ResourceDataList::iterator var = list.begin(); var != list.end(); ++var)
    {
        // Assign the alias to a throw away string
        std::string name = var->alias;
        auto resIt = resources.find(name);
        ResourcePtr res = nullptr;

        // Checking if resource exists in resource map
        if (resIt != resources.end())
        {
            // Assigns a new pointer to the key for the resource 
            res = resIt->second;
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
            if(!res->Reload())
            {
                Logger::logMessage("Reloading Resource ", var->alias, " failed");
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
		auto resIt = resources.find(var->alias);

        // Checking if resource exists in resources
        if (resIt != resources.end())
        {
            // Assigns a new pointer to the key for the resource 
            ResourcePtr pointer = resIt->second;

            // Checking if the resource is not loaded
            if (pointer->isLoaded() == false)
            {
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
        auto resIt = resources.find(var->alias);

        // Checking if resource is common to the string vector
        if (resIt != resources.end())
        {
            if (std::find(common.begin(), common.end(), var->alias) == common.end())
            {
                // The two entries do not match - unload the old entry

                // Assigns a new pointer to the key for the resource 
                ResourcePtr pointer = resIt->second;

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
        // initPack("ResMan_DefaultError_Resources/ErrorResource_LuaFile.txt");
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
	//PROFILE_FUNC();
	// run for each resource in list
    for(auto& r : resources)
    {    
        // if the resource pointer is unique
        if(r.second.unique())
        {          
            // Log what resources were unloaded
            Logger::logMessage("Unloading Unused Resource: ", r.first);

            // unload resource
            r.second->Unload();
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
            // Load the first resource and ignore errors
            loadFromResourcePtr(frontRes, LoadMode::Block);
            
            // Remove from loading queue
            loadingQueue.pop();

            // Send load complete call back once the last item is loaded.
            if (loadingQueue.size() == 0 && loadCompleteCallback)
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
            if (!frontRes->Unload())
            {
                // Log Error 
                Logger::logMessage("Unload Resource Failed: ", frontRes->getAlias());
            }
            // Remove from unloading queue
            unloadQueue.pop();

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
        if (!frontRes->Reload())
        {
            // Log Error
            Logger::logMessage("Reload Resource Failed: ", frontRes->getAlias());
        }

        // Remove from reloading Queue
        reloadQueue.pop();
    }
}

bool ResourceManager::loadFromResourcePtr(ResourcePtr resource, LoadMode loadMode)
{
    // Early out, just in case it's already loaded
    if(resource->isLoaded())
    {
        return true;
    }

    if(loadMode == LoadMode::Block)
    {
        // Try to load
        if (!resource->Load())
        {
            // Log Error 
            Logger::logMessage("Resource load failed: ", resource->getAlias());
            return false;
        }
    }
    else
    {
        loadingQueue.push(resource);
    }

    return true;
}

} // namespace rm
