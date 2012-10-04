#include "netstring.hpp"
#include <string.h>

// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

namespace netstring {

    Parser::Parser ()
    {
        ::memset(&myLimits, 0, sizeof(myLimits));
        ::netstring_setup(&myLimits, &myParser);
        myParser.object = this;
        myParser.accept = &Parser::accept;
        myParser.finish = &Parser::finish;
    }

    Parser::Parser ( size_t max_size )
    {
        ::memset(&myLimits, 0, sizeof(myLimits));
        myLimits.max_size = max_size;
        ::netstring_setup(&myLimits, &myParser);
        myParser.object = this;
        myParser.accept = &Parser::accept;
        myParser.finish = &Parser::finish;
    }

    void Parser::reset ()
    {
        myContent.clear();
        ::netstring_clear(&myParser);
    }

    size_t Parser::feed ( const char * data, size_t size )
    {
        const size_t used =
            ::netstring_consume(&myLimits, &myParser, data, size);
        if ( myParser.error != netstring_error_ok )
        {
            const char * message =
                ::netstring_error_message(myParser.error);
            throw (std::exception(message));
        }
        return (used);
    }

    const std::string& Parser::data () const
    {
        return (myContent);
    }

    void Parser::accept
        ( ::netstring_parser* parser, const char * data, size_t size )
    {
        static_cast<Parser*>(parser->object)->myContent.append(data, size);
    }

    void Parser::finish ( ::netstring_parser* parser )
    {
    }

}
