/**************************************************************************************************
 * Copyright (c) 2022 Calypso Networks Association https://calypsonet.org/                        *
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
 * Indicates that a signature is incorrect. This can happen in the following cases:
 *
 * <ul>
 *   <li>The "PSO Verify Signature" SAM command status is 6988h;
 * </ul>
 *
 * @since 1.2.0
 */
class InvalidSignatureException : public RuntimeException {
public:
    /**
     * @param message The message to identify the exception context.
     * @since 1.2.0
     */
    InvalidSignatureException(const std::string& message) : RuntimeException(message) {}

    /**
     * Encapsulates a lower level exception.
     *
     * @param message Message to identify the exception context.
     * @param cause The cause.
     * @since 1.2.0
     */
    InvalidSignatureException(const std::string& message, const std::shared_ptr<Exception> cause)
    : RuntimeException(message, cause) {}
};

}
}
}
}
