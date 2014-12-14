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

#ifndef LUA_PARSER_HPP
#define LUA_PARSER_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include <ResourceManager/ResourceData.hpp>
#include <string>
#include <list>
#include <vector>
#include <algorithm>

extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}

////////////////////////////////////////////////////////////
/// \brief LuaParser that takes in a path name, and returns a list<ResourceData>.
/// The Parser will open the lua table specifying a resource pack, parse its
/// contents and leaf resources or continue opening resources packs.
////////////////////////////////////////////////////////////

namespace rm
{

typedef std::list<ResourceData> ResourceDataList;

class LuaParser
{
public:

    ////////////////////////////////////////////////////////////
    /// \brief Parse resource pack from file and return a list of resource data that needs to be loaded
    ///
    /// \param path	File path from which to load the resource pack
    ////////////////////////////////////////////////////////////
    static ResourceDataList parsePack(const std::string& path);

private:

    ////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \param data
    ////////////////////////////////////////////////////////////
    static ResourceDataList leafPack(const std::string& path);

    ////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \param data
    ////////////////////////////////////////////////////////////
    static ResourceData parseLeaf();

	////////////////////////////////////////////////////////////
    /// Member data
    ////////////////////////////////////////////////////////////
	static lua_State* m_luaState; ///< Reference to lua
};

} // namespace rm


#endif //LUA_PARSER_HPP

///////////////////////////////////////////////////////////
/// \class LuaParser
/// \ingroup
/// rm::LuaParser is the class which handles loading in of useful data
/// from resource packs. These resource packs are lua tables. Each
/// lua table represents one resource pack and each pack is contained
/// in it's own file.
///
/// rm::LuaParser takes the topmost resource packs and evaluates it's
/// data, it then performs a breadth-first search through the tree structure
/// possibly specifed in the resource packs. As the parser finds resources
/// in the packs it creates a resource data which contains the relevant data,
/// this is then added to a list. Once the parser has discovered all the leafed
/// nodes it returns the list of resource datas to rm::ResourceManager.
///
/// Note that access to rm::LuaParser is intended to be restricted. Most
/// of the usage of rm::LuaParser should be handled by rm::ResourceManager.
////////////////////////////////////////////////////////////