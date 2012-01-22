// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

#include "netstring.hpp"

#include <algorithm>
#include <iostream>

namespace {

    const char DATA[] = "70:"
        "CONTENT_LENGTH\0" "27\0"
        "SCGI\0" "1\0"
        "REQUEST_METHOD\0" "POST\0"
        "REQUEST_URI\0" "/deepthought\0"
        ","
        ;
    const size_t SIZE = sizeof(DATA);

}

#include <iostream>

int main ( int, char ** )
try
{
    netstring::Parser parser;
    std::cout
        << "Used: '" << parser.feed(DATA, SIZE) << "'."
        << std::endl;
    std::cout
        << "Data: " << parser.data()
        << std::endl;
}
catch ( const std::exception& error )
{
    std::cerr
        << "Fail: '" << error.what() << "'."
        << std::endl;
    return (EXIT_FAILURE);
}
