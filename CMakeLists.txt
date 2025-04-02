cmake_minimum_required(VERSION 3.31.6)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
set(CMAKE_CXX_EXTENSIONS OFF)

project(UmbraLogging VERSION 1.0.0)

add_library(UmbraLogging STATIC
  src/log.cpp
  src/logger.cpp
)

include(GNUInstallDirs)

target_include_directories(UmbraLogging PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

add_compile_definitions(UMBRA_BUILD_DLL)

target_compile_features(UmbraLogging PRIVATE cxx_std_20)

target_precompile_headers(UmbraLogging PRIVATE include/pch.h)

# Allow installation
install(TARGETS UmbraLogging
  EXPORT UmbraLoggingTargets
  ARCHIVE DESTINATION lib
)

install(DIRECTORY include/ DESTINATION include)
install(EXPORT UmbraLoggingTargets
  FILE UmbraLoggingTargets.cmake
  NAMESPACE Umbra::
  DESTINATION lib/cmake/UmbraLogging
)
install(FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/include/core.h
  DESTINATION include/UmbraLogging

)

# Setup system link to compile_commands directory for LSP config In NeoVim.
# This needs additional setup in the LspConfig file in the NeoVim config directory
# If you are not using NeoVim, you can remove this.
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ln -sf ${CMAKE_BINARY_DIR}/compile_commands.json ~/.config/clangd/compile_commands/compile_commands.json
)
