# *************************************************************************************************
# Copyright (c) 2021 Calypso Networks Association                                                 *
# https://www.calypsonet-asso.org/                                                                *
#                                                                                                 *
# See the NOTICE file(s) distributed with this work for additional information regarding          *
# copyright ownership.                                                                            *
#                                                                                                 *
# This program and the accompanying materials are made available under the terms of the Eclipse   *
# Public License 2.0 which is available at http://www.eclipse.org/legal/epl-2.0                   *
#                                                                                                 *
# SPDX-License-Identifier: EPL-2.0                                                                *
# *************************************************************************************************/

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_LEGACY_CYGWIN_WIN32 0)
SET(CMAKE_CXX_STANDARD 11)

# Compilers
SET(CMAKE_C_COMPILER_WORKS 1)
SET(CMAKE_CXX_COMPILER_WORKS 1)

project(Project)

IF(NOT TOOLCHAIN_FILE)
    MESSAGE(FATAL_ERROR "Toolchain file not specified")
ENDIF()

# Set common output directory
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
SET(GOOGLETEST_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add Google Test
INCLUDE(CMakeLists.txt.googletest)

# Add projects
ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/src)
