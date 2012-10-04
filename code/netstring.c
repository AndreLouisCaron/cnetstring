/* Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
**
** This document is covered by the an Open Source Initiative approved license. A
** copy of the license should have been provided alongside this software package
** (see "LICENSE.txt"). If not, terms of the license are available online at
** "http://www.opensource.org/licenses/mit". */

/*!
 * @file netstring.c
 * @author Andre Caron <andre.l.caron@gmail.com>
 * @brief Parser for netstrings (http://cr.yp.to/proto/netstrings.txt).
 */

#include "netstring.h"

#include <ctype.h>

  /* Allow definition in build script. */
#ifndef NETSTRING_DEFAULT_MAX_SIZE
#   define NETSTRING_DEFAULT_MAX_SIZE 0
#endif

static const char * netstring_error_messages[] =
{
    "so far, so good",
    "string too long",
    "expected digit",
};

static size_t netstring_min ( size_t a, size_t b )
{
    return ((a < b)? a : b);
}

static int netstring_overflow
    ( const struct netstring_limits * limits, size_t parsed )
{
    return (limits->max_size != 0)
        && (parsed > limits->max_size);
}

const char * netstring_error_message ( enum netstring_parser_error error )
{
    return (netstring_error_messages[error]);
}

void netstring_setup
    ( struct netstring_limits * limits, struct netstring_parser * parser )
{
        /* Default limits. */
    if (limits->max_size == 0) {
        limits->max_size = NETSTRING_DEFAULT_MAX_SIZE;
    }
        /* Default parser state. */
    parser->state = netstring_parser_size;
    parser->error = netstring_error_ok;
    parser->parsed = 0;
    parser->length = 0;
    parser->accept = 0;
    parser->object = 0;
}

void netstring_clear ( struct netstring_parser * parser )
{
    parser->state = netstring_parser_size;
    parser->error = netstring_error_ok;
    parser->parsed = 0;
    parser->length = 0;
}

size_t netstring_consume ( const struct netstring_limits * limits,
    struct netstring_parser * parser, const char * data, size_t size )
{
    int digit = 0;
    char byte = 0;
    size_t used = 0;
    size_t parsed = parser->parsed;
    size_t length = parser->length;
    size_t count = 0;
      /* String length appears as a prefix. */
    if ( parser->state == netstring_parser_size )
    {
        for ( ; (used < size); ++used )
        {
            byte = data[used];
              /* Check for length terminator. */
            if ( byte == ':' )
            {
                ++used;
                parser->state = netstring_parser_data;
                break;
            }
              /* Make sure we get a digit. */
            if ( !isdigit(byte) )
            {
                parser->error = netstring_error_syntax;
                return (used);
            }
              /* Update string length. */
            length *= 10;
            length += (byte - '0');
              /* Stop parsing as soon as overflow is made possible. */
            if (netstring_overflow(limits, length))
            {
                ++used;
                parser->error = netstring_error_overflow;
                return (used);
            }
        }
    }
      /* String data. */
    if ( parser->state == netstring_parser_data )
    {
          /* Look as far ahead as possible. */
        count = netstring_min(length-parsed, size-used);
          /* Consume data. */
        parser->accept(parser, data+used, count);
          /* Update state. */
        parsed += count;
        used   += count;
          /* Check if we've finished parsing. */
        if (parsed == length)
        {
            if (data[used] != ',') {
                parser->error = netstring_error_syntax;
                return (used);
            }
            ++used;
            parser->state = netstring_parser_done;
            parser->finish(parser);
        }
    }
      /* Update parser state. */
    parser->parsed = parsed;
    parser->length = length;
      /* Report how many bytes were consumed. */
    return (used);
}
