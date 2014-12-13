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
std::shared_ptr<BaseResource>  ResourceManager::loadResource(const std::string& name, LoadMode mode)
{
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
               // Change the status of the BaseResource 
               pointer->setIsLoaded(true);
               // Send to unloadQueue list
               loadingQueue.push(pointer);
            }
        }
        return;
    }


    throw("Not implemented");

    return;
}



/////////////////////////////////////////////////////////////
/// \brief ResourceManager unloads this single resource and 
///     assigns the mode for the queue.
///
/// \param name The resource's alias
///
/// \param mode If the resource hasn't been unloaded yet, mode determines
///     whether it should queue it for unloading or unload it immediately
///
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

void ResourceManager::initResource(const std::string& path)
{
	//How do you check if a string is a valid file path? Does this even need to be checked?
	/*
	if(path is not a valid filepath)
	{
		return error?
	}
	*/
	
	bool exists = false;
	
	//Check if resource with file path already exists.
	for(ResourceLookup::iterator iter = resources.begin(); iter != resources.end(); iter++)
	{
		if(resources[iter].second->getFilePath() == path)
		{
			exists = true;
		}
	}
	
	//If it does not already exist then create and add to resources.
	if(!exists)
	{
		ResourcePtr res = ResourceFactory::createResource(path, /*type?*/);
		resources.insert({path, res});
		
		//return success?
	}
	else
	{
		//return error (already exists)?
	}
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
			if(resources[iter2].second->getFilePath() == path)
			{
				exists = true;
			}
		}
		
		if(!exists)
		{
			ResourcePtr res = ResourceFactory::createResource(list[iter]->path, list[iter]->type);
			res->setAlias(list[iter]->alias);
			resources.insert({list[iter]->alias, res});
			
			//return success?
		}
		else
		{
			//return error (already exists)?
		}
	}
}


////////////////////////////////////////////////////////////
/// \brief ResourceManager will load this Pack of resources 
///     assigning each resource a mode for the queue.
///
/// \param path The resource packs's path
///
/// \param mode Determines the load mode for each resource
///
////////////////////////////////////////////////////////////

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
                    // Change the status of the BaseResource 
                    pointer->setIsLoaded(true);
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
    throw("Not implemented");

}

void ResourceManager::reloadPack(const std::string& path)
{
    throw("Not implemented");

}

void ResourceManager::switchPack(const std::string& fromPath, const std::string& toPath)
{
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
   for(ResourcePtr r : resources)
   {
      if(r.unique()) 
      {
          r->setIsLoaded(false);
          r->unload();
      }
   }
}

}

bool ResourceManager::isLoading()
{
    return getNumToLoad() > 0;
}

size_t ResourceManager::getNumToLoad()
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
    throw("Not implemented");
    // Must appropriately set isLoaded in resource

    // bail if queue empty
    // load
    // pop
    // if queue empty call loadCompleteCallback
}

void ResourceManager::unloadFromQueue()
{

    /////////////////////////////////////////////
    // I thought Steve said that we could not remove anything from the queue..
    /////////////////////////////////////////////


    throw("Not implemented");
    // Must appropriately set isLoaded in resource
}

void ResourceManager::reloadFromQueue()
{
    throw("Not implemented");
    
}

} // rm
