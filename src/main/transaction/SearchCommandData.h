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
namespace transaction {

/**
 * Contains the input/output data of the
 * CardTransactionManager::prepareSearchRecords(SearchCommandData) method.
 *
 * @since 1.1.0
 */
class SearchCommandData {
public:
    /**
     * Sets the SFI of the EF in which the search is to be performed.
     *
     * @param sfi The SFI of the EF.
     * @return The current instance.
     * @since 1.1.0
     */
    virtual SearchCommandData& setSfi(const uint8_t sfi) = 0;

    /**
     * Sets the number of the record where the search should begin.
     *
     * <p>By default, the search will begin from the first record.
     *
     * @param recordNumber The number of the record where the search should begin.
     * @return The current instance.
     * @since 1.1.0
     */
    virtual SearchCommandData& startAtRecord(const int recordNumber) = 0;

    /**
     * Sets the offset in number of bytes from which the analysis should be performed within a
     * record.
     *
     * <p>By default, the analysis will start at the beginning of the record (offset 0).
     *
     * @param offset The offset.
     * @return The current instance.
     * @since 1.1.0
     */
    virtual SearchCommandData& setOffset(const int offset) = 0;

    /**
     * Allows the command to analyze the data present at the given offset, and repeatedly at each
     * following offset, until the end of the record is reached. The last offset is less or equal
     * than ((record size) − (length of the search data)).
     *
     * @return The current instance.
     * @since 1.1.0
     */
    virtual SearchCommandData& enableRepeatedOffset() = 0;

    /**
     * Sets the data to search.
     *
     * @param data The data to search.
     * @return The current instance.
     * @since 1.1.0
     */
    virtual SearchCommandData& setSearchData(const std::vector<uint8_t>& data) = 0;

    /**
     * Sets the mask of bits to take into account during the comparison (padded right with FFh if
     * absent or incomplete).
     *
     * <p>Requirement: The length of the mask must be <b>less or equal</b> than the length of the
     * data to search.
     *
     * @param mask The mask.
     * @return The current instance.
     * @since 1.1.0
     */
    virtual SearchCommandData& setMask(const std::vector<uint8_t>& mask) = 0;

    /**
     * Requests to fetch the content of the first matching record into the {@link
     * org.calypsonet.terminal.calypso.card.CalypsoCard}.
     *
     * @return The current instance.
     * @since 1.1.0
     */
    virtual SearchCommandData& fetchFirstMatchingResult() = 0;

    /**
     * Returns a list containing the numbers of the records who has matched.
     *
     * @return An empty list if no record has matched or if the command has not yet been processed.
     * @since 1.1.0
     */
    virtual const std::vector<int> getMatchingRecordNumbers() = 0;
};

}
}
}
}
