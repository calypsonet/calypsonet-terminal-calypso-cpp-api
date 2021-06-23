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
#include "ElementaryFile.h"

namespace calypsonet {
namespace terminal {
namespace calypso {
namespace card {

/**
 * Calypso EF metadata.
 *
 * @since 1.0
 */
class FileHeader {
public:
    /**
     * Gets the associated LID.
     *
     * @return The LID
     * @since 1.0
     */
    virtual uint16_t getLid() const = 0;

    /**
     * Gets the DF status.
     *
     * @return The DF status byte
     * @since 1.0
     */
    virtual uint8_t getDfStatus() const = 0;

    /**
     * Gets the Elementary File type.
     *
     * @return A not null file type.
     * @since 1.0
     */
    virtual ElementaryFile::Type getEfType() const = 0;

    /**
     * Gets the number of records :
     *
     * <ul>
     *   <li>For a Counter file, the number of records is always 1.<br>
     *       Extra bytes (rest of the division of the file size by 3) aren't accessible.
     *   <li>For a Binary file, the number of records is always 1.
     * </ul>
     *
     * @return The number of records.
     * @since 1.0
     */
    virtual int getRecordsNumber() const = 0;

    /**
     * Gets the size of a record :
     *
     * <ul>
     *   <li>For a Counter file, the record size is the original size of the record #1.<br>
     *       Extra bytes (rest of the division of the file size by 3) aren't accessible.
     *   <li>For a Binary file, the size of the record is corresponding to the file size.
     * </ul>
     *
     * @return The size of a record.
     * @since 1.0
     */
    virtual int getRecordSize() const = 0;

    /**
     * Gets a reference to the access conditions.
     *
     * @return A not empty byte array reference.
     * @since 1.0
     */
    virtual const std::vector<uint8_t>& getAccessConditions() const = 0;

    /**
     * Gets a reference to the keys indexes.
     *
     * @return A not empty byte array reference.
     * @since 1.0
     */
    virtual const std::vector<uint8_t>& getKeyIndexes() = 0;

    /**
     * Gets the shared reference of a shared file.
     *
     * @return Null if file is not shared.
     * @since 1.0
     */
    virtual const std::shared_ptr<uint16_t> getSharedReference() const = 0;
};

}
}
}
}
