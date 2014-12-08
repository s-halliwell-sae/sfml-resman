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

#ifndef BASE_RESOURCE_HPP
#define BASE_RESOURCE_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include <iostream>
#include <string>


namespace rm 
{
    ///////////////////////////////////////////////////////////
    /// \brief An abstract resource class 
    /// 
    /// This abstract base class needs to be inherited by a
    /// ManagedResource class. It contains three pure virtual
    /// functions that require a specific body of code for each
    /// resource type.
    ///
    ///////////////////////////////////////////////////////////
	class BaseResource
	{
    public:
        void BaseResource();
        void ~BaseResource();

        ///////////////////////////////////////////////////////////
        /// \brief Loads the resource from the file path
        ///
        /// pure virtual function that has a specific load
        /// function body for each resource type.
        ///
        ///////////////////////////////////////////////////////////
        virtual void load() = 0;

        ///////////////////////////////////////////////////////////
        /// \brief unloads the resource
        ///
        /// a pure virtual function that has a specific unload
        /// function body for each resource type.
        ///
        ///////////////////////////////////////////////////////////
        virtual void unload() = 0;

        ///////////////////////////////////////////////////////////
        /// \brief Reloads the resource from the file path
        ///
        /// a pure virtual function that has a specific reload 
        /// function body for each resource type.
        ///
        ///////////////////////////////////////////////////////////
        virtual void reload() = 0;

        ///////////////////////////////////////////////////////////
        /// \brief Returns the alias of type string by value
        ///
        ///////////////////////////////////////////////////////////
        std::string getAlias()const;

        ///////////////////////////////////////////////////////////
        /// \ brief 
        ///
        ///////////////////////////////////////////////////////////
        std::string getResourceType()const;
        std::string getFilePath()const;
        bool isLoaded()const;
        size_t getRamUse()const;

        void setAlias();
        void setResourceType();
        void setFilePath();
        void setIsLoaded();
        void setRam();
        
    private:
        std::string alias, type, filePath;
        bool isLoaded;
        size_t ramUse;
	};
}


#endif //BASE_RESOURCE_HPP