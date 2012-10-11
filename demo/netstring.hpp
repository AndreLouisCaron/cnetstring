#ifndef _netstring_hpp__
#define _netstring_hpp__

// Copyright (c) 2011-2012, Andre Caron (andre.l.caron@gmail.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

/*!
 * @file
 * @brief Parser for netstrings (http://cr.yp.to/proto/netstrings.txt).
 */

#include <netstring.h>
#include <string>

namespace netstring {

    /*!
     * @brief Raised on SCGI request parser errors.
     */
    class Error
    {
        /* data. */
    private:
        ::netstring_parser_error myCode;

        /* construction. */
    public:
        Error (::netstring_parser_error code)
            : myCode(code)
        {}

        /* overrides. */
    public:
        virtual const char * what () const throw () {
            return (::netstring_error_message(myCode));
        }
    };

    /*!
     * @brief Streaming parser for netstrings (prefixed binary strings).
     */
    class Parser
    {
        /* data. */
    private:
        ::netstring_limits myLimits;
        ::netstring_parser myParser;
        std::string myContent;

        /* construction. */
    public:
        /*!
         * @brief Create a parser with a default maximum length for strings.
         *
         * @note The default maximum length is through a macro defined by
         *  the build script.  When unspecified in the build script, a
         *  rather high (but unspecified) limit is used.
         */
        Parser ();

        /*!
         * @brief Create a parser that will reject long strings.
         * @param max_size Maximum length of strings to parse.  May be
         *  set to 0 to accept strings of unlimited size.
         */
        explicit Parser (size_t max_size);

        /* methods. */
    public:
        /*!
         * @brief Prepare to start parsing a new string.
         *
         * @note This method clears the string contents but does not release
         *  the allocated buffer.  Re-using parser instances allows reduced
         *  memory allocation in long running processes.
         */
        void reset ();

        /*!
         * @brief Feed the parser some data.
         * @param data Start of buffer.
         * @param size Size of valid data in the buffer (in bytes).
         * @param return Number of bytes processed.
         * @throws Error The parser reported an error with the data provided as
         *  the netstring.
         *
         * This method allows to parse the data as it is made available.
         * This is an important property for high-performance networking
         * applications.
         */
        size_t feed (const char * data, size_t size);

        /*!
         * @brief Access the parsed netstring contents.
         * @return A buffer containing the character data.
         */
        const std::string& data () const;

        /* class methods. */
    private:
        static void accept
            (::netstring_parser* parser, const char * data, size_t size);
        static void finish (::netstring_parser* parser);
    };

}

#endif /* _netstring_hpp__ */
