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


Getting started
===============

The library is currently only distributed in source form.  However, it has no
dependencies on external projects and will compile as-is with almost any C
compiler.

The following presents the *supported* way to get up and running with
``cnetstring``.  Feel free to experiment with your toolchain of choice.

Requirements
------------

Dependencies are:

* Git_
* CMake_
* Doxygen_
* A C++ compiler toolchain:
  * Microsoft Visual Studio
  * ``g++`` and ``make``

.. _Git: http://git-scm.com/
.. _CMake: http://www.cmake.org/
.. _Doxygen: http://www.stack.nl/~dimitri/doxygen/

Standalone build
----------------

#. Get the source code

   ::

      > git clone git://github.com/AndreLouisCaron/cnetstring.git
      > cd cnetstring

   Feel free to check out a specific version

   ::

      > git tag
      v0.1

      > git checkout v0.1

#. Generate the build scripts

   ::

      > mkdir work
      > cd work
      > cmake -G "NMake Makefiles" ..

#. Build the source code

   ::

      > nmake

#. Run the test suite

   ::

      > nmake /A test

#. Build the API documentation

   ::

      > nmake help

   Open the HTML documentation in ``help/html/index.html``.

Embedded build
--------------

#. Register as a Git sub-module

   ::

      > cd myproject
      > git submodule add git://github.com/AndreLouisCaron/cnetstring.git libs/cnetstring

   Feel free to check out a specific version
   Feel free to check out a specific version

   ::

      > cd libs/cnetstring
      > git tag
      v0.1

      > git checkout v0.1
      > cd ../..
      > git add libs/cnetstring

#. Add ``cnetstring`` targets to your CMake project.

   ::

      set(cnetstring_DIR
        ${CMAKE_SOURCE_DIR}/libs/cnetstring
      )

#. Make sure your project can ``#include <netstring.h>``

   ::

      include_directories(
        ${cnetstring_include_dirs}
      )


#. Link against the ``netstring`` library

   ::

      target_link_libraries(my-application ${cnetstring_libraries})
