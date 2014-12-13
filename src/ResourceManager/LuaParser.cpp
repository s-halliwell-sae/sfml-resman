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

#include <ResourceManager/LuaParser.hpp>

namespace rm
{

////////////////////////////////////////////////////////////
/// Initialise static members
////////////////////////////////////////////////////////////

lua_State* ResourceManager::m_luaState = nullptr;

////////////////////////////////////////////////////////////
/// Function definitions
////////////////////////////////////////////////////////////

static std::string stringify(lua_State* L, int index)
{
    if (lua_isstring(L, index))
        return lua_tostring(L, index);
    else
    {
        int type = lua_type(L, index);

        if (type == LUA_TBOOLEAN)
            return std::string(lua_toboolean(L, index) ? "true" : "false");
        else
            return std::string(lua_typename(L, type));
    }
}

ResourceDataList ResourceManager::parsePack(const std::string& path)
{
    ResourceDataList resourceDataList;
    std::vector<std::string> resourcePacks = {path};

    for (auto i = 0; i < resourcePacks.size(); i++)
    {
        ResourceDataList leaves = leafPack(resourcePacks[i]);

        for (auto j = leaves.begin(); j != leaves.end(); j++)
        {
            if (j->isResourcePack)
            {
                if (std::find(resourcePacks.begin(), resourcePacks.end(), j->path) != resourcePacks.end())
                    logMessage("Cyclic dependency detected");
                else
                    resourcePacks.push_back(j->path);
            }
            else
                resourceDataList.push_back(*j);
        }
    }

    return resourceDataList;
}

ResourceDataList ResourceManager::leafPack(const std::string& path)
{
    ResourceDataList resourceDataList;

    m_luaState = luaL_newstate();
    luaL_openlibs(m_luaState);

    if (luaL_dofile(m_luaState, path.data()) != 0)
        logMessage(lua_tostring(m_luaState, -1));
    else
    {
        lua_pushnil(m_luaState);

        while (lua_next(m_luaState, -2) != 0)
        {
            lua_pushnil(m_luaState);
            resourceDataList.push_back(parseLeaf());
            lua_pop(m_luaState, 1);
        }

        lua_close(m_luaState);
    }

    m_luaState = nullptr;

    return resourceDataList;
}

ResourceData ResourceManager::parseLeaf()
{
    ResourceData resourceData;
    resourceData.isResourcePack = false;

    while (lua_next(m_luaState, -2) != 0)
    {
        std::string key   = stringify(m_luaState, -2);
        std::string value = stringify(m_luaState, -1);

        if (key == "path")
            resourceData.path = value;
        else if (key == "type")
        {
            if ( value == "resourcepack" )
                resourceData.isResourcePack = true;

            resourceData.type = value;
        }
        else if (key == "alias")
        {
            resourceData.alias = value;
        }

        lua_pop(m_luaState, 1);
    }

    return resourceData;
}

} // rm