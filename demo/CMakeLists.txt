set(headers
  netstring.hpp
)
set(sources
  netstring.cpp
  demo.cpp
)
add_executable(
  cnetstring-demo
  ${sources}
  ${headers}
)
target_link_libraries(cnetstring-demo netstring)
add_dependencies(cnetstring-demo netstring)
