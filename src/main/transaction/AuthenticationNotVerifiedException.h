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

#include <string>

/* Calypsonet Terminal Calypso */
#include "CardTransactionException.h"

namespace calypsonet {
namespace terminal {
namespace calypso {
namespace transaction {

/**
 * Indicates that the card has correctly closed the secure session, but that it is impossible to
 * check the authenticity of the support because the SAM is no more available (timeout, network
 * problem,...).
 *
 * @since 1.0
 */
class AuthenticationNotVerifiedException final : public CardTransactionException {
public:
    /**
     * @param message The message to identify the exception context
     * @since 1.0
     */
    AuthenticationNotVerifiedException(const std::string& message)
    : CardTransactionException(message) {}

    /**
     * Encapsulates lower level exception.
     *
     * @param message Message to identify the exception context.
     * @param cause The cause.
     * @since 1.0
     */
    AuthenticationNotVerifiedException(const std::string& message, const std::exception& cause)
    : CardTransactionException(message, cause) {}
};

}
}
}
}
