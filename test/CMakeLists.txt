# sha1 library demo projects.

macro(add_test_program name)
  add_executable(${name} ${name}.cpp)
  target_link_libraries(${name} netstring)
  add_dependencies(${name} netstring)
endmacro()

add_test_program(netstring-decode)
add_test_program(netstring-encode)

set(decode ${PROJECT_BINARY_DIR}/netstring-decode)
set(encode ${PROJECT_BINARY_DIR}/netstring-encode)
set(test-data ${CMAKE_CURRENT_SOURCE_DIR}/data)

add_test(decode-test-001
  "${decode}" "${test-data}/netstring-001.txt")
set_tests_properties(decode-test-001
  PROPERTIES PASS_REGULAR_EXPRESSION "foo")

add_test(decode-test-002
  "${decode}" "${test-data}/netstring-002.txt")
set_tests_properties(decode-test-002
  PROPERTIES PASS_REGULAR_EXPRESSION "Hello, world!")
