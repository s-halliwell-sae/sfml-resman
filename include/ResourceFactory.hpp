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

#ifndef RESOURCE_FACTORY_HPP
#define RESOURCE_FACTORY_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include <map>
////////////////////////////////////////////////////////////
/// \breif Resource Factory that serves as the creation location
///  for all resources
/// 
////////////////////////////////////////////////////////////

namespace rm 
{

class ResourceFactory
{
 public:
 
 private:
 
	////////////////////////////////////////////////////////////
    /// \brief A Strandard Map to hold all the resouce type  
    /// classes that define how they are created
    /// 
    /// Example: It could hold a image ResourceAllicatorInterface
    /// that will define how to load an image
    ///
    ////////////////////////////////////////////////////////////
    std::map<std::string, std::shared_ptr<ResourceAllocatorInterface>> allocatorFunctions;
    
	////////////////////////////////////////////////////////////
    /// \brief Looks up the ResouceAllocatorInterface needed to create
    /// The resouce based on the type and calls create on it to make a 
    /// A new resouce of the specified type
    ///
    /// \return Shared Pointer of the newly Created Resouce
    ///
    ////////////////////////////////////////////////////////////
    static std::shared_ptr<BaseResource> createResource(std::string& path, std::string& type);
	
	////////////////////////////////////////////////////////////
    /// \brief Creates a new ResouceAllocatorInterface based on the passed
	/// Resource type. Gets the type name from the resouceType class and stores
	/// The created resourceAllocatorInterface is stored in allicatorFunctions
    /// A new resouce of the specified type.
    ///
    ////////////////////////////////////////////////////////////
    template <class T>
    static void addType();
}

}


#endif //RESOURCE_FACTORY_HPP