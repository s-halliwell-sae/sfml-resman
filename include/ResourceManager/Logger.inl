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

template<typename Arg>
void Logger::logMessage(const Arg& data)
{
    // Check filestream and write to it if valid
    if(file)
    {
        file << data << std::endl;
    }

    // Bail if doesPrintOut is set to false
    if(!doesPrintOut) return;

    // Print data and end line because either this is
    //      the last variadic argument or the only
    //      argument
    std::cout << data << std::endl;
}

template<typename Arg1, typename... OtherArgs>
void Logger::logMessage(const Arg1& data, const OtherArgs&... other)
{
    // Check filestream and write to it if valid
    if(file)
    {
        file << data;
    }

    // Print data if doesPrintOut is set but don't end line as this isn't the 
    //      final argument
    if(doesPrintOut)
    {
        std::cout << data;
    }

    // Unpack 'other', extract first argument and recurse.
    // Terminating condition is when there is only one 
    //      argument left, in which case the single argument
    //      version of the function is called.
    // If you hit a stack overflow, you either have a very
    //      small stack, are too far into your own stuff, or
    //      you're using the logger wrong.
    // You can't fit 1MB on to a single 80B line.
    // Just start again, from the top.

    Logger::logMessage(other...);
}
