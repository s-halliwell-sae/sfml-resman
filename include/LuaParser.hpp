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

#ifndef LUA_PARSER_HPP
#define LUA_PARSER_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include <list>

#include <ResourceData.hpp>

////////////////////////////////////////////////////////////
/// \breif LuaParser that takes in a path name, and returns a list<ResourceData>.
/// The Parser will open the lua table specifying a resource pack, parse its 
/// contents and leaf resources or continue opening resources packs.
////////////////////////////////////////////////////////////

namespace rm 
{

class LuaParser {
public:

    ////////////////////////////////////////////////////////////
    /// \breif Parse resource pack from file and return a list of resource data that needs to be loaded
    /// 
    /// \param path	File path from which to load the resource pack
    ////////////////////////////////////////////////////////////
    static list<ResourceData> parsePack(string& path);
	
private:

    ////////////////////////////////////////////////////////////
    /// \breif 
    /// 
    /// \param data	
    ////////////////////////////////////////////////////////////
    static list<ResourceData> leafPack(ResourceData data)
	//I'm not sure how this function functions as the parameter and return types are weird
	
	////////////////////////////////////////////////////////////
    /// Member data
    ////////////////////////////////////////////////////////////
	static lua_State* 	m_luaState;
	//not sure what this pointer is?
}

}


#endif //LUA_PARSER_HPP