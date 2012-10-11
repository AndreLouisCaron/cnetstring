# Copyright (c) 2011-2012, Andre Caron (andre.l.caron@gmail.com)
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.

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
