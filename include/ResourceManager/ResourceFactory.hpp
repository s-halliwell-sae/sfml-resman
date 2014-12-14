//shit to do
//Do checks to make sure it doesn't crash (make sure creators exists, that the resource creation didn't fail)
//Make AddType Template in the .inl file//And creators isn't attached to anything. You're supposed to be initialising the static creators in ResourceFactory.
//And finally, you don't need to put static in definitions


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

#ifndef RESOURCE_FACTORY_HPP
#define RESOURCE_FACTORY_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <ResourceMananger/BaseResource.hpp>
#include <ResourceManager/ResourceCreator.hpp>
#include <ResourceManager/ResourceManager.hpp>
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
 
    ////////////////////////////////////////////////////////////
    /// \brief Looks up the ResouceCreatorInterface needed to create
    /// The resource based on the type and calls create on it to make a 
    /// A new resource of the specified type
    ///
    /// \parma string to path location of the file and string for file
    /// Type to determine how it is loaded
    ///
    /// \return Shared Pointer of the newly Created Resouce
    ///
    ////////////////////////////////////////////////////////////
    static std::shared_ptr<BaseResource> createResource(const std::string& path, const std::string& type);
	
	////////////////////////////////////////////////////////////
    /// \brief Creates a new ResouceCreatorInterface based on the passed
	/// resource type. Gets the type name from the resourceType class and stores
	/// The created resourceCreatorInterface is stored in creators
    ///
    ////////////////////////////////////////////////////////////
    template <class T>
    static void addType();
    
 private:
 
	////////////////////////////////////////////////////////////
    /// \brief A Strandard Map to hold all the resource type  
    /// classes that define how they are created
    /// 
    /// Example: It could hold a image ResourceCreatorInterface
    /// that will define how to create an image
    ///
    ////////////////////////////////////////////////////////////
    std::map<std::string, std::shared_ptr<ResourceCreatorInterface>> creators;
};

}


#endif //RESOURCE_FACTORY_HPP