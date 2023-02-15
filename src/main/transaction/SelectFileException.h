/**************************************************************************************************
 * Copyright (c) 2023 Calypso Networks Association https://calypsonet.org/                        *
 *                                                                                                *
 * See the NOTICE file(s) distributed with this work for additional information regarding         *
 * copyright ownership.                                                                           *
 *                                                                                                *
 * This program and the accompanying materials are made available under the terms of the Eclipse  *
 * Public License 2.0 which is available at http://www.eclipse.org/legal/epl-2.0                  *
 *                                                                                                *
 * SPDX-License-Identifier: EPL-2.0                                                               *
 **************************************************************************************************/

#pragma once

/* Keyple Core Util */
#include "RuntimeException.h"

namespace calypsonet {
namespace terminal {
namespace calypso {
namespace transaction {

using namespace keyple::core::util::cpp::exception;

/**
 * Indicates that the file selection failed because it was not found. This can happen in the
 * following cases:
 *
 * <ul>
 *   <li>The "Select File" card command status is 6A82h;
 * </ul>
 *
 * @since 1.4.0
 */
class SelectFileException : public RuntimeException {
public:
    /**
     * Encapsulates a lower level exception.
     *
     * @param message Message to identify the exception context.
     * @param cause The cause.
     * @since 1.4.0
     */
    SelectFileException(const std::string& message, const std::shared_ptr<Exception> cause)
    : RuntimeException(message, cause) {}

};

}
}
}
}
