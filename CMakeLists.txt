cmake_minimum_required( VERSION 2.8 )
project( ucc CXX)

include(ExternalProject)

find_package(Git REQUIRED)
ExternalProject_Add(
  catch
  PREFIX ${CMAKE_BINARY_DIR}/catch
  GIT_REPOSITORY https://github.com/philsquared/Catch.git
  TIMEOUT 10
  UPDATE_COMMAND ${GIT_EXECUTABLE} pull
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
  LOG_DOWNLOAD ON
  )

# Expose required variable (CATCH_INCLUDE_DIR) to parent scope
ExternalProject_Get_Property(catch source_dir)

set(CATCH_INCLUDE_DIR ${source_dir}/include CACHE INTERNAL
  "Path to include folder for Catch")
if ( ${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU"
    OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang" )
  set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -std=c++14" )
  if ( ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang" )
    set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weverything -Wno-c++98-compat" )
  endif ()
  set( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -g" )
  set( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -O2" )
elseif ( ${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC" )
  if ( CMAKE_CXX_FLAGS MATCHES "/W[0-4]" )
    string( REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}" )
  else ()
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4" )
  endif ()
endif ()

set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

set( EXTRA_DIRS ${EXTRA_DIRS}
  src
  "${CATCH_INCLUDE_DIR}"
  "${PROJECT_SOURCE_DIR}/thirdparty"
  )
include_directories( ${EXTRA_DIRS} )

set( EXTRA_LIBS ${EXTRA_LIBS}
  )

set( LIB_NAME ${PROJECT_NAME} )
set( LIBRARY_TYPE STATIC )
set( SOURCE ${SOURCE}
  "${PROJECT_SOURCE_DIR}/src/token.cpp"
  "${PROJECT_SOURCE_DIR}/src/lexer.cpp"
  "${PROJECT_SOURCE_DIR}/src/util.cpp"
  )
add_library ( ${LIB_NAME}
  ${LIBRARY_TYPE}
  ${SOURCE}
  )
target_link_libraries( ${LIB_NAME} ${EXTRA_LIBS} )

add_executable( "${PROJECT_NAME}code" src/main.cpp )
target_link_libraries( "${PROJECT_NAME}code" ${LIB_NAME} )

add_executable( "${PROJECT_NAME}test" src/test.cpp )
target_link_libraries( "${PROJECT_NAME}test" ${LIB_NAME} )

enable_testing( true )
add_test( NAME RunTests COMMAND "${PROJECT_NAME}test" )

find_package( Doxygen )
if ( DOXYGEN_FOUND )
  configure_file( ${PROJECT_SOURCE_DIR}/Doxyfile ${PROJECT_BINARY_DIR}/Doxyfile
    @ONLY )
  add_custom_target( doc
    ${DOXYGEN_EXECUTABLE} ${PROJECT_BINARY_DIR}/Doxyfile
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/..
    COMMENT "Generating API documentation with Doxygen" VERBATIM
    )
endif ( DOXYGEN_FOUND )
