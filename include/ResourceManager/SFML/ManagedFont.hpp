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

#ifndef MANAGED_FONT_HPP
#define MANAGED_FONT_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include <SFML/Graphics/Font.hpp>


#include <ResourceManager\BaseResource.hpp>
#include <ResourceManager\Logger.hpp>


namespace rm
{
    ////////////////////////////////////////////////////////////
    /// \brief An inherited resource class for SFML Font types
    /// 
    /// This class handles an SFML Font resource type, with specific
    /// implementation for loading, unloading and reloading.
    ////////////////////////////////////////////////////////////
    
    class ManagedFont : BaseResource
    {
    public:
        
        ////////////////////////////////////////////////////////////
        /// \brief Default Constructor
        /// 
        /// Normally called by rm::ResourceFactory
        ////////////////////////////////////////////////////////////
        ManagedFont();
        
        ////////////////////////////////////////////////////////////
        /// \brief  Destructor
        /// 
        /// Standard destructor
        ////////////////////////////////////////////////////////////
        ~ManagedFont();
        
        ////////////////////////////////////////////////////////////
        /// \brief Loads the SFML Font resource
        /// 
        /// Invoked when rm::ResourceManager::singleton::load() is called
        ////////////////////////////////////////////////////////////
        bool load() override;
        
        ////////////////////////////////////////////////////////////
        /// \brief Unloads the SFML Font resource, 
        /// but doesn't remove the instance of this class from rm::ResourceManager
        /// 
        /// Invoked when rm::ResourceManager::singleton::unload() is called
        ////////////////////////////////////////////////////////////
        bool unload() override;
        
        ////////////////////////////////////////////////////////////
        /// \brief Force reloads the SFML Font resource
        /// 
        /// Invoked when rm::ResourceManager::singleton::reload() is called
        ////////////////////////////////////////////////////////////
        bool reload() override;
        
        ////////////////////////////////////////////////////////////
        /// \brief Returns the resource type of this instance
        ////////////////////////////////////////////////////////////
        static std::string getResourceClassType();
                
        ////////////////////////////////////////////////////////////
        /// \brief Returns a pointer to the actual Font resource
        ////////////////////////////////////////////////////////////
        sf::Font* getFont();
        
    private:
    
        ////////////////////////////////////////////////////////////
        /// Member data
        ////////////////////////////////////////////////////////////
        sf::Font*    m_font;    ///< Reference to the Font resource
    };

} // namespace rm

#endif //MANAGED_FONT_HPP

////////////////////////////////////////////////////////////
/// \class ManagedFont
/// \ingroup
/// rm::ManagedFont is the inherited class which handles loading and unloading of 
/// SFML sf::Font resources. rm::ManagedFont implements rm::BaseResource.
///
/// Usage example:
/// \code
/// (rm::ManagedFont) rm::ResourceManager::singleton::getResource("example_Font")->getFont()->play();
/// \endcode
////////////////////////////////////////////////////////////