cmake_minimum_required(VERSION 3.8.2 FATAL_ERROR)

option(NSW_BUILD_SHARED   "If enabled, the library will be build as a shared library." OFF)
option(NSW_BUILD_DOC      "If enabled, and Doxygen is installed, the documentation will be built." ON)
option(NSW_BUILD_EXAMPLES "If enabled, the examples that come with the library will be build." ON)

project(NostraSocketWrapper
	VERSION 1.0.0.0
	DESCRIPTION "A C wrapper for POSIX and Windows sockets."
	LANGUAGES C CXX)
	
include(CTest)

#configure_file("cmake/config.hpp.in" "include/NostraSocketWrapper/config.hpp" @ONLY)

list(APPEND NSW_SRC_FILES "src/error.c" "src/socket.c")

if(NSW_BUILD_SHARED)
	add_library(NostraSocketWrapper SHARED ${NSW_SRC_FILES})
else()
	add_library(NostraSocketWrapper STATIC ${NSW_SRC_FILES})
endif()

add_library(Nostra::SocketWrapper ALIAS NostraSocketWrapper)

target_include_directories(NostraSocketWrapper
	PUBLIC
		"$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
		"$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>"
		"$<INSTALL_INTERFACE:include>")

if(MSVC)
	target_compile_options(NostraSocketWrapper
		PRIVATE
			"/wd4251")
else()
	target_compile_options(NostraSocketWrapper
		PRIVATE
			"-Wall"
			"-Wextra"
			"-Wpedantic")
endif()

include(GenerateExportHeader)

generate_export_header(NostraSocketWrapper 
	BASE_NAME "nsw" 
	EXPORT_FILE_NAME "${CMAKE_CURRENT_BINARY_DIR}/include/nostrasocketwrapper/export.h"
	DEFINE_NO_DEPRECATED)

install(TARGETS NostraSocketWrapper EXPORT NostraSocketWrapperTargets
	RUNTIME 
		DESTINATION "bin"
		COMPONENT "Required"
	LIBRARY 
		DESTINATION "lib"
		COMPONENT "Required"
	ARCHIVE	
		DESTINATION "lib/static"
		COMPONENT "Develop"
	INCLUDES 
		DESTINATION "include")

install(DIRECTORY "include" 
	DESTINATION 
		"."
	COMPONENT
		"Develop")
		
# Install the additionally configured file(s)
install(DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/include/" 
	DESTINATION 
		"include"
	COMPONENT
		"Develop")

#[==[
if(NSW_BUILD_DOC)
	
	message(STATUS "NostraSocketWrapper: Attempting to generate Doxygen documentation.")

	find_package(Doxygen OPTIONAL_COMPONENTS dot)

	if(DOXYGEN_FOUND)
		
		message(STATUS "NostraSocketWrapper: Doxygen executable was found, documentation will be generated.")

		configure_file("doc/Doxyfile.in" "doc/Doxyfile")

		add_custom_target(NostraSocketWrapperDoc
			ALL COMMAND Doxygen::doxygen "doc/Doxyfile"
			WORKING_DIRECTORY "."
			COMMENT "Generating Doxygen documentation."
			VERBATIM)

		install(DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/doc/html/"
			DESTINATION
				"doc"
			COMPONENT
				"Documentation")

	else()

		message(WARNING "NostraSocketWrapper: Doxygen executable could not be found, documentation generation will be omitted.")

	endif()

else()

	message(STATUS "NostraSocketWrapper: Generation of documentation is disabled.")

endif()
#]==]


# Function for simpler addition of tests
function(nsw_add_test TEST_NAME)
	add_executable("nsw.${TEST_NAME}" "test/${TEST_NAME}.c")
	
	target_link_libraries("nsw.${TEST_NAME}" Nostra::SocketWrapper)

	install(TARGETS "nsw.${TEST_NAME}" EXPORT NostraSocketWrapperTargets
		RUNTIME 
			DESTINATION "test"
			COMPONENT "Test")

	add_test(
		NAME 
			"nsw.${TEST_NAME}"
		COMMAND 
			"nsw.${TEST_NAME}")
endfunction()

enable_testing()

# Tests start
if(BUILD_TESTING)

endif()
# Tests end



# Function for simpler addition of examples
function(nsw_add_example EXAMPLE_NAME)
	add_executable("${EXAMPLE_NAME}" "examples/${EXAMPLE_NAME}.c")

	target_link_libraries("${EXAMPLE_NAME}" Nostra::SocketWrapper)

	install(TARGETS "${EXAMPLE_NAME}" EXPORT NostraSocketWrapperTargets
		RUNTIME 
			DESTINATION "examples"
			COMPONENT "Examples")
endfunction()

# Examples start
if(NSW_BUILD_EXAMPLES)

endif()
# Examples end



install(FILES "cmake/INSTALL_README.md" 
	DESTINATION	
		"." 
	COMPONENT 
		"Required"
	RENAME
		"README.md")

install(FILES "cmake/INSTALL_LICENSE.txt"
	DESTINATION	
		"." 
	COMPONENT 
		"Required"
	RENAME 
		"LICENSE")

install(FILES "CHANGELOG.md"
	DESTINATION	
		"." 
	COMPONENT 
		"Required")


include(CMakePackageConfigHelpers)

write_basic_package_version_file("${CMAKE_CURRENT_BINARY_DIR}/NostraSocketWrapperConfigVersion.cmake"
	VERSION "${PROJECT_VERSION}"
	COMPATIBILITY AnyNewerVersion)

export(EXPORT NostraSocketWrapperTargets
	FILE "${CMAKE_CURRENT_BINARY_DIR}/NostraSocketWrapperTargets.cmake"
	NAMESPACE Nostra::)

configure_file("cmake/NostraSocketWrapperConfig.cmake.in" "NostraSocketWrapperConfig.cmake" @ONLY)

set(CONFIG_PACKAGE_LOCATION "lib/cmake/NostraSocketWrapper")

install(EXPORT NostraSocketWrapperTargets
	FILE
		"NostraSocketWrapperTargets.cmake"
	NAMESPACE
		Nostra::
	DESTINATION
		${CONFIG_PACKAGE_LOCATION}
	COMPONENT
		"Required")

install(
  FILES
    "${CMAKE_CURRENT_BINARY_DIR}/NostraSocketWrapperConfig.cmake"
  DESTINATION
    ${CONFIG_PACKAGE_LOCATION}
  COMPONENT
    "Develop")

configure_file("cmake/CPackConfig.cmake.in" "cmake/CPackConfig.cmake" @ONLY)

include("${CMAKE_BINARY_DIR}/cmake/CPackConfig.cmake")

include(CPack)