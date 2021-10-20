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

#include <cstdint>
#include <vector>

namespace calypsonet {
namespace terminal {
namespace calypso {
namespace card {

/**
 * Record of a Stored Value debit log.
 *
 * @since 1.0.0
 */
class SvDebitLogRecord {
public:
    /**
     * Gets the raw data of the SV debit log record.
     *
     * @return A byte array.
     * @since 1.0.0
     */
    virtual const std::vector<uint8_t>& getRawData() const = 0;

    /**
     * Gets the debit date as an array of bytes
     *
     * @return A 2-byte byte array
     * @since 1.0.0
     */
    virtual const std::vector<uint8_t> getDebitDate() const = 0;

    /**
     * Gets the debit time as an array of bytes
     *
     * @return A 2-byte byte array
     * @since 1.0.0
     */
    virtual const std::vector<uint8_t> getDebitTime() const = 0;

    /**
     * Gets the debit amount value
     *
     * @return An int
     * @since 1.0.0
     */
    virtual int getAmount() const = 0;

    /**
     * Gets the SV balance value
     *
     * @return An int
     * @since 1.0.0
     */
    virtual int getBalance() const = 0;

    /**
     * Gets the KVC of the debit key (as given in the last SV Debit)
     *
     * @return A byte
     * @since 1.0.0
     */
    virtual uint8_t getKvc() const = 0;

    /**
     * Gets the SAM ID as an array of bytes
     *
     * @return A 4-byte byte array
     * @since 1.0.0
     */
    virtual const std::vector<uint8_t> getSamId() const = 0;

    /**
     * Gets the SAM transaction number value as an int
     *
     * @return An int
     * @since 1.0.0
     */
    virtual int getSamTNum() const = 0;

    /**
     * Gets the SV transaction number value as an int
     *
     * @return An int
     * @since 1.0.0
     */
    virtual int getSvTNum() const = 0;
};

}
}
}
}
