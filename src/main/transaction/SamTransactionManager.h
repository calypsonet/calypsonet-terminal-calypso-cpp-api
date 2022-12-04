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

/* Calypsonet Terminal Calypso */
#include "CommonTransactionManager.h"
#include "SamSecuritySetting.h"

namespace calypsonet {
namespace terminal {
namespace calypso {
namespace transaction {

/**
 * Service providing the high-level API to manage transactions with a Calypso SAM.
 *
 * <p>The target CalypsoSam object provided to the build is kept and updated at each step of
 * using the service. It is the main container of the data handled during the transaction and acts
 * as a SAM image.
 *
 * <p>There are two main steps in using the methods of this service:
 *
 * <ul>
 *   <li>A command preparation step during which the application invokes prefixed "prepare" methods
 *       that will add to an internal list of commands to be executed by the SAM. The incoming data
 *       to the target SAM are placed in {@link CalypsoSam}.
 *   <li>A processing step corresponding to the prefixed "process" methods, which will carry out the
 *       communications with the target SAM. The outgoing data from the card are placed in
 *       CalypsoSam.
 * </ul>
 *
 * <p>Technical or data errors, security conditions, etc. are reported as exceptions.
 *
 * @since 1.2.0
 */
class SamTransactionManager
: public CommonTransactionManager<SamTransactionManager, SamSecuritySetting> {
public:
    /**
     * Gets the reader used to communicate with the target SAM on which the transaction is
     * performed.
     *
     * @return A not null reference.
     * @since 1.2.0
     */
    virtual CardReader getSamReader() const = 0;

    /**
     * Gets the target SAM on which the transaction is performed.
     *
     * @return A not null CalypsoSam having a CalypsoSam::ProductType different from
     *         CalypsoSam::ProductType::UNKNOWN.
     * @since 1.2.0
     */
    virtual CalypsoSam getCalypsoSam() const = 0;
};

}
}
}
}
