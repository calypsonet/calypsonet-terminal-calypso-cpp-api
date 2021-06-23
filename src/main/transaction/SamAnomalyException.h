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
 * Indicates an anomaly in the SAM.
 *
 * <p>This can occur if the SAM is not Calypso compliant.
 *
 * @since 1.0
 */
class SamAnomalyException final : public CardTransactionException {
public:
    /**
     * @param message Message to identify the exception context.
     * @param cause The cause.
     * @since 1.0
     */
    SamAnomalyException(const std::string& message, const std::exception& cause)
    : CardTransactionException(message, cause) {}
};

}
}
}
}
