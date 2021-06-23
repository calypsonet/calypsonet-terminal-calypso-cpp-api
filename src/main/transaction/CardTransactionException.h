/**************************************************************************************************
 * Copyright (c) 2021 Calypso Networks Association                                                *
 * https://www.calypsonet-asso.org/                                                               *
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

#include <exception>
#include <string>

/* Keyple Core Util */
#include "RuntimeException.h"

namespace calypsonet {
namespace terminal {
namespace calypso {
namespace transaction {

using namespace keyple::core::util::cpp::exception;

/**
 * Parent abstract class of all Calypso card transaction functional exceptions.
 *
 * @since 1.0
 */
class CardTransactionException : public RuntimeException {
protected:
    /**
     * @param message The message to identify the exception context
     * @since 1.0
     */
    CardTransactionException(const std::string& message) : RuntimeException(message) {}

    /**
     * Encapsulates a lower level card transaction exception
     *
     * @param message Message to identify the exception context.
     * @param cause The cause.
     * @since 1.0
     */
    CardTransactionException(const std::string& message, const std::exception& cause)
    : RuntimeException(message, cause) {}
};

}
}
}
}
