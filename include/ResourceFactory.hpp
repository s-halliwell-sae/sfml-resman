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
