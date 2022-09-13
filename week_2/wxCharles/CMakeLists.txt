cmake_minimum_required(VERSION 3.10)

project(wxCharles)

# TODO: manually specify list of sources to compile, this works but is discouraged by CMake
aux_source_directory(. SRC_LIST)
aux_source_directory(framework SRC_LIST)

# Tell CMake to use C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

# Set up wxWidgets
set(wxWidgets_CONFIGURATION mswu)
find_package(wxWidgets COMPONENTS core base REQUIRED)
include(${wxWidgets_USE_FILE})

# Include manifest to set executable icon and use modern UI look on Windows
if(WIN32)
  set(SRC_LIST ${SRC_LIST} framework/res/charles.rc)
endif(WIN32)

# Build the executable, which on OSX will be a bundle
add_executable(${PROJECT_NAME} WIN32 MACOSX_BUNDLE ${SRC_LIST})

# Attach Info.plist on OSX bundles so that it is recognized as a GUI application and has proper high-DPI scaling
if(APPLE)
  set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/framework/res/Info.plist)
endif(APPLE)

# Link against wxWidgets
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})

# Set up the compile options
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic-errors)