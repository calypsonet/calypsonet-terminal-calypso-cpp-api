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

/* Calypsonet Terminal Reader */
#include "CardSelection.h"

/* Calypsonet Terminal Calypso */
#include "CalypsoSam.h"

namespace calypsonet {
namespace terminal {
namespace calypso {
namespace sam {

using namespace calypsonet::terminal::reader::selection::spi;

/**
 * SAM specific calypsonet::terminal::reader::selection::spi::CardSelection providing means to
 * filter SAM and define optional commands to be executed during the selection phase such as the
 * Unlock command.
 *
 * @since 1.0
 */
class CalypsoSamSelection : public CardSelection {
public:
    /**
     * Sets a filter to target a SAM having the provided specific {@link CalypsoSam.ProductType}.
     *
     * <p>If not specified, any type is accepted.
     *
     * @param productType The SAM product type.
     * @return The object instance.
     * @throw IllegalArgumentException If productType is null.
     * @since 1.0
     */
    virtual CalypsoSamSelection& filterByProductType(const CalypsoSam::ProductType productType) = 0;

    /**
     * Sets a filter targeting a SAM having a serial number matching the provided regular
     * expression.
     *
     * <p>If set, only a SAM with a serial number matching the provided filter will be selected.<br>
     * The filter is regular expression that will be applied to the real serial number.
     *
     * <p>The regular expression is based on an hexadecimal representation of the serial number.
     *
     * <p>Example:
     *
     * <ul>
     *   <li>A filter targeting all SAMs having an 8-byte serial number starting with A0h would be
     *       "^A0.{6}$".
     *   <li>A filter targeting a SAM having the exact serial number 12345678h would be "12345678".
     * </ul>
     *
     * @param serialNumberRegex A regular expression.
     * @return The object instance.
     * @throw IllegalArgumentException If samSerialNumberRegex is null, empty or invalid.
     * @since 1.0
     */
    virtual CalypsoSamSelection& filterBySerialNumber(const std::string& serialNumberRegex) = 0;

    /**
     * Sets the lock value expected by the SAM to be unlocked (8 or 16 bytes).
     *
     * <p>The Unlock command will be executed only after a successful filtering.
     *
     * @param unlockData A hexadecimal representation of the 16 or 32 digit long unlock value.
     * @return The object instance.
     * @throws IllegalArgumentException If unlockData is null, malformed or out of range.
     * @since 1.0
     */
    virtual CalypsoSamSelection& setUnlockData(const std::string& unlockData) = 0;
};

}
}
}
}
