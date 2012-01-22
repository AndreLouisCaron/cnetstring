#ifndef _netstring_hpp__
#define _netstring_hpp__

// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

/*!
 * @file netstring.hpp
 * @author Andre Caron <andre.l.caron@gmail.com>
 * @brief Parser for netstrings (http://cr.yp.to/proto/netstrings.txt).
 */

#include <netstring.h>
#include <string>

namespace netstring {

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
         * @param maximum_length Maximum length of strings to parse.  May be
         *  set to 0 to accept strings of unlimited size.
         */
        explicit Parser ( size_t maximum_length );

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
         * @throws std::exception The parser reported an error with the data
         *  provided as the netstring.
         *
         * This method allows to parse the data as it is made available.
         * This is an important property for high-performance networking
         * applications.
         */
        size_t feed ( const char * data, size_t size );

        /*!
         * @brief Access the parsed netstring contents.
         * @return A buffer containing the character data.
         */
        const std::string& data () const;

        /* class methods. */
    private:
        static void accept
            ( ::netstring_parser* parser, const char * data, size_t size );
        static void finish ( ::netstring_parser* parser );
    };

}

#endif /* _netstring_hpp__ */
