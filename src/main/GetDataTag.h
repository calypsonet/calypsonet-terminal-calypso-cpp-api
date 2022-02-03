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

#include <string>

namespace calypsonet {
namespace terminal {
namespace calypso {

/**
 * Enumeration of all supported tags for the Get Data command.
 *
 * <p>May not be applicable to all products.
 *
 * @since 1.0.0
 */
enum class GetDataTag {
    /**
     * FCP for the current file, as returned by Select File.
     *
     * @since 1.0.0
     */
    FCP_FOR_CURRENT_FILE,

    /**
     * FCI for the current DF, as returned by Select Application.
     *
     * @since 1.0.0
     */
    FCI_FOR_CURRENT_DF,

    /**
     * List of EFs in the current DF.
     *
     * @since 1.1.0
     */
    EF_LIST,

    /**
     * Product traceability information.
     *
     * @since 1.1.0
     */
    TRACEABILITY_INFORMATION
};

}
}
}
