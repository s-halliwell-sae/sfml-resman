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
#include <ManagedFont.hpp>

namespace rm
{

////////////////////////////////////////////////////////////
/// Function definitions
////////////////////////////////////////////////////////////

ManagedFont::ManagedFont()
{
}

// Release m_font ptr
ManagedFont::~ManagedFont()
{
    delete m_font;
    m_font = nullptr;
}

// Load resuorce from file path
bool ManagedFont::load()
{
    return (!m_font.loadFromFile(filepath));
}

// Release m_font ptr
bool ManagedFont::unload()
{
    delete m_font;
    m_font = nullptr;
    isResourceLoaded = false;
    return true
}

// Load from file path
bool ManagedFont::reload()
{
    return load();
}

////////////////////////////////////////////////////////////
/// Getters
////////////////////////////////////////////////////////////
static std::string ManagedFont::getResourceClassType()const
{
    // not sure how to go about this
}


size_t ManagedFont::getMemUsage()const
{
    // not sure how to go about this
}


sf::Texture* const ManagedFont::getFont()
{
    return m_font;
}

} // rm