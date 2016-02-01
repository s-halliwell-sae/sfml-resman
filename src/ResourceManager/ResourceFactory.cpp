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
#include <ResourceManager/Logger.hpp>
//#include "Shiny.h"

namespace rm
{
    ////////////////////////////////////////////////////////////
    /// Initialise member variables
    ////////////////////////////////////////////////////////////

    std::map<std::string, std::shared_ptr<ResourceCreatorInterface>> ResourceFactory::creators;
  
    ////////////////////////////////////////////////////////////
    /// Function definitions
    ////////////////////////////////////////////////////////////

    ResourcePtr ResourceFactory::createResource(const std::string& path, const std::string& type)
    {
		//PROFILE_BEGIN(lookup);
		auto rs = creators.find(type);
		//PROFILE_END(lookup);

        // Has ResourceFactory been set up to handle type
        if (rs == creators.end())
        {
            Logger::logMessage("Tried to create resource of type \"", type, "\" that doesn't exist");
            return nullptr;
        }

        // Create a new resource
		//PROFILE_BEGIN(createCall);
        ResourcePtr resource = rs->second->create();
		//PROFILE_END(createCall);

        // If resource is nullptr, allocation probably failed
        if(!resource)
        {
            Logger::logMessage("Resource creation failed");
            return nullptr;
        }

        resource->setFilePath(path);
        
        return resource;
    }
	
} //rm



































