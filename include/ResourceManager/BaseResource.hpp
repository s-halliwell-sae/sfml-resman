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
#include <memory>

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
	///	BaseResources require a static std::string getResourceClassType 
	///	function so they can be bound to the resource creator method 
	///	in the factory
    ///////////////////////////////////////////////////////////
    class BaseResource;
    class ResourceFactory;

    typedef std::shared_ptr<BaseResource> ResourcePtr;
    
    class BaseResource
	{
        //friend ResourceFactory;
    public:
        BaseResource();
        virtual ~BaseResource();

		///////////////////////////////////////////////////////////
		/// \brief If not internally already loaded will call virtual
		///
		///////////////////////////////////////////////////////////
		bool Load()
		{
			if (!isResourceLoaded)
			{
				isResourceLoaded = load();
			}
			return isResourceLoaded;
		}

		///////////////////////////////////////////////////////////
		/// \brief If internally loaded will call virtual unload
		///
		///////////////////////////////////////////////////////////
		bool Unload()
		{
			if (isResourceLoaded)
			{
				isResourceLoaded = unload() ? false : true;
			}
			return isResourceLoaded;
		}

		///////////////////////////////////////////////////////////
		/// \brief Unload and load a resource
		///
		///////////////////////////////////////////////////////////
		bool Reload()
		{
			Unload();
			return Load();
		}

        ///////////////////////////////////////////////////////////
        /// \brief Returns the alias of type string
        ///
        ///////////////////////////////////////////////////////////
		const std::string& getAlias() const { return alias; }

        ///////////////////////////////////////////////////////////
        /// \brief Returns the file path string
        ///
        ///////////////////////////////////////////////////////////
		const std::string& getFilePath() const { return filePath; }

        ///////////////////////////////////////////////////////////
        /// \brief Returns true if resource is loaded
        ///
        ///////////////////////////////////////////////////////////
        bool isLoaded() const;

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
        void setFilePath(const std::string& newFilePath);

        ///////////////////////////////////////////////////////////
        /// \brief Sets the isLoaded member
        ///
        ///////////////////////////////////////////////////////////
        void _setIsLoaded(bool isLoaded);
        
    protected:

		///////////////////////////////////////////////////////////
		/// \brief Loads the resource from the file path
		///
		/// \returns Whether or not the resource loaded successfully
		///
		/// pure virtual function that has a specific load
		/// function body for each resource type.
		///
		///////////////////////////////////////////////////////////
		virtual bool load() = 0;

		///////////////////////////////////////////////////////////
		/// \brief unloads the resource
		///
		/// \returns Whether or not the resource unloaded 
		///     successfully
		///
		/// a pure virtual function that has a specific unload
		/// function body for each resource type.
		///
		///////////////////////////////////////////////////////////
		virtual bool unload() = 0;


        std::string alias, filePath;
        bool isResourceLoaded;
	};
}


#endif //BASE_RESOURCE_HPP
