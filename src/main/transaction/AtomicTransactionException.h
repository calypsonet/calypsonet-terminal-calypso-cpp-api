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
 * Indicates that the transaction cannot be done in an atomic way because the capacity of the
 * session buffer is not sufficient.
 *
 * @since 1.0
 */
class AtomicTransactionException final : public CardTransactionException {
public:
    /**
     * @param message The message to identify the exception context
     * @since 1.0
     */
    AtomicTransactionException(const std::string& message) : CardTransactionException(message) {}
};

}
}
}
}
