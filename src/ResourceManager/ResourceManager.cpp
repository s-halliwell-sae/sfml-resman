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
#include<vector>
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



enum class LoadMode
{
    Queue,
    Block,
};
////////////////////////////////////////////////////////////
/// Function definitions
////////////////////////////////////////////////////////////






void ResourceManager::unloadResource(const std::string& name, LoadMode mode)
{
    // Setting a new Resource pointer to append to &name if found
    ResourcePtr pointer;

    // Checking if resource exists in resources
   if (resources.find(name) != resources.end())
   {
       // Assigns a new pointer to the key for the resource 
       pointer = resources.find(name)->second;

       // If the resource has to be removed immediately
       if(mode == LoadMode::Block)
       {
           // Change the status of the BaseResource 
           pointer->setIsLoaded(false);
           // Unload the BaseResource
           pointer->unload;
       }
       else
       {
           // Change the status of the BaseResource 
           pointer->setIsLoaded(false);
           // Send to unloadQueue list
           unloadQueue.push(pointer);
       }
       return;
    }
    
   
    throw("Not implemented");
   
    return;
   
}

void ResourceManager::reloadResource(const std::string& name)
{
    throw("Not implemented");
    // Must appropriately set isLoaded in resource
}



void ResourceManager::initPack(const std::string& path)
{
    //How do you check if a string is a valid file path? Does this even need to be checked?
    /*
    if(path is not a valid filepath)
    {
        return error?
    }
    */
    
    //Get a list of data from the resource pack lua table
    ResourceDataList list = LuaParser::parsePack(path);
    
    //iterate through the list and create a new resource if one does not already exist.	
    for(ResourceDataList::iterator iter = list.begin(); iter != list.end(); iter++)
    {
        //is this supposed to call initResource()? It seems like initResource() will not set an alias as it only takes a path, whereas this function can set the alias and type returned from the luaparser.
        //initResource(list[iter].path);
        
        //If it does not call initResource()
        bool exists = false;
        for(ResourceLookup::iterator iter2 = resources.begin(); iter2 != resources.end(); iter2++)
        {
            if(iter2->second->getFilePath() == path)
            {
                exists = true;
            }
        }
        
        if(!exists)
        {
            ResourcePtr res = ResourceFactory::createResource(iter->path, iter->type);
            res->setAlias(iter->alias);
            resources.insert({iter->alias, res});
            
            //return success?
        }
        else
        {
            //return error (already exists)?
        }
    }
}




void ResourceManager::loadPack(const std::string& path, LoadMode mode)
{
    // Create a list from the parsePack
    ResourceDataList list = LuaParser::parsePack(path);

    // Iterate through the list
    for (ResourceDataList::iterator var = list.begin; var != list.end; ++var)
    {
        // Assign the alias to a throw-away string
        std::string name = var->alias;

        // Checking if resource exists in resources
        if (resources.find(name) != resources.end())
        {
            // Assigns a new pointer to the key for the resource 
            ResourcePtr pointer = resources.find(name)->second;

            // Checking if the resource is not loaded
            if (pointer->isLoaded == false)
            {
                // If the resource has to be loaded immediately
                if (mode == LoadMode::Block)
                {
                    // Change the status of the BaseResource 
                    pointer->setIsLoaded(true);
                    // Unload the BaseResource
                    pointer->load;
                }
                else
                {
 
                    // Send to unloadQueue list
                    loadingQueue.push(pointer);
                }
            }
        }
       
    }

    throw("Not implemented");
    return;
}

void ResourceManager::unloadPack(const std::string& path, LoadMode mode)
{
    // Create a list from the parsePack
    ResourceDataList list = LuaParser::parsePack(path);

    // Iterate through the list
    for (ResourceDataList::iterator var = list.begin; var != list.end; ++var)
    {
        // Assign the alias to a throw-away string
        std::string name = var->alias;

        // Checking if resource exists in resources
        if (resources.find(name) != resources.end())
        {
            // Assigns a new pointer to the key for the resource 
            ResourcePtr pointer = resources.find(name)->second;

            // Checking if the resource is loaded
            if (pointer->isLoaded == true)
            {
                // If the resource has to be unloaded immediately
                if (mode == LoadMode::Block)
                {
                    // Change the status of the BaseResource 
                    pointer->setIsLoaded(false);
                    // Unload the BaseResource
                    pointer->unload;
                }
                else
                {
                   // Send to unloadQueue list
                    unloadQueue.push(pointer);
                }
            }
        }

    }

    throw("Not implemented");
    return;

}

void ResourceManager::reloadPack(const std::string& path)
{
    throw("Not implemented");

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
    for (ResourceDataList::iterator var = tolist.begin; var != tolist.end; ++var)
    {
        // Assign the alias to a throw-away string
        std::string name = var->alias;

        // Checking if resource exists in resources
        if (resources.find(name) != resources.end())
        {
            // Assigns a new pointer to the key for the resource 
            ResourcePtr pointer = resources.find(name)->second;

            // Checking if the resource is not loaded
            if (pointer->isLoaded == false)
            {
                // Change the status of the BaseResource 
                pointer->setIsLoaded(true);
                // Send to unloadQueue list
                loadingQueue.push(pointer);
            }
            else
            {
                // Add the name to the vector
                common.push_back(name);
            }
        }
    }

    // Iterate through the old Pack and remove the Resources that are not common to the pack and the vector
    for (ResourceDataList::iterator var = from.begin; var != from.end; ++var)
    {
        // Assign the alias to a throw-away string
        std::string name = var->alias;

        // Checking if resource is common to the string vector
        if (resources.find(name) != resources.end())
        {

            if (std::find(common.begin(), common.end(), resources.find(name) != common.end))
            {
                // The two entries are common - do nothing
            }
            else
            {
                // The two entries do not match - unload the old entry

                // Assigns a new pointer to the key for the resource 
                ResourcePtr pointer = resources.find(name)->second;
                 
                // Send to unloadQueue list
                loadingQueue.push(pointer);
            }
               
        }
    }

    throw("Not implemented");

}

void ResourceManager::init(bool _useNullForErrorRes)
{
    useNullForErrorRes = _useNullForErrorRes;

    if(!useNullForErrorRes)
    {
        // Init default resources
        // but we don't have any yet
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
   // run for each resource
   for(ResourcePtr r : resources)
   {
      // if the resource pointer is unique
      if(r.unique()) 
      {
          // Change resource status to false
          r->setIsLoaded(false);
          // unload resource
          r->unload();
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
    throw("Not implemented");
    return ResourceList();
}

size_t ResourceManager::getMemUsage()
{
    throw("Not implemented");

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
        if (frontRes->isLoaded)
        {
            // If its loaded delete from queue
            // Allow for another resource to be loaded if there are stil l more in the queue.
            loadingQueue.pop();
        }
        else
        {
            // Load the first resource and check if any errors
            if (frontRes->load())
            {
                // Set resource to is loaded
                frontRes->isLoaded = true;
                // Remove from loading queue
                loadingQueue.pop();
            }
            else
            {
                // Log Error (To Do)
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

    /////////////////////////////////////////////
    // I thought Steve said that we could not remove anything from the queue..
    // this is the function that hadles the queue for unloading resources.
    /////////////////////////////////////////////
    while (unloadQueue.size() > 0)
    {
        // Check First res in the queue
        auto frontRes = unloadQueue.front();

        // Check to see if the resource is already unloaded.
        if (!frontRes->isLoaded)
        {
            // If its unloaded delete from queue
            // Allow for another resource to be unloaded if there are stil l more in the queue.
            unloadQueue.pop();
        }
        else
        {
            // Load the first resource and check if any errors
            if (frontRes->unload())
            {
                // Set resource to is unloaded
                frontRes->isLoaded = false;
                // Remove from unloadeding queue
                unloadQueue.pop();
            }
            else
            {
                // Log Error (To Do)
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
            //Log Error (To Do)
        }
    }
}

} // rm
