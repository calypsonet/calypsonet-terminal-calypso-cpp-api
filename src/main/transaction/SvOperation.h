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

namespace calypsonet {
namespace terminal {
namespace calypso {
namespace transaction {

/**
 * Defines the type of Stored Value operation to be performed.
 *
 * @since 1.0
 */
enum class SvOperation {
    /**
     * Increase the balance of the stored value
     *
     * @since 1.0
     */
    RELOAD,

    /**
     * Decrease the balance of the stored value
     *
     * @since 1.0
     */
    DEBIT
};

}
}
}
}
