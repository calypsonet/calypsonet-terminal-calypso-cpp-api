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

#include <exception>
#include <string>

/* Calypsonet Terminal Calypso */
#include "CardTransactionException.h"

namespace calypsonet {
namespace terminal {
namespace calypso {
namespace transaction {

/**
 * Indicates an inconsistency in the card data.
 *
 * <p>This can occur, for example, if data read in session is different from data read outside the
 * session.
 *
 * @since 1.0.0
 */
class InconsistencyDataException final : public CardTransactionException {
public:
    /**
     * @param message The message to identify the exception context
     * @since 1.0.0
     */
    InconsistencyDataException(const std::string& message) : CardTransactionException(message) {}
};

}
}
}
}
