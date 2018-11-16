cmake_minimum_required(VERSION 3.8.2 FATAL_ERROR)

option(NSW_BUILD_SHARED   "If enabled, the library will be build as a shared library." OFF)
option(NSW_BUILD_DOC      "If enabled, and Doxygen is installed, the documentation will be built." ON)
option(NSW_BUILD_EXAMPLES "If enabled, the examples that come with the library will be build." ON)
option(NSW_RESTORE_ERRNO  "If enabled, functions from this library will never affect errno/WSAGetLastError()." OFF)
option(NSW_USE_CPP        "If enabled, the C++ tests will be compiled as well." ON)

set(NSW_LANGUAGES "C")

if(NSW_USE_CPP)
	list(APPEND NSW_LANGUAGES "CXX")
endif()

project(NostraSocketWrapper
	VERSION 1.0.0.0
	DESCRIPTION "A C wrapper for POSIX and Windows sockets."
	LANGUAGES ${NSW_LANGUAGES})
	
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
		"$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>"
		"$<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/include>"
		"$<INSTALL_INTERFACE:include>")

if(MSVC)
	target_compile_options(NostraSocketWrapper
		PRIVATE
			"/wd4251")

    target_link_libraries(NostraSocketWrapper 
        PRIVATE 
            Ws2_32)
else()
	target_compile_options(NostraSocketWrapper
		PRIVATE
			"-Wall"
			"-Wextra"
			"-Wpedantic")
endif()

if(NSW_RESTORE_ERRNO)
	target_compile_definitions(NostraSocketWrapper
		PRIVATE
			"NSW_RESTORE_ERRNO")
endif()

include(GenerateExportHeader)

generate_export_header(NostraSocketWrapper 
	BASE_NAME "nsw" 
	EXPORT_FILE_NAME "${CMAKE_BINARY_DIR}/include/nostrasocketwrapper/export.h"
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
install(DIRECTORY "${CMAKE_BINARY_DIR}/include/" 
	DESTINATION 
		"include"
	COMPONENT
		"Develop")

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

		install(DIRECTORY "${CMAKE_BINARY_DIR}/doc/html/"
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

# Function for simpler addition of C++ tests
function(nsw_add_cpp_test TEST_NAME)
	add_executable("nsw.cpp.${TEST_NAME}" "test/${TEST_NAME}.d/src/${TEST_NAME}.cpp")
	
	target_compile_features("nsw.cpp.${TEST_NAME}" 
		PUBLIC
			cxx_std_11)

	target_link_libraries("nsw.cpp.${TEST_NAME}" Nostra::SocketWrapper)

	install(TARGETS "nsw.cpp.${TEST_NAME}" EXPORT NostraSocketWrapperTargets
		RUNTIME 
			DESTINATION "test/nsw.${TEST_NAME}.d"
			COMPONENT "Test")

	add_test(
		NAME 
			"nsw.cpp.${TEST_NAME}"
		COMMAND 
			"nsw.cpp.${TEST_NAME}"
        WORKING_DIRECTORY
            "test/${TEST_NAME}.d")
endfunction()

function(nsw_prefix_list OUT PREFIX)
	set(LIST_INTERNAL "")

	foreach(STR IN LISTS ARGN)
		list(APPEND LIST_INTERNAL "${PREFIX}${STR}")
	endforeach()

	set("${OUT}" "${LIST_INTERNAL}" PARENT_SCOPE)
endfunction()

# Function for simpler addition of C tests
function(nsw_add_c_test TEST_NAME)
	cmake_parse_arguments(NSW_FUNC "NOCOPY" "" "ADDITIONAL_SOURCES" "${ARGN}")

	if(DEFINED NSW_FUNC_UNPARSED_ARGUMENTS)
		message(SEND_ERROR "NostraSocketWrapper: nsw_add_c_test(): unknown argument: ${NSW_FUNC_UNPARSED_ARGUMENTS}")
	endif()

	if(NOT NSW_FUNC_NOCOPY)
		
		# Make sure the working directory for the command exists
		# This is only required if the resources were copied, 
		file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/test/${TEST_NAME}.d")

		# If the resources folder exists, copy it
		if(EXISTS "${CMAKE_SOURCE_DIR}/test/${TEST_NAME}.d/resources")
			file(COPY "test/${TEST_NAME}.d/resources" DESTINATION "${CMAKE_BINARY_DIR}/test/${TEST_NAME}.d")
		endif()

		# Set working dir to test/${TEST_NAME}.d in the binary dir because resources have been copied
		set(NSW_WORKING_DIR "${CMAKE_BINARY_DIR}/test/${TEST_NAME}.d")
	else()
		# Set working dir to test/${TEST_NAME}.d in the source dir because resources have not been copied
		set(NSW_WORKING_DIR "${CMAKE_SOURCE_DIR}/test/${TEST_NAME}.d")
	endif()

	# Properly prefix the additional source files to locate them in test/<test name>.d/src/
	nsw_prefix_list(NSW_FUNC_ACTUAL_ADD_SOURCES "test/${TEST_NAME}.d/src/" "${NSW_FUNC_ADDITIONAL_SOURCES}")

	add_executable("nsw.c.${TEST_NAME}" "test/${TEST_NAME}.d/src/${TEST_NAME}.c" "${NSW_FUNC_ACTUAL_ADD_SOURCES}")
	
	target_link_libraries("nsw.c.${TEST_NAME}" Nostra::SocketWrapper)

	install(TARGETS "nsw.c.${TEST_NAME}" EXPORT NostraSocketWrapperTargets
		RUNTIME 
			DESTINATION "test/nsw.${TEST_NAME}.d"
			COMPONENT "Test")

	# Install ressources folder from the SOURCES directory (if it exists)
	if(EXISTS "${CMAKE_SOURCE_DIR}/test/${TEST_NAME}.d/resources")
		install(DIRECTORY "${CMAKE_SOURCE_DIR}/test/${TEST_NAME}.d/resources" 
			DESTINATION
				"test/nsw.${TEST_NAME}.d"
			COMPONENT 
				"Test")
	endif()

	add_test(
		NAME 
			"nsw.c.${TEST_NAME}"
		COMMAND 
			"nsw.c.${TEST_NAME}"
        WORKING_DIRECTORY
			"${NSW_WORKING_DIR}")
endfunction()

# Function to convert from a C test to a C++ test
function(nsw_c_test_to_cpp TEST_NAME)
#[[
	configure_file("test/${TEST_NAME}.d/src/${TEST_NAME}.c" "${CMAKE_BINARY_DIR}/test/${TEST_NAME}.d/src/${TEST_NAME}.cpp" COPYONLY)

	add_executable("nsw.cpp.${TEST_NAME}" "${CMAKE_BINARY_DIR}/test/${TEST_NAME}.d/src/${TEST_NAME}.cpp")
	
	target_link_libraries("nsw.cpp.${TEST_NAME}" Nostra::SocketWrapper)

	install(TARGETS "nsw.cpp.${TEST_NAME}" EXPORT NostraSocketWrapperTargets
		RUNTIME 
			DESTINATION "test/nsw.${TEST_NAME}.d"
			COMPONENT "Test")

	add_test(
		NAME 
			"nsw.cpp.${TEST_NAME}"
		COMMAND 
			"nsw.cpp.${TEST_NAME}"
        WORKING_DIRECTORY
			"test/${TEST_NAME}.d")
			]]
endfunction()

enable_testing()

# Tests start
if(BUILD_TESTING)
	nsw_add_c_test(socket.wt)
	nsw_add_c_test(error.wt)

	if(NSW_USE_CPP)
		nsw_c_test_to_cpp(error.wt)
	endif()
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

write_basic_package_version_file("${CMAKE_BINARY_DIR}/NostraSocketWrapperConfigVersion.cmake"
	VERSION "${PROJECT_VERSION}"
	COMPATIBILITY AnyNewerVersion)

export(EXPORT NostraSocketWrapperTargets
	FILE "${CMAKE_BINARY_DIR}/NostraSocketWrapperTargets.cmake"
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
    "${CMAKE_BINARY_DIR}/NostraSocketWrapperConfig.cmake"
  DESTINATION
    ${CONFIG_PACKAGE_LOCATION}
  COMPONENT
    "Develop")

configure_file("cmake/CPackConfig.cmake.in" "cmake/CPackConfig.cmake" @ONLY)

include("${CMAKE_BINARY_DIR}/cmake/CPackConfig.cmake")

include(CPack)