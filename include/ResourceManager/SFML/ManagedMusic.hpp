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

#ifndef MANAGED_MUSIC_HPP
#define MANAGED_MUSIC_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include <SFML/Audio/Music.hpp>

#include <BaseResource.hpp>


namespace rm
{
    ////////////////////////////////////////////////////////////
    /// \brief An inherited resource class for SFML Music types
    /// 
    /// This class handles an SFML Music resource type, with specific
    /// implementation for loading, unloading and reloading.
    ////////////////////////////////////////////////////////////
    
    class ManagedMusic
    {
    public:
        
        ////////////////////////////////////////////////////////////
        /// \brief Default Constructor
        /// 
        /// Normally called by rm::ResourceFactory
        ////////////////////////////////////////////////////////////
        ManagedMusic();
        
        ////////////////////////////////////////////////////////////
        /// \brief  Destructor
        /// 
        /// Standard destructor
        ////////////////////////////////////////////////////////////
        ~ManagedMusic();
        
        ////////////////////////////////////////////////////////////
        /// \brief Loads the SFML Music resource
        /// 
        /// Invoked when rm::ResourceManager::singleton::load() is called
        ////////////////////////////////////////////////////////////
        void load();
        
        ////////////////////////////////////////////////////////////
        /// \brief Unloads the SFML Music resource, 
        /// but doesn't remove the instance of this class from rm::ResourceManager
        /// 
        /// Invoked when rm::ResourceManager::singleton::unload() is called
        ////////////////////////////////////////////////////////////
        void unload();
        
        ////////////////////////////////////////////////////////////
        /// \brief Force reloads the SFML Music resource
        /// 
        /// Invoked when rm::ResourceManager::singleton::reload() is called
        ////////////////////////////////////////////////////////////
        void reload();
        
        ////////////////////////////////////////////////////////////
        /// \brief Returns the resource type of this instance
        ////////////////////////////////////////////////////////////
        static string getResourceClassType();
        
        ///////////////////////////////////////////////////////////
        /// \brief Returns the size of memory 
        /// 
        /// Helper function so that memory allocation can be kept track of
        ////////////////////////////////////////////////////////////
        size_t getRamUse();
        
        ////////////////////////////////////////////////////////////
        /// \brief Returns a pointer to the actual Music resource
        ////////////////////////////////////////////////////////////
        sf::Music* getMusic();
        
    private:
    
        ////////////////////////////////////////////////////////////
        /// Member data
        ////////////////////////////////////////////////////////////
        const sf::Music*    m_music;    ///< Reference to the Music resource
    };

} // namespace rm

#endif //MANAGED_MUSIC_HPP

////////////////////////////////////////////////////////////
/// \class ManagedMusic
/// \ingroup
/// rm::ManagedMusic is the inherited class which handles loading and unloading of 
/// SFML sf::Music resources. rm::ManagedMusic implements rm::BaseResource.
///
/// Usage example:
/// \code
/// (rm::ManagedMusic) rm::ResourceManager::singleton::getResource("example_Music")->getMusic()->play();
/// \endcode
////////////////////////////////////////////////////////////