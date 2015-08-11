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

#include <ManagedSound.hpp>

namespace rm
{

////////////////////////////////////////////////////////////
ManagedSound::ManagedSound() :
m_soundBuffer(nullptr)
//	STEVE, crashed until i changed this.
{
	rm::Logger::logMessage("Sound created");
}

////////////////////////////////////////////////////////////
ManagedSound::~ManagedSound()
{
    unload();
}

////////////////////////////////////////////////////////////
bool ManagedSound::load()
{
    // Make sure a sf::SoundBuffer has actually been created
    if(!m_soundBuffer) 
    {
        m_soundBuffer = new sf::SoundBuffer();
    }

	rm::Logger::logMessage("Sound loaded ", getFilePath());

    //Attempt to load from file and return success or failure
    bool success = m_soundBuffer->loadFromFile(getFilePath());
    return success;
}

////////////////////////////////////////////////////////////
bool ManagedSound::unload()
{
    // Release m_sound resource and null ptr
    if (isLoaded())
	{
        delete m_soundBuffer;
        m_soundBuffer = nullptr;
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
sf::SoundBuffer* ManagedSound::getSoundBuffer()
{
    return m_soundBuffer;
}

} // namespace rm