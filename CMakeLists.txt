cmake_minimum_required(VERSION 3.10)

project(HelloWorld)

# First we want to build the lxsdk so we have the library we depend on to make 
# plug-ins for Modo.

# Create a variable to allow developers to set the path to the downloaded sdk.
set(LXSDK_PATH "" CACHE PATH "Path to root of downloaded LXSDK")

# Get all source and headers for lxsdk
# TODO: Read somewhere it's recommended not to use GLOB like this,
file(GLOB LXSDK_SOURCES ${LXSDK_PATH}/common/*.cpp)
file(GLOB LXSDK_HEADERS ${LXSDK_PATH}/include/*.h?)

# CRT_SECURE_NO_WARNINGS on windows,
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

# Should create our library so we can now focus on our own project.
add_library(lxsdk STATIC ${LXSDK_SOURCES})
set_target_properties(lxsdk PROPERTIES LIBRARY_OUTPUT_DIRECTORY lib)
target_include_directories(lxsdk PRIVATE ${LXSDK_PATH}/include)

# This is the plug-in we create, shared makes it on windows to a .dll which is
# what we expect for a plug-in
add_library(hello SHARED "src/hello.cpp")
# We also must include the headers for the sdk
target_include_directories(hello PRIVATE ${LXSDK_PATH}/include)
# And link to the library
target_link_libraries(hello lxsdk)

# Set the output for the plug-in to match the system name, 
# index.cfg will then load the correct plug-in depending on
# system.
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  # Branch on check for 32 vs 64-bit
  if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(PLUGIN_DIR "win64")
  elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
    set(PLUGIN_DIR "win32")
  endif()

elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
  set(PLUGIN_DIR "mac")

elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  set(PLUGIN_DIR "unix")

endif()

# Set the output to the folder Modo will search, 
# $<0:> is just to remove any config subfolders like DEBUG and RELEASE
set_target_properties(hello 
  PROPERTIES 
    LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/${PLUGIN_DIR}/$<0:>
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/${PLUGIN_DIR}/$<0:> # windows apparently needs this set as well
)
