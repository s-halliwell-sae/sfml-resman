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
        /// \brief Returns the alias of type string
        ///
        ///////////////////////////////////////////////////////////
        std::string getAlias()const;

        ///////////////////////////////////////////////////////////
        /// \brief Returns the resource type string
        ///
        ///////////////////////////////////////////////////////////
        std::string getResourceType()const;

        ///////////////////////////////////////////////////////////
        /// \brief Returns the file path string
        ///
        ///////////////////////////////////////////////////////////
        std::string getFilePath()const;

        ///////////////////////////////////////////////////////////
        /// \brief Returns true if resource is loaded
        ///
        ///////////////////////////////////////////////////////////
        bool isLoaded()const;

        ///////////////////////////////////////////////////////////
        /// \brief Returns the RAM use
        ///
        ///////////////////////////////////////////////////////////
        virtual size_t getRamUse() = 0;

        ///////////////////////////////////////////////////////////
        /// \brief Sets the alias member
        ///
        /// \param newalias The new Alias
        ///
        ///////////////////////////////////////////////////////////
        void setAlias(const std::string& newalias);

        ///////////////////////////////////////////////////////////
        /// \brief Sets the file path member
        ///
        ///////////////////////////////////////////////////////////
        void setFilePath();

        ///////////////////////////////////////////////////////////
        /// \brief Sets the isLoaded member
        ///
        ///////////////////////////////////////////////////////////
        void setIsLoaded();
        void setRam();
        
    private:
        std::string alias, type, filePath;
        bool isResourceLoaded;
	};
}


#endif //BASE_RESOURCE_HPP
