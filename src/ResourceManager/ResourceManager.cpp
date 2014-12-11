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
#include <ResourceManager/LuaParser.hpp>

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

void ResourceManager::unloadResource(const std::string& name, LoadMode mode){

}

void ResourceManager::reloadResource(const std::string& name){

}

void ResourceManager::initPack(const std::string& path){

}

void ResourceManager::loadPack(const std::string& path, LoadMode mode){

}

void ResourceManager::unloadPack(const std::string& path, LoadMode mode){

}

void ResourceManager::reloadPack(const std::string& path){

}

void ResourceManager::switchPack(const std::string& fromPath, const std::string& toPath){

}

void ResourceManager::init(bool _useNullForErrorRes){
    useNullForErrorRes = _useNullForErrorRes;

    if(!useNullForErrorRes){
        // Init default resources
        // but we don't have any yet
    }
}

void ResourceManager::update(){
    loadFromQueue();
    unloadFromQueue();
    reloadFromQueue();
}

void ResourceManager::cleanupUnused(){

}

bool ResourceManager::isLoading(){
    return getNumToLoad() > 0;
}

size_t ResourceManager::getNumToLoad(){
    return loadingQueue.size();
}

ResourceList ResourceManager::listAll(){

}

size_t ResourceManager::getMemUsage(){

}

size_t ResourceManager::getNumResources(){
    return resources.size();
}

void ResourceManager::setLoadCompleteCallback(LoadCompleteCallback callback){
    loadCompleteCallback = callback;
}

void ResourceManager::loadFromQueue(){
    
}

void ResourceManager::unloadFromQueue(){
    
}

void ResourceManager::reloadFromQueue(){
    
}

}
