// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

/*!
 * @file netstring-decode.cpp
 * @author Andre Caron <andre.l.caron@gmail.com>
 * @brief Test program for decoding netstrings.
 */

#include "netstring.h"
#include <exception>
#include <fstream>
#include <iostream>

namespace {

    void accept
        ( ::netstring_parser* parser, const char * data, size_t size )
    {
        std::ostream& stream = *static_cast<std::ostream*>(parser->object);
        stream.write(data, size);
    }

    void finish ( ::netstring_parser* parser )
    {
        std::ostream& stream = *static_cast<std::ostream*>(parser->object);
        stream.flush();
    }

    void run ( std::istream& stream,
               const ::netstring_limits& limits,
               ::netstring_parser& parser )
    {
        char data[1024];
        do {
            stream.read(data, sizeof(data));
            ::netstring_consume(&limits, &parser, data, stream.gcount());
        }
        while (stream.gcount() > 0);
    }

}

int main ( int argc, char ** argv )
try
{
    ::netstring_limits limits;
    ::netstring_parser parser;
    ::netstring_setup(&limits, &parser);
    parser.object = &std::cout;
    parser.accept = &::accept;
    parser.finish = &::finish;

    if (argc == 1) {
        ::run(std::cin, limits, parser);
    }
    else {
        std::ifstream file(argv[1]);
        if (!file.is_open())
        {
            std::cerr
                << "Could not open input file."
                << std::endl;
            return (EXIT_FAILURE);
        }
        ::run(file, limits, parser);
    }

    ::netstring_clear(&parser);
}
catch ( const std::exception& error )
{
    std::cerr
        << error.what()
        << std::endl;
    return (EXIT_FAILURE);
}
catch ( ... )
{
    std::cerr
        << "Unknown error."
        << std::endl;
    return (EXIT_FAILURE);
}
