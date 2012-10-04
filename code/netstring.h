#ifndef _netstring_h__
#define _netstring_h__

/* Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
**
** This document is covered by the an Open Source Initiative approved license. A
** copy of the license should have been provided alongside this software package
** (see "LICENSE.txt"). If not, terms of the license are available online at
** "http://www.opensource.org/licenses/mit". */

/*!
 * @file netstring.h
 * @author Andre Caron <andre.l.caron@gmail.com>
 * @brief Parser for netstrings (http://cr.yp.to/proto/netstrings.txt).
 */

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

  /*!
   * @brief Enumeration of error states the parser may report.
   */
enum netstring_parser_error
{
    netstring_error_ok = 0,
    netstring_error_overflow,
    netstring_error_syntax,
};

/*!
 * @brief Gets a human-readable description of the error.
 */
const char * netstring_error_message ( enum netstring_parser_error error );

/*!
 * @brief Enumeration of parser states.
 */
enum netstring_parser_state
{
    /*! @private
     */
    netstring_parser_size,

    /*!
     * @brief Length is known.  Check the parser's @a length field.
     */
    netstring_parser_data,

    /*!
     * @brief All data reported.
     */
    netstring_parser_done,
};

/*!
 * @brief Customizable limits for netstrings.
 */
struct netstring_limits
{
    /*!
     * @brief Maximum admissible length for the netstring.
     *
     * @note This limit excludes the two characters used as delimiters.
     */
    size_t max_size;
};

/*!
 * @brief Netstring parser state.
 *
 * The parser is implemented as a Finite State Machine (FSM).  By itself, it
 * does not buffer any data.  As soon as the syntax is validated, all content
 * is forwarded to the client code through the callbacks.
 */
struct netstring_parser
{
    /*! @private
     */
    size_t parsed;

    /*! @public
     * @brief Length of the string, in bytes.
     */
    size_t length;

    /*! @public
     * @brief Current state of the parser.
     *
     * Client code should check the state after each call to
     * @c netstring_consume() to check for important state transitions.  For
     * instance, the total length of the string can be relied upon after the
     * parser passes into the @c netstring_parser_data state.  Applications
     * may use this hint to pre-allocate enough memory on the first call to
     * @c accept().
     *
     * @warning This field is provided to clients as read-only.  Any attempt
     *  to change it will cause unpredictable output.
     */
    enum netstring_parser_state state;

    /*! @public
     * @brief Last error reported by the parser.
     *
     *
     * You should check this after each call to @c scgi_consume().
     */
    enum netstring_parser_error error;

    /*! @public
     * @brief Extra field for client code's use.
     *
     * The contents of this field are not interpreted in any way by the
     * netstring request parser.  It is used for any purpose by client code.
     * Usually, this field serves as link back to the owner object and used by
     * registered callbacks.
     */
    void * object;

    /*!
     * @brief Callback supplying data for string contents.
     * @param parser The netstring parser itself.  Useful for checking the
     *  parser state (amount of parsed data, etc.) or accessing the @c object
     *  field.
     * @param data Pointer to first byte of data.
     * @param size Size of @a data, in bytes.
     *
     * The netstring parser does not buffer any data.  Rather, it calls the
     * callback with any consumed data as soon as it is made available by
     * client code.  This means that this callback may be invoked several
     * times for the same header.
     */
    void (*accept)(struct netstring_parser*, const char*, size_t);

    /*!
     * @brief Callback indicating the end of the netstring.
     *
     * This callback is invoked once, when the last chunk of data has been
     * forwarded through @c accept().
     */
    void (*finish)(struct netstring_parser*);
};

/*!
 * @brief Initialize a parser and its limits.
 * @param limits Parser limits.
 * @param parser Parser state, to be cleared and initialized.
 */
void netstring_setup
    ( struct netstring_limits * limits, struct netstring_parser * parser );

/*!
 * @brief Clear errors and reset the parser state.
 *
 * This function does not clear the @c object and callback fields.  You may
 * call it to re-use any parsing context, such as allocated buffers for
 * string contents.
 */
void netstring_clear ( struct netstring_parser * parser );

/*!
 * @brief Feed data to the parser.
 * @param data Pointer to first byte of data.
 * @param size Size of @a data, in bytes.
 * @return Number of bytes consumed.  Normally, this value is equal to
 *  @a size.  However, the parser may choose to interrupt parser early or stop
 *  processing data because of an error.
 *
 * You should @e always check the parser's @c error field after a call to this
 * method.  In particular, all data may be consumed before an error is
 * reported, so a return value equal to @a size is not a reliable indicator of
 * success.
 */
size_t netstring_consume ( const struct netstring_limits * limits,
    struct netstring_parser * parser, const char * data, size_t size );

#ifdef __cplusplus
}
#endif

#endif /* _netstring_h__ */
