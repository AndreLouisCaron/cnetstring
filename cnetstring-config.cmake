# Library configuration file used by dependent projects
# via find_package() built-in directive in "config" mode.

if(NOT DEFINED cnetstring_FOUND)

  # Locate library headers.
  find_path(cnetstring_include_dirs
    NAMES netstring.h
    PATHS ${cnetstring_DIR}/code
  )

  # Export library targets.
  set(cnetstring_libraries
    netstring
    CACHE INTERNAL "cnetstring library" FORCE
  )

  # Usual "required" et. al. directive logic.
  include(FindPackageHandleStandardArgs)
  find_package_handle_standard_args(
    cnetstring DEFAULT_MSG
    cnetstring_include_dirs
    cnetstring_libraries
  )

  # Register library targets when found as part of a dependent project.
  # Since this project uses a find_package() directive to include this
  # file, don't recurse back into the CMakeLists file.
  if(NOT ${PROJECT_NAME} STREQUAL cnetstring)
    add_subdirectory(
      ${cnetstring_DIR}
      ${CMAKE_CURRENT_BINARY_DIR}/cnetstring
    )
  endif()
endif()
