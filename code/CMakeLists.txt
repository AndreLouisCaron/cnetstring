# netstring library.

set(netstring_headers
  netstring.h
)
set(netstring_sources
  netstring.c
)
add_library(netstring
  STATIC
  ${netstring_sources}
  ${netstring_headers}
)
