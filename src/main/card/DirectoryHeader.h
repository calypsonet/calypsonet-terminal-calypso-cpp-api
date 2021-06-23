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

#include <cstdint>
#include <vector>

/* Calypsonet Terminal Calypso */
#include "WriteAccessLevel.h"

namespace calypsonet {
namespace terminal {
namespace calypso {
namespace card {

using namespace calypsonet::terminal::calypso;

/**
 * Calypso DF metadata.
 *
 * @since 1.0
 */
class DirectoryHeader {
public:
    /**
     * Gets the associated LID.
     *
     * @return The LID.
     * @since 1.0
     */
    virtual uint16_t getLid() const = 0;

    /**
     * Gets the DF status.
     *
     * @return The DF status byte.
     * @since 1.0
     */
    virtual uint8_t getDfStatus() const = 0;

    /**
     * Gets a reference to access conditions.
     *
     * @return A not empty byte array.
     * @since 1.0
     */
    virtual const std::vector<uint8_t> getAccessConditions() const = 0;

    /**
     * Gets a reference to keys indexes.
     *
     * @return A not empty byte array.
     * @since 1.0
     */
    virtual const std::vector<uint8_t> getKeyIndexes() const = 0;

    /**
     * Gets the KIF associated to the provided write access level.
     *
     * @param writeAccessLevel The write access level (should be not null).
     * @return The KIF value.
     * @throws IllegalArgumentException if writeAccessLevel is null.
     * @since 1.0
     */
    virtual uint8_t getKif(const WriteAccessLevel writeAccessLevel) const = 0;

    /**
     * Gets the KVC associated to the provided write access level.
     *
     * @param writeAccessLevel The write access level (should be not null).
     * @return The KVC value.
     * @throws IllegalArgumentException if writeAccessLevel is null.
     * @since 1.0
     */
    virtual uint8_t getKvc(const WriteAccessLevel writeAccessLevel) const = 0;
};

}
}
}
}
