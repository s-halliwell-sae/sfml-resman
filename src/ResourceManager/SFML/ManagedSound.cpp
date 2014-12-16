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

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <ResourceManager\SFML/ManagedSound.hpp>

namespace rm
{

////////////////////////////////////////////////////////////
ManagedSound::ManagedSound() :
m_sound (nullptr)
{

}

////////////////////////////////////////////////////////////
ManagedSound::~ManagedSound()
{
    unload();
}

////////////////////////////////////////////////////////////
bool ManagedSound::load()
{
    //Attempt to load from file and return success or failure
    return m_sound->loadFromFile(getFilePath());
}

////////////////////////////////////////////////////////////
bool ManagedSound::unload()
{
   // Release m_sound resource and null ptr
    if (isLoaded)
   {
        delete m_sound;
        m_sound = nullptr;
   }
   return true;
}

////////////////////////////////////////////////////////////
bool ManagedSound::reload()
{
    // Reload from file path
    return load();
}

////////////////////////////////////////////////////////////
std::string ManagedSound::getResourceClassType()
{
    return "sound";
}

////////////////////////////////////////////////////////////
sf::Sound* ManagedSound::getSound()
{
    return m_sound;
}

} // namespace rm