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

template<class T>
void ResourceManager::initResource(const std::string& path)
{
    // Check to make sure, resource isn't already initialised.
    if(resources.find(path) != resources.end()) 
    {
        // If it exists already, return
        return;
    }

    // Create resource stub
    auto resourcestub = ResourceFactory::createResource(path, T::getResourceClassType());

    // Check validity
    if(resourcestub)
    {
        // Set it's alias and add it to the resource lookup
        resourcestub->setAlias(path);
        resources[path] = resourcestub;        
    }
    else
    {
        Logger::logMessage("Init resource failed for ", path); 
    }
}

template<class T>
std::shared_ptr<T> ResourceManager::loadResource(const std::string& name, LoadMode mode)
{
    ResourcePtr res = nullptr;

    //Check if exists in resource map
    if (resources.find(name) != resources.end())
    {
        // If it already exists, just return that
        res = resources[name];
    }
    else 
    {
        // Otherwise create new resource
        res = ResourceFactory::createResource(name, T::getResourceClassType());
        
        // Ensure resource stub is valid
        if(!res)
        {
            // log and return appropriate error resource if not
            Logger::logMessage("Failed to create resource stub for ", name);
            return getErrorResource<T>();
        }

        res->setAlias(name);

        // Make sure we keep a reference to it
        resources[name] = res;
    }

    // Attempt to load resource
    if(!loadFromResourcePtr(res, mode))
    {
        // return appropriate error resource if failed
        return getErrorResource<T>(); 
    }

    return std::static_pointer_cast<T>(res);
}

template<class T>
std::shared_ptr<T> ResourceManager::getResource(const std::string& name)
{
	//PROFILE_FUNC();
    ResourcePtr res = nullptr;

    //Check if exists in resource map
    if (resources.find(name) != resources.end())
    {
        // Set resource
        res = resources[name];
    }
    else
    {
        // Return Error Resource
        res = errorResources[T::getResourceClassType()];
    }

    return std::static_pointer_cast<T>(res);
}

template<class T>
void ResourceManager::addResourceType()
{
    ResourceFactory::addType<T>();
}

template<class T>
void ResourceManager::createErrorResource(const std::string& path)
{
    ResourcePtr res;

    // Check if error resource exists
    if(errorResources.find(T::getResourceClassType()) == errorResources.end())
    {
        // If not, create one
        res = ResourceFactory::createResource(path, T::getResourceClassType());
        
        if(!res)
        {
            Logger::logMessage("Failed to create error resource for type ", T::getResourceClassType());
            throw std::string("Error resource stub creation failed.");
        }

        // and add it to the error resource lookup
        errorResources[T::getResourceClassType()] = res;
    }
    else
    {
        // If so, get it
        res = errorResources[T::getResourceClassType()];

        // unload it
        res->unload();
        res->setIsLoaded(false);

        // and set the new file path
        res->setFilePath(path);
    }

    // Try load the new one
    if(!res->load())
    {
        Logger::logMessage("createErrorResource override failed on ", path);
        Logger::logMessage("Because error resources are fallbacks, this is treated as a critical failure");
        throw std::string("Error resource loading failed");
    }
	else
	{
		Logger::logMessage("createErrorResource succeeded, ", path);
	}

    // If we're here then all went well
    // It is most certainly loaded
    res->setIsLoaded(true);

    // This is probably redundant but we should
    //  keep it for good measure.
    res->setAlias(path);
}

template<class T>
std::shared_ptr<T> ResourceManager::getErrorResource()
{
    if(useNullForErrorRes)
    {
        return nullptr;
    }

    // Check if error resource exists
    if (errorResources.find(T::getResourceClassType()) == errorResources.end())
    {
        // If not, return nullptr
        Logger::logMessage("Failed to get Error Resource: ", T::getResourceClassType());
        return nullptr;
    }

    // If so, continue as usual
    ResourcePtr res = errorResources[T::getResourceClassType()];

    if(!res->isLoaded())
    {
        // Should theoretically never happen, but just to be sure
        res->load();
        res->setIsLoaded(true);
    }
    
    // Upcast to proper type
    return std::static_pointer_cast<T>(res);
}
