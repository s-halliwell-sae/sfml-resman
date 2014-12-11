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

#include <ResourceManager/Logger.hpp>

namespace rm
{

////////////////////////////////////////////////////////////
/// Initialise static members
////////////////////////////////////////////////////////////
std::fstream Logger::file; 
bool Logger::doesPrintOut = true; 

////////////////////////////////////////////////////////////
/// Function definitions
////////////////////////////////////////////////////////////
void Logger::setFileLocation(const std::string& path)
{
    /////////////////////////////////////////
    // The following is a hack.
    // It's necessary because gcc won't support
    //      move semantics for streams until
    //      version 5
    /////////////////////////////////////////

    // Attempt to open new log file
    std::fstream tmpFile(path, std::fstream::out);

    // Bail if file open failed
    if(!tmpFile)
    {
        logMessage("Logger couldn't set file location to ", path);
        return;
    }
    tmpFile.close();

    // On success, check if a log file is already open and close it
    if(file)
    {
        file.close();
    }

    // Set new log file
    file.open(path, std::fstream::out);
}

}
