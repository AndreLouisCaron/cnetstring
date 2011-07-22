=====================================================
  `cnetstring` --- Streaming netstring parser for C
=====================================================
:authors:
   André Caron
:contact: andre.l.caron@gmail.com

Description
===========

This library provides a parser for `netstrings`_.  The parser is implemented as
a finite state machine (FSM) for use in streaming applications (i.e. data
arrives at an unpredictable rate and the parser must be interruptible).  As
such, the parser itself does not buffer any received data.  It just forwards it
to registered callbacks.  It requires little overhead and is well suited for
being used in an object-oriented wrapper.

Known uses
==========

The parser is used in the `cscgi`_ project to parse the `SCGI`_ request headers.

.. _`netstrings`: http://cr.yp.to/proto/netstrings.txt
.. _`cscgi`: https://github.com/AndreLouisCaron/cscgi
.. _`SCGI`: http://en.wikipedia.org/wiki/Simple_Common_Gateway_Interface
