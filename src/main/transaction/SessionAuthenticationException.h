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

/* Calypsonet Terminal Calypso */
#include "CardTransactionException.h"

namespace calypsonet {
namespace terminal {
namespace calypso {
namespace transaction {

/**
 * Indicates that the card has correctly closed the secure session, but the support is not authentic
 * because the signature of the card is incorrect.
 *
 * @since 1.0
 */
class SessionAuthenticationException final : public CardTransactionException {
public:
    /**
     * @param message The message to identify the exception context
     * @since 1.0
     */
    SessionAuthenticationException(const std::string& message)
    : CardTransactionException(message) {}

    /**
     * Encapsulates lower level exception.
     *
     * @param message Message to identify the exception context.
     * @param cause The cause.
     * @since 1.0
     */
    SessionAuthenticationException(const std::string& message, const std::exception& cause)
    : CardTransactionException(message, cause) {}
};

}
}
}
}
