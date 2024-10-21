#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "sootlib::sootlib" for configuration "Release"
set_property(TARGET sootlib::sootlib APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(sootlib::sootlib PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libsootlib.so"
  IMPORTED_SONAME_RELEASE "libsootlib.so"
  )

list(APPEND _cmake_import_check_targets sootlib::sootlib )
list(APPEND _cmake_import_check_files_for_sootlib::sootlib "${_IMPORT_PREFIX}/lib/libsootlib.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
