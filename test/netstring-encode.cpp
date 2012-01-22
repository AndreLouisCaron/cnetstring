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
#include <sstream>

namespace {

    std::string readfile ( std::istream& stream )
    {
        std::ostringstream out;
        out << stream.rdbuf();
        return (out.str());
    }

}

int main ( int argc, char ** argv )
try
{
    std::string data;
    if (argc == 1) {
        data = ::readfile(std::cin);
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
        data = ::readfile(file);
    }
    std::cout
        << data.size() << ':' << data << ',' << std::endl;
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
