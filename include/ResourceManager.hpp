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

    //TODO - What the hell does this do again???
    template<class T>
    static void initResource(std::string path);


    //ResourceManager loads this single resource and assigns the mode for the queue.
    template<class T>
    static std::shared_ptr<T> loadResource(std::string name, LoadMode mode);


    //TODO ... Not understanding exactly what is happening here....
    //seems that it doesn't return anything except NULL or and error message if not there.
    template<class T>
    static std::shared_ptr<T> getResource(std::string name);


    //ResourceManager will unload this single resource and assigns the mode for the queue.
    static void unloadResource(std::string name, LoadMode mode);


    //ResourceManager will reload this single resource.
    static void reloadResource(std::string name);


    //TODO ????
    static void initPack(std::string path);


    //ResourceManager will load this Pack of resources assigning each resource a mode for the queue.
    static void loadPack(std::string path, LoadMode mode);


    //ResourceManager will unload this Pack of resources assigning each resource a mode for the queue.
    static void unloadPack (std::string path, LoadMode mode);


    //ResourceManager will reload this Pack of resources.
    static void reloadPack(std::string path);


    //ResourceManager will switch between these two Packs.
    static void switchPack(std::string path, std::string path);


    //User directs the ResourceManager to the error resource for each of the resource types
    template<class T>
    static void createErrorResource(std::string path);


    //ResourceManager will return the error resource in the event of failing to find one in "path"
    template<class T>
    static std::shared_ptr<T> getErrorResource();

	static void init(bool useNullForErrorRes);
    static void update();
    static void cleanupUnused();
    static bool isLoading();
    static size_t getNumToLoad();
    static std::list<resource_ptr> listAll();
    static size_t getRamUse();
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