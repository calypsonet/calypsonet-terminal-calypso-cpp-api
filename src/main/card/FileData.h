/**************************************************************************************************
 * Copyright (c) 2023 Calypso Networks Association https://calypsonet.org/                        *
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
#include <map>
#include <vector>

namespace calypsonet {
namespace terminal {
namespace calypso {
namespace card {

/**
 * Calypso EF content.
 *
 * @since 1.0.0
 */
class FileData {
public:
    /**
     * Gets a reference to the known content of record #1.<br>
     * For a Binary file, it means all the bytes of the file.
     *
     * @return an empty array if the record #1 is not set.
     * @since 1.0.0
     */
    virtual const std::vector<uint8_t> getContent() const = 0;

    /**
     * Gets a reference to the known content of a specific record.
     *
     * @param numRecord The record number.
     * @return an empty array if the requested record is not set.
     * @since 1.0.0
     */
    virtual const std::vector<uint8_t> getContent(const uint8_t numRecord) const = 0;

    /**
     * Gets a copy of a known content subset of a specific record from dataOffset to dataLength.
     *
     * @param numRecord The record number.
     * @param dataOffset The offset index (should be {@code >=} 0).
     * @param dataLength The data length (should be {@code >=} 1).
     * @return a not empty copy of the record subset content when the record is set, an empty array
     *         when the record is not set.
     * @throw IllegalArgumentException if dataOffset {@code <} 0 or dataLength {@code <} 1.
     * @throw IndexOutOfBoundsException if dataOffset {@code >=} content length or (dataOffset +
     *        dataLength) {@code >} content length.
     * @since 1.0.0
     */
    virtual const std::vector<uint8_t> getContent(const uint8_t numRecord,
                                                  const uint8_t dataOffset,
                                                  const uint8_t dataLength) const = 0;

    /**
     * Gets a reference to all known records content.
     *
     * @return a not null map possibly empty if there's no content.
     * @since 1.0.0
     */
    virtual const std::map<const uint8_t, std::vector<uint8_t>>& getAllRecordsContent() const = 0;

    /**
     * Gets the known value of the counter #numCounter.<br>
     * The counter value is extracted from the 3 next bytes at the index [(numCounter - 1) * 3] of
     * the record #1.<br>
     * e.g. if numCounter == 2, then value is extracted from bytes indexes [3,4,5].
     *
     * @param numCounter The counter number (should be {@code >=} 1).
     * @return The counter value or null if record #1 or numCounter is not set.
     * @throw IllegalArgumentException if numCounter is {@code <} 1.
     * @throw IndexOutOfBoundsException if numCounter has a truncated value (when size of record #1
     *        modulo 3 != 0).
     * @since 1.0.0
     */
    virtual const std::shared_ptr<int> getContentAsCounterValue(const int numCounter) const = 0;

    /**
     * Gets all known counters value.<br>
     * The counters values are extracted from record #1.<br>
     * If last counter has a truncated value (when size of record #1 modulo 3 != 0), then last
     * counter value is not returned.
     *
     * @return an empty map if record #1 is not set.
     * @since 1.0.0
     */
    virtual const std::map<const int, const int> getAllCountersValue() const = 0;
};

}
}
}
}
