# *************************************************************************************************
# Copyright (c) 2021 Calypso Networks Association http://calypsonet.org/                          *
#                                                                                                 *
# See the NOTICE file(s) distributed with this work for additional information regarding          *
# copyright ownership.                                                                            *
#                                                                                                 *
# This program and the accompanying materials are made available under the terms of the Eclipse   *
# Public License 2.0 which is available at http://www.eclipse.org/legal/epl-2.0                   *
#                                                                                                 *
# SPDX-License-Identifier: EPL-2.0                                                                *
# *************************************************************************************************/

SET(LIBRARY_NAME calypsonetterminalcalypsocppapi)

# declare this library as header only
ADD_LIBRARY(
    ${LIBRARY_NAME}
    INTERFACE
)

TARGET_INCLUDE_DIRECTORIES(
    ${LIBRARY_NAME}
    INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/card
    ${CMAKE_CURRENT_SOURCE_DIR}/sam
    ${CMAKE_CURRENT_SOURCE_DIR}/spi
    ${CMAKE_CURRENT_SOURCE_DIR}/transaction
)

ADD_LIBRARY(CalypsoNet::TerminalCalypso ALIAS ${LIBRARY_NAME})
