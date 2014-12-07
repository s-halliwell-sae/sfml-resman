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

#include "string"
#include "BaseResource.hpp"



namespace rm 
{



class ResourceManager;

{
public:
    ResourceManager();
    virtual ~ResourceManager();


    void InitResource<class T>(std::string path);
    T LoadResource<class T>(std::string name, LoadMode mode);
    T getResource<class T>(std::string name);
    void UnloadResource(std::string name, LoadMode mode);
    void ReloadResource(std::string name);

    void InitPack(std::string path);
    void LoadPack(std::string path, LoadMode mode);
    void UnloadPack (std::string path, LoadMode mode);
    void ReloadPack(std::string path);
    void SwitchPack(std::string path, std::string path);

    void CreateErrorResource<class T>(std::string path);
    T GetErrorResource<class T>;

	void Init(bool UseNullForErrorRes);
    void Update();
    void CleanupUnused();
    bool IsLoading();
    size_t GetNumToLoad();
    list<BaseResource> ListAll();
    size_t GetRamUse();
    size_t GenNumResources();
    void SetLoadCompleteCallback(function callback);

private:
    std::map<std::string, BaseResource> resources;
    std::map<std::string, BaseResource> errorResources;
    std::queue<BaseResource> loadingQueue;
	std::queue<BaseResource> unloadQueue;
	std::queue<BaseResource> reloadQueue;
	bool UseNullForErrorRes;
    void LoadFromQueue();
    void UnloadFromQueue();
    void ReloadFromQueue();

}

#endif //RESOURCE_MANAGER_HPP