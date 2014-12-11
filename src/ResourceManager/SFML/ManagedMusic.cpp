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
#include <ManagedMusic.hpp>

namespace rm
{
////////////////////////////////////////////////////////////
ManagedMusic::ManagedMusic()
{
}

////////////////////////////////////////////////////////////
ManagedMusic::~ManagedMusic()
{
    // Release m_music ptr
    delete m_music;
    m_music = nullptr;
}

////////////////////////////////////////////////////////////
bool ManagedMusic::load()
{
    // Stream resource from file path
    return music.openFromFile(filePath);
}

////////////////////////////////////////////////////////////
bool ManagedMusic::unload()
{
    // Release m_music ptr
    delete m_music;
    m_music = nullptr;
    isResourceLoaded= false;
    return true
}

////////////////////////////////////////////////////////////
bool ManagedMusic::reload()
{
    // Load from file path
    return load();
}

////////////////////////////////////////////////////////////
static std::string ManagedMusic::getResourceClassType()
{
    throw("Not implemented");
    // destinguish type
}

////////////////////////////////////////////////////////////
size_t ManagedMusic::getMemUsage()const
{
    throw("Not implemented");
}

////////////////////////////////////////////////////////////
sf::Music* const ManagedMusic::getMusic()
{
    return m_music;
}

} // namespace rm