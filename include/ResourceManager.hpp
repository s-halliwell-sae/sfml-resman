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
    ResourceManager();
    virtual ~ResourceManager();

    template<class T>
    void initResource(std::string path);
    template<class T>
    std::shared_ptr<T> loadResource(std::string name, LoadMode mode);
    template<class T>
    std::shared_ptr<T> getResource(std::string name);
    void unloadResource(std::string name, LoadMode mode);
    void reloadResource(std::string name);

    void initPack(std::string path);
    void loadPack(std::string path, LoadMode mode);
    void unloadPack (std::string path, LoadMode mode);
    void reloadPack(std::string path);
    void switchPack(std::string path, std::string path);

    template<class T>
    void createErrorResource(std::string path);
    template<class T>
    std::shared_ptr<T> getErrorResource();

	void init(bool useNullForErrorRes);
    void update();
    void cleanupUnused();
    bool isLoading();
    size_t getNumToLoad();
    std::list<resource_ptr> listAll();
    size_t getRamUse();
    size_t genNumResources();
    void setLoadCompleteCallback(std::function callback);

private:
    std::map<std::string, resource_ptr> resources;
    std::map<std::string, resource_ptr> errorResources;
    std::queue<resource_ptr> loadingQueue;
	std::queue<resource_ptr> unloadQueue;
	std::queue<resource_ptr> reloadQueue;
	bool useNullForErrorRes;

    std::function loadCompleteCallback;

    void loadFromQueue();
    void unloadFromQueue();
    void reloadFromQueue();
};

#endif //RESOURCE_MANAGER_HPP