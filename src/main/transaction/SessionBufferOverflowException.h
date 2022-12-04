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

#include <string>

/* Keyple Core Util */
#include "RuntimeException.h"

namespace calypsonet {
namespace terminal {
namespace calypso {
namespace transaction {

using namespace keyple::core::util::cpp::exception;

/**
 * Indicates that the secure session cannot be performed atomically because the session buffer
 * capacity is not sufficient to handle all the prepared write commands.
 *
 * @since 1.2.0
 */
class SessionBufferOverflowException final : public RuntimeException {
public:
    /**
     * @param message The message to identify the exception context.
     * @since 1.2.0
     */
    SessionBufferOverflowException(const std::string& message) : RuntimeException(message) {}
};

}
}
}
}
