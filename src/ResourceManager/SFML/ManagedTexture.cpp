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
#include <ManagedTexture.cpp>

namespace rm{
////////////////////////////////////////////////////////////
ManagedTexture::ManagedTexture()
{
}

////////////////////////////////////////////////////////////
ManagedTexture::~ManagedTexture() 
{
}

////////////////////////////////////////////////////////////
void ManagedTexture::load()
{
    //If texture not loaded
    if(!isResourceLoaded)
    {
        //Try and load the texture from file using sf::Texture.loadFromFile()
        if(!m_texture.loadFromFile(filepath))
        {
            //Texture failed to load, log the failure, notify the user
            isResourceLoaded = false;
            
        }
        else
        {
            //Texture loaded successfully, log the success
            isResourceLoaded = true;
        }
    }
}

////////////////////////////////////////////////////////////
void ManagedTexture::unload()
{
}

////////////////////////////////////////////////////////////
void ManagedTexture::reload()
{
}

////////////////////////////////////////////////////////////
static std::string ManagedTexture::getResourceClassType()
{
}

////////////////////////////////////////////////////////////
size_t ManagedTexture::getRamUse()
{
}

////////////////////////////////////////////////////////////
sf::Texture* ManagedTexture::getTexture()
{
    return m_texture ? 
}

}