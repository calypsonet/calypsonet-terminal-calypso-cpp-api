/**************************************************************************************************
 * Copyright (c) 2022 Calypso Networks Association https://calypsonet.org/                        *
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
#include <ostream>
#include <string>
#include <vector>

/* Calypsonet Terminal Reader */
#include "SmartCard.h"

namespace calypsonet {
namespace terminal {
namespace calypso {
namespace sam {

using namespace calypsonet::terminal::reader::selection::spi;

/**
 * A static and partial view of the SAM's content.
 *
 * @since 1.0.0
 */
class CalypsoSam : public SmartCard {
public:
    /**
     * All Calypso SAM products supported by this API.
     *
     * @since 1.0.0
     */
    enum class ProductType {
        /**
         * SAM C1
         *
         * @since 1.0.0
         */
        SAM_C1,

        /**
         * SAM S1E1
         *
         * @since 1.0.0
         */
        SAM_S1E1,

        /**
         * SAM S1Dx
         *
         * @since 1.0.0
         */
        SAM_S1DX,

        /**
         * SAM CSAM_F
         *
         * @since 1.0.0
         */
        CSAM_F,

        /**
         * Unidentified smart card.
         *
         * @since 1.0.0
         */
        UNKNOWN
    };

    /**
     * Gets the SAM product type.
     *
     * @return The identified product type.
     * @since 1.0.0
     */
    virtual ProductType getProductType() const = 0;

    /**
     * Gets a text description of the SAM.
     *
     * @return A not null String.
     * @since 1.0.0
     */
    virtual const std::string getProductInfo() const = 0;

    /**
     * Gets the SAM serial number as an array of bytes
     *
     * @return A not null array of bytes
     * @since 1.0.0
     */
    virtual const std::vector<uint8_t>& getSerialNumber() const = 0;

    /**
     * Gets the platform identifier
     *
     * @return A byte
     * @since 1.0.0
     */
    virtual uint8_t getPlatform() const = 0;

    /**
     * Gets the application type
     *
     * @return A byte
     * @since 1.0.0
     */
    virtual uint8_t getApplicationType() const = 0;

    /**
     * Gets the application subtype
     *
     * @return A byte
     * @since 1.0.0
     */
    virtual uint8_t getApplicationSubType() const = 0;

    /**
     * Gets the software issuer identifier
     *
     * @return A byte
     * @since 1.0.0
     */
    virtual uint8_t getSoftwareIssuer() const = 0;

    /**
     * Gets the software version number
     *
     * @return A byte
     * @since 1.0.0
     */
    virtual uint8_t getSoftwareVersion() const = 0;

    /**
     * Gets the software revision number
     *
     * @return A byte
     * @since 1.0.0
     */
    virtual uint8_t getSoftwareRevision() const = 0;
};

inline std::ostream& operator<<(std::ostream& os, const CalypsoSam::ProductType& pt)
{
    os << "PRODUCT_TYPE: ";

    switch (pt) {
    case CalypsoSam::ProductType::SAM_C1:
        os << "SAM_C1";
        break;
    case CalypsoSam::ProductType::SAM_S1E1:
        os << "SAM_S1E1";
        break;
    case CalypsoSam::ProductType::SAM_S1DX:
        os << "SAM_S1DX";
        break;
    case CalypsoSam::ProductType::CSAM_F:
        os << "CSAM_F";
        break;
    default:
        os << "UNKNOWN";
        break;
    }

    return os;
}

}
}
}
}
