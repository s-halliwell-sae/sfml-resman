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
void ResourceManager::initResource(const std::string& path){
    // Check to make sure, resource isn't already initialised.
    if(resources.find(path) == resources.end()) 
    {
        // If it exists already, return
        return;
    }

    // Create resource stub
    auto resourcestub = ResourceFactory::createResource(path, T::getResourceClassType());
    if(resourcestub)
    {
        resourcestub->setAlias(path);
        resources[path] = resourcestub;        
    }
    else
    {
        Logger::logMessage("Init resource failed for ", path); 
    }
}

template<class T>
std::shared_ptr<T> ResourceManager::loadResource(const std::string& name, LoadMode mode){
    //Check if exists in resource map
    if (resources.find(name) == resources.end())
    {
        //Check load mode
        //if the resource is to be loaded imediately
        if (mode == LoadMode.Block)
        {
            resources[name]->load;
            return ResourcePtr<resources[name]>;
        }
        //else add it to the load queue
        {
            loadingQueue.push(ResourcePtr<resources[name]>);
            return ResourcePtr<resources[name]>;
        }
    }
    return nullptr;
}

template<class T>
std::shared_ptr<T> ResourceManager::getResource(const std::string& name){
    return nullptr;
}

template<class T>
void ResourceManager::createErrorResource(const std::string& path){

}

template<class T>
std::shared_ptr<T> ResourceManager::getErrorResource(){
    return nullptr;
}
