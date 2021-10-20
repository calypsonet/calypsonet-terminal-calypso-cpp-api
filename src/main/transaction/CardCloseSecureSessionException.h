/**************************************************************************************************
 * Copyright (c) 2021 Calypso Networks Association https://calypsonet.org/                        *
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
 * Indicates that the card has refused the secure session closing.
 *
 * <p>This is usually due to an incorrect SAM signature, or that the secure session has been altered
 * by other APDU commands that would have interfered with it.
 *
 * <p>In this case, the card has rollback the data set by cancelling all updates except for PIN
 * verification attempts.
 *
 * @since 1.0.0
 */
class CardCloseSecureSessionException final : public CardTransactionException {
public:
    /**
     * @param message Message to identify the exception context.
     * @param cause The cause.
     * @since 1.0.0
     */
    CardCloseSecureSessionException(const std::string& message, const std::exception& cause)
    : CardTransactionException(message, cause) {}
};

}
}
}
}
