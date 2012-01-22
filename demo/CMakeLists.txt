set(headers
  netstring.hpp
)
set(sources
  netstring.cpp
  demo.cpp
)
add_executable(
  demo
  ${sources}
  ${headers}
)
target_link_libraries(demo netstring)
add_dependencies(demo netstring)
