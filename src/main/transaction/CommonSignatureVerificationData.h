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
#include <vector>

namespace calypsonet {
namespace terminal {
namespace calypso {
namespace transaction {

/**
 * Contains the input/output data of the
 * CommonTransactionManager::prepareVerifySignature(CommonSignatureVerificationData) method for
 * common signature verification modes.
 *
 * @param <T> The type of the lowest level child object.
 * @since 1.2.0
 */
template <typename T>
class CommonSignatureVerificationData {
public:
    /**
     * Sets the signed data, the associated signature and the KIF/KVC of the key to be used for the
     * signature verification.
     *
     * @param data The signed data.
     * @param signature The associated signature.
     * @param kif The KIF of the key to be used for the signature verification.
     * @param kvc The KVC of the key to be used for the signature verification.
     * @return The current instance.
     * @since 1.2.0
     */
    virtual T& setData(const std::vector<uint8_t>& data,
                       const std::vector<uint8_t>& signature,
                       const uint8_t kif,
                       const uint8_t kvc) = 0;

    /**
     * Sets a specific key diversifier to use before verifying the signature (optional).
     *
     * <p>By default, the key diversification is performed with the full serial number of the target
     * card or SAM depending on the transaction context (Card or SAM transaction).
     *
     * @param diversifier The diversifier to be used (from 1 to 8 bytes long).
     * @return The current instance.
     * @since 1.2.0
     */
    virtual T& setKeyDiversifier(const std::vector<uint8_t>& diversifier) = 0;

    /**
     * Returns the result of the signature verification process by indicating if the signature is
     * valid or not.
     *
     * @return True if the signature is valid.
     * @throw IllegalStateException If the command has not yet been processed.
     * @since 1.2.0
     */
    virtual bool isSignatureValid() const = 0;
};

}
}
}
}
