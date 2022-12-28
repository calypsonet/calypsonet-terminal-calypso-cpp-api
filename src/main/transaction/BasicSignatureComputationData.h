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
#include "CommonSignatureComputationData.h"

namespace calypsonet {
namespace terminal {
namespace calypso {
namespace transaction {

/**
 * Contains the input/output data of the
 * CommonTransactionManager::prepareComputeSignature(CommonSignatureComputationData)} method for
 * basic signature computation using the "Data Cipher" SAM command.
 *
 * @since 1.2.0
 */
class BasicSignatureComputationData
: virtual public CommonSignatureComputationData<BasicSignatureComputationData> {
public:
    /**
     *
     */
    virtual ~BasicSignatureComputationData() = default;
};

}
}
}
}
