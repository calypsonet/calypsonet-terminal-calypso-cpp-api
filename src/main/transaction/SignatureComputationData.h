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
 * CommonTransactionManager::prepareComputeSignature(SignatureComputationData) method.
 *
 * @since 1.2.0
 */
classs SignatureComputationData {
public
    /**
     * Sets the data to be signed and the KIF/KVC of the key to be used for the signature
     * computation.
     *
     * @param data The data to be signed.
     * @param kif The KIF of the key to be used for the signature computation.
     * @param kvc The KVC of the key to be used for the signature computation.
     * @return The current instance.
     * @since 1.2.0
     */
    virtual SignatureComputationData& setData(const std::vector<uint8_t>& data, 
                                              const uint8_t kif, 
                                              const uint8_t kvc) = 0;

    /**
     * Sets the expected size of the signature in bytes, which can be between 1 and 8 bytes
     * (optional).
     *
     * <p>By default, the signature will be generated on 8 bytes.
     *
     * <p>Note: the longer the signature, the more secure it is.
     *
     * @param size The expected size [1..8]
     * @return The current instance.
     * @since 1.2.0
     */
    virtual SignatureComputationData& setSignatureSize(const int size) = 0;

    /**
     * Sets a specific key diversifier to use before signing (optional).
     *
     * <p>By default, the key diversification is performed with the full serial number of the target
     * card or SAM depending on the transaction context (Card or SAM transaction).
     *
     * @param diversifier The diversifier to be used (from 1 to 8 bytes long).
     * @return The current instance.
     * @since 1.2.0
     */
    virtual SignatureComputationData& setKeyDiversifier(const std::vector<uint8_t>& diversifier) 
        = 0;

    /**
     * Enables the "SAM traceability" mode to securely record in the data to sign the SAM serial
     * number and the value of the counter associated with the signing key.
     *
     * <p>The SAM replaces the bits after the indicated offset by its serial number (3 or 4 bytes)
     * followed by the new value (3 bytes) of the counter.
     *
     * <p>To reduce the size of the data modified, the SAM may use only the 3 LSBytes of its serial
     * number. With the full serial number, 56 bits of data are replaced. With the 3 LSBytes of the
     * serial number, 48 bits of data are replaced.
     *
     * <p>By default, the "SAM traceability" mode is disabled.
     *
     * @param offset The offset in bits.
     * @param usePartialSamSerialNumber True if only the 3 LSBytes of the SAM serial number should
     *        be used.
     * @return The current instance.
     * @since 1.2.0
     */
    virtual SignatureComputationData& withSamTraceabilityMode(const int offset, 
                                                              const bool usePartialSamSerialNumber) 
        = 0;

    /**
     * Disables the "Busy" mode. When enabled, if the "PSO Verify Signature" command used to check
     * the signature fails because of an incorrect signature, other "PSO Verify Signature" command
     * with "Busy" mode is rejected for a few seconds by responding with the "busy" status word. For
     * security reasons, it is recommended to use the "Busy" mode in all new usages of this command.
     *
     * <p>By default, the "Busy" mode is enabled.
     *
     * @return The current instance.
     * @since 1.2.0
     */
    virtual SignatureComputationData& withoutBusyMode() = 0;

    /**
     * Returns the data that was used to generate the signature. If the "SAM traceability" mode was
     * enabled, then the signed data are the original data modified with the SAM traceability
     * information.
     *
     * @return A byte array of the same size as the original data to be signed.
     * @throws IllegalStateException If the command has not yet been processed.
     * @since 1.2.0
     */
    const std::vector<uint8_t>& getSignedData() const = 0;

    /**
     * Returns the computed signature.
     *
     * @return A byte array of 1 to 8 bytes.
     * @throws IllegalStateException If the command has not yet been processed.
     * @since 1.2.0
     */
    const std::vector<uint8_t>& getSignature() const = 0;
};

}
}
}
}
