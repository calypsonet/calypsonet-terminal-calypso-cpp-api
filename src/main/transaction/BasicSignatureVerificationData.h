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
#include "CommonSignatureVerificationData.h"

namespace calypsonet {
namespace terminal {
namespace calypso {
namespace transaction {

/**
 * Contains the input/output data of the
 * CommonTransactionManager::prepareVerifySignature(CommonSignatureVerificationData) method for
 * basic signature verification using the "Data Cipher" SAM command.
 *
 * @since 1.2.0
 */
class BasicSignatureVerificationData
: virtual public CommonSignatureVerificationData<BasicSignatureVerificationData> {
public:
    /**
     *
     */
    virtual ~BasicSignatureVerificationData() {}
};

}
}
}
}
