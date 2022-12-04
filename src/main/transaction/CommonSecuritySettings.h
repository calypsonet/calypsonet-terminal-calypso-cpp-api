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

/* Calypsonet Terminal Calypso */
#include "CalypsoSam.h"

/* Calypsonet Terminal Reader */
#include "CardReader.h"

namespace calypsonet {
namespace terminal {
namespace calypso {
namespace transaction {

using namespace calypsonet::terminal::calypso::sam;

/**
 * Common data to manage the security operations of a Calypso transaction.
 *
 * @param <S> The type of the lowest level child object.
 * @since 1.2.0
 */
template <typename S>
class CommonSecuritySetting {
public:
    /**
     * Defines the control SAM and the reader through which it is accessible to be used to handle
     * the relevant cryptographic operations.
     *
     * @param samReader The control SAM reader.
     * @param calypsoSam The control Calypso SAM.
     * @return The current instance.
     * @throw IllegalArgumentException If one of the arguments is null or if the product type of
     *        CalypsoSam is equal to CalypsoSam::ProductType::UNKNOWN.
     * @since 1.2.0
     */
    virtual S& setControlSamResource(const std::shared_ptr<CardReader> samReader, 
                                     const std::shared_ptr<CalypsoSam> calypsoSam) = 0;

    /**
     * Sets the service to be used to dynamically check if a SAM is revoked or not.
     *
     * @param service The user's service to be used.
     * @return The current instance.
     * @throws IllegalArgumentException If the provided service is null.
     * @since 1.2.0
     */
    virtual S& setSamRevocationService(const std::shared_ptr<SamRevocationServiceSpi> service) = 0;
};

}
}
}
}
