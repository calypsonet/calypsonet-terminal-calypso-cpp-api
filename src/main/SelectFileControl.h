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

namespace calypsonet {
namespace terminal {
namespace calypso {

/**
 * Enumeration of all expected behaviors of the selection command (see the specifics of this command
 * in the ISO7816-4 standard and the Calypso specification).
 *
 * @since 1.0
 */
enum class SelectFileControl {
    /**
     * The first EF of the current Calypso DF
     *
     * @since 1.0
     */
    FIRST_EF,

    /**
     * The next EF of the current Calypso DF
     *
     * @since 1.0
     */
    NEXT_EF,

    /**
     * The Calypso DF
     *
     * @since 1.0
     */
    CURRENT_DF
};

}
}
}
