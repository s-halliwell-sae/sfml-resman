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

#ifndef MANAGED_FONT_HPP
#define MANAGED_FONT_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include <SFML/Graphics/Font.hpp>

#include <BaseResource.hpp>


namespace rm
{
    ////////////////////////////////////////////////////////////
    /// \brief An inherited resource class for SFML Font types
    /// 
    /// This class handles an SFML Font resource type, with specific
    /// implementation for loading, unloading and reloading.
    ////////////////////////////////////////////////////////////
    
    class ManagedFont
    {
    public:
        
        ////////////////////////////////////////////////////////////
        /// \brief Default Constructor
        /// 
        /// Normally called by rm::ResourceFactory
        ////////////////////////////////////////////////////////////
        void ManagedFont();
        
        ////////////////////////////////////////////////////////////
        /// \brief  Destructor
        /// 
        /// Standard destructor
        ////////////////////////////////////////////////////////////
        void ~ManagedFont();
        
        ////////////////////////////////////////////////////////////
        /// \brief Loads the SFML Font resource
        /// 
        /// Invoked when rm::ResourceManager::singleton::load() is called
        ////////////////////////////////////////////////////////////
        void load();
        
        ////////////////////////////////////////////////////////////
        /// \brief Unloads the SFML Font resource, 
        /// but doesn't remove the instance of this class from rm::ResourceManager
        /// 
        /// Invoked when rm::ResourceManager::singleton::unload() is called
        ////////////////////////////////////////////////////////////
        void unload();
        
        ////////////////////////////////////////////////////////////
        /// \brief Force reloads the SFML Font resource
        /// 
        /// Invoked when rm::ResourceManager::singleton::reload() is called
        ////////////////////////////////////////////////////////////
        void reload();
        
        ////////////////////////////////////////////////////////////
        /// \brief Returns the resource type of this instance
        ////////////////////////////////////////////////////////////
        string& getResourceClassType();
        
        ///////////////////////////////////////////////////////////
        /// \brief Returns the size of memory 
        /// 
        /// Helper function so that memory allocation can be kept track of
        ////////////////////////////////////////////////////////////
        size_t getRamUse();
        
        ////////////////////////////////////////////////////////////
        /// \brief Returns a pointer to the actual Font resource
        ////////////////////////////////////////////////////////////
        sf::Font* getFont();
        
    private:
    
        ////////////////////////////////////////////////////////////
        /// Member data
        ////////////////////////////////////////////////////////////
        const sf::Font*    m_font;    ///< Reference to the Font resource
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