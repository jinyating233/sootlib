# Install script for directory: /home/jinyating/work/sootlib/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/jinyating/work/sootlib/library")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/jinyating/work/sootlib/bulid/src/nucleationModels/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/jinyating/work/sootlib/bulid/src/growthModels/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/jinyating/work/sootlib/bulid/src/oxidationModels/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/jinyating/work/sootlib/bulid/src/coagulationModels/cmake_install.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsootlib.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsootlib.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsootlib.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/jinyating/work/sootlib/bulid/src/libsootlib.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsootlib.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsootlib.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsootlib.so")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "/home/jinyating/work/sootlib/src/sootHeaders.h"
    "/home/jinyating/work/sootlib/src/state.h"
    "/home/jinyating/work/sootlib/src/sootDefs.h"
    "/home/jinyating/work/sootlib/src/sootModel.h"
    "/home/jinyating/work/sootlib/src/sootModel_MONO.h"
    "/home/jinyating/work/sootlib/src/sootModel_MOMIC.h"
    "/home/jinyating/work/sootlib/src/sootModel_LOGN.h"
    "/home/jinyating/work/sootlib/src/sootModel_QMOM.h"
    "/home/jinyating/work/sootlib/src/sootModel_SECT.h"
    )
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/coagulationModels" TYPE FILE FILES
    "/home/jinyating/work/sootlib/src/coagulationModels/coagulationModel.h"
    "/home/jinyating/work/sootlib/src/coagulationModels/coagulationModel_FM.h"
    "/home/jinyating/work/sootlib/src/coagulationModels/coagulationModel_CONTINUUM.h"
    "/home/jinyating/work/sootlib/src/coagulationModels/coagulationModel_HM.h"
    "/home/jinyating/work/sootlib/src/coagulationModels/coagulationModel_FUCHS.h"
    "/home/jinyating/work/sootlib/src/coagulationModels/coagulationModel_NONE.h"
    )
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/growthModels" TYPE FILE FILES
    "/home/jinyating/work/sootlib/src/growthModels/growthModel.h"
    "/home/jinyating/work/sootlib/src/growthModels/growthModel_LL.h"
    "/home/jinyating/work/sootlib/src/growthModels/growthModel_LIN.h"
    "/home/jinyating/work/sootlib/src/growthModels/growthModel_HACA.h"
    "/home/jinyating/work/sootlib/src/growthModels/growthModel_MB.h"
    "/home/jinyating/work/sootlib/src/growthModels/growthModel_NONE.h"
    )
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nucleationModels" TYPE FILE FILES
    "/home/jinyating/work/sootlib/src/nucleationModels/nucleationModel.h"
    "/home/jinyating/work/sootlib/src/nucleationModels/nucleationModel_LL.h"
    "/home/jinyating/work/sootlib/src/nucleationModels/nucleationModel_LIN.h"
    "/home/jinyating/work/sootlib/src/nucleationModels/nucleationModel_LINA1.h"
    "/home/jinyating/work/sootlib/src/nucleationModels/nucleationModel_PAH.h"
    "/home/jinyating/work/sootlib/src/nucleationModels/nucleationModel_MB.h"
    "/home/jinyating/work/sootlib/src/nucleationModels/nucleationModel_NONE.h"
    )
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/oxidationModels" TYPE FILE FILES
    "/home/jinyating/work/sootlib/src/oxidationModels/oxidationModel.h"
    "/home/jinyating/work/sootlib/src/oxidationModels/oxidationModel_LL.h"
    "/home/jinyating/work/sootlib/src/oxidationModels/oxidationModel_LEE_NEOH.h"
    "/home/jinyating/work/sootlib/src/oxidationModels/oxidationModel_NSC_NEOH.h"
    "/home/jinyating/work/sootlib/src/oxidationModels/oxidationModel_HACA.h"
    "/home/jinyating/work/sootlib/src/oxidationModels/oxidationModel_OPTJ.h"
    "/home/jinyating/work/sootlib/src/oxidationModels/oxidationModel_OPTG.h"
    "/home/jinyating/work/sootlib/src/oxidationModels/oxidationModel_MB.h"
    "/home/jinyating/work/sootlib/src/oxidationModels/oxidationModel_NONE.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/sootlib/sootlib_exp.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/sootlib/sootlib_exp.cmake"
         "/home/jinyating/work/sootlib/bulid/src/CMakeFiles/Export/e218ed8b3c3fa7a9bc8172501a4a0e2f/sootlib_exp.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/sootlib/sootlib_exp-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/sootlib/sootlib_exp.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/sootlib" TYPE FILE FILES "/home/jinyating/work/sootlib/bulid/src/CMakeFiles/Export/e218ed8b3c3fa7a9bc8172501a4a0e2f/sootlib_exp.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/sootlib" TYPE FILE FILES "/home/jinyating/work/sootlib/bulid/src/CMakeFiles/Export/e218ed8b3c3fa7a9bc8172501a4a0e2f/sootlib_exp-release.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/sootlib" TYPE FILE FILES "/home/jinyating/work/sootlib/src/sootlibConfig.cmake")
endif()

