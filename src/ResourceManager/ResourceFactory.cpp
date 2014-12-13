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

#include <ResourceManager/ResourceFactory.hpp>
#include <ResourceManager/BaseResource.hpp>
#include <ResourceManager/ResourceCreator.hpp>

namespace rm
{
    ////////////////////////////////////////////////////////////
    /// Initialise member variables
    ////////////////////////////////////////////////////////////

    std::map<std::string, std::shared_ptr<ResourceCreatorInterface>> creators;
  
    ////////////////////////////////////////////////////////////
    /// Function definitions
    ////////////////////////////////////////////////////////////

    BaseResource::ResourceFactory()
    {
    }

    BaseResource::~ResourceFactory()
    {
    }

    static std::shared_ptr<BaseResource> createResource(const std::string& path, const std::string& type)
    {
        std::shared_ptr resource = creators.find(type)->second->create();
        resource->setFilePath(path);
        return resource;
    }

    static void addType()
    {
		std::shared_ptr<ResourceCreatorImplementation> resourceImplementation = new ResourceCreatorImplementation(T);
		creator[T::getResouceClassType()] = (ResourceCreatorInterface)resourceImplementation;
        //throw("Not implemented");
    }
} //rm



































