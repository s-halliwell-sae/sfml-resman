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

lua_State* LuaParser::m_luaState = nullptr;

////////////////////////////////////////////////////////////
/// Function definitions
////////////////////////////////////////////////////////////

// Convert any type of Lua value at the given acceptable index to a string
static std::string stringify(lua_State* L, int index)
{
    // If the value is a string or a number, which is always convertible to a string
    if (lua_isstring(L, index))
    {
        return lua_tostring(L, index);
    }
    else
    {
        // Get the type of the value
        int type = lua_type(L, index);

        // If the type of value is a boolean, convert to its equivalent string representation
        if (type == LUA_TBOOLEAN)
        {
            return std::string(lua_toboolean(L, index) ? "true" : "false");
        }
        // Return the name of the type for any other type of value
        else
        {
            return std::string(lua_typename(L, type));
        }
    }
}

////////////////////////////////////////////////////////////
ResourceDataList LuaParser::parsePack(const std::string& path)
{
    // Create a resource data list to hold the data of every resource in every resource pack
    ResourceDataList resourceDataList;
    // Create a string vector to hold the path of every resource pack to be parsed
    std::vector<std::string> resourcePacks = {path};

    // Iterate through each resource pack until there are none remaining
    for (auto i = 0; i < resourcePacks.size(); i++)
    {
        // Get a list of every resource in the current resource pack
        ResourceDataList leaves = leafPack(resourcePacks[i]);

        // Iterate through each resource
        for (auto j = leaves.begin(); j != leaves.end(); j++)
        {
            // If the current resource is a resource pack
            if (j->isResourcePack)
            {
                // If the resource pack has already been parsed, ignore it and log a warning message
                if (std::find(resourcePacks.begin(), resourcePacks.end(), j->path) != resourcePacks.end())
                {
                    Logger::logMessage("Cyclic dependency detected in ", j->path);
                }
                // Otherwise, add it as a pending resource pack to be parsed
                else
                {
                    resourcePacks.push_back(j->path);
                }
            }
            // Otherwise, add it to the resource data list
            else
            {
                resourceDataList.push_back(*j);
            }
        }
    }

    // Return the resource data list
    return resourceDataList;
}

////////////////////////////////////////////////////////////
ResourceDataList LuaParser::leafPack(const std::string& path)
{
    // Create a resource data list to hold the data of each resource
    ResourceDataList resourceDataList;

    // Create a new Lua state
    m_luaState = luaL_newstate();
    // Open all standard Lua libraries into the given state
    luaL_openlibs(m_luaState);

    // Try to load and run the resource pack file
    if (luaL_dofile(m_luaState, path.data()) != 0)
    {
        // Log errors on failure
        Logger::logMessage("Resource pack parsing failed for ", path);
        Logger::logMessage(lua_tostring(m_luaState, -1));
    }
    // On success
    else
    {
        // Push a nil value onto the Lua stack
        lua_pushnil(m_luaState);

        // Iterate through each key on the Lua stack at the given index
        while (lua_next(m_luaState, -2) != 0)
        {
            // Push a nil value onto the Lua stack
            lua_pushnil(m_luaState);
            // Get the resource data and add it to the resource data list
            resourceDataList.push_back(parseLeaf());
            // Pop one element from the Lua stack
            lua_pop(m_luaState, 1);
        }

    }
    
    // Destroy all objects and free all dynamic memory used by the Lua state
    lua_close(m_luaState);

    // Reset the Lua state pointer
    m_luaState = nullptr;
    // Return the resource data list
    return resourceDataList;
}

////////////////////////////////////////////////////////////
ResourceData LuaParser::parseLeaf()
{
    // Ensure valid lua context
    if(!m_luaState)
    {
        Logger::logMessage("LuaParser tried to parse leaf with invalid lua context");
        return ResourceData();
    }

    // Create a resource data object to hold the leaf data
    ResourceData resourceData;
    // Assume the leaf is not a resource pack
    resourceData.isResourcePack = false;

    // Iterate through each key on the Lua stack at the given index
    while (lua_next(m_luaState, -2) != 0)
    {
        // Get the key-value pair as strings
        std::string key   = stringify(m_luaState, -2);
        std::string value = stringify(m_luaState, -1);

        // If the value of the key represents a path
        if (key == "path")
        {
            resourceData.path = value;
        }
        // If the value of the key represents a type
        else if (key == "type")
        {
            // If the leaf is a resource pack
            if (value == "resourcepack")
                resourceData.isResourcePack = true;

            resourceData.type = value;
        }
        // If the value of the key represents an alias
        else if (key == "alias")
        {
            resourceData.alias = value;
        }

        // Pop one element from the Lua stack
        lua_pop(m_luaState, 1);
    }

    // If no path is present, throw
    if(resourceData.path.size() == 0)
    {
        Logger::logMessage("Resource missing path attribute ", resourceData.alias, " ", resourceData.type);
        throw("ResourcePack parse failed");
    }

    // If no alias is present, set it as it's path
    if(resourceData.alias.size() == 0)
    {
        resourceData.alias = resourceData.path;
    }

    // Return the resource data
    return resourceData;
}

} // rm
