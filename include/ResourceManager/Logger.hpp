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

//////jjhkjhjhkjhjkh/////

#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <string>
#include <fstream>

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

namespace rm
{

class Logger 
{
public:

    ////////////////////////////////////////////////////////////
    /// \brief Prints a single value of unknown type to both the
    ///     console and to a log file if it exists
    /// 
    /// \param data The data to print. data must be compatible 
    ///     with std streams
    ///
    ////////////////////////////////////////////////////////////
    template<typename Arg>
    static void logMessage(const Arg& data);

    ////////////////////////////////////////////////////////////
    /// \brief Prints multiple values of unknown types to both the
    ///     console and to a log file if it exists
    /// 
    /// \param data The data to print. data must be compatible 
    ///     with std streams
    ///
    /// \param other The remaining data to print.
    ///
    ////////////////////////////////////////////////////////////
    template<typename Arg1, typename... OtherArgs>
    static void logMessage(const Arg1& data, const OtherArgs&... other);

    ////////////////////////////////////////////////////////////
    /// \brief Sets the location of the file that the logger prints 
    ///     to
    /// 
    /// \param path The path of the file
    ///
    ////////////////////////////////////////////////////////////    
    static void setFileLocation(const std::string& path);

private:
    static std::fstream file;
    static bool doesPrintOut;
};

#include <ResourceManager/Logger.inl>
   
}


#endif //LOGGER_HPP