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

SET(EXECTUABLE_NAME keypleterminalcalypso_ut)

SET(KEYPLE_UTIL_DIR        "../../../keyple-util-cpp-lib")
SET(KEYPLE_UTIL_LIB        "keypleutilcpplib")

INCLUDE_DIRECTORIES(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../main
    ${CMAKE_CURRENT_SOURCE_DIR}/../main/spi

    ${KEYPLE_UTIL_DIR}/src/main
    ${KEYPLE_UTIL_DIR}/src/main/cpp
)

ADD_EXECUTABLE(
    ${EXECTUABLE_NAME}

    ${CMAKE_CURRENT_SOURCE_DIR}/MainTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/CalypsoApiPropertiesTest.cpp
)

# Add Google Test
SET(GOOGLETEST_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
INCLUDE(CMakeLists.txt.googletest)

TARGET_LINK_LIBRARIES(${EXECTUABLE_NAME} gtest gmock ${KEYPLE_UTIL_LIB})
