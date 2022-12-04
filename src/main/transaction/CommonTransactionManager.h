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
 * Common service providing the high-level API to manage transactions with a Calypso card or SAM.
 *
 * @param <T> The type of the lowest level child object.
 * @param <E> The type of the lowest level child object of the associated {@link
 *     CommonSecuritySetting}.
 * @since 1.2.0
 */
template <typename T, typename E>
class CommonTransactionManager {
public:
    /**
     * Returns the settings defining the security parameters of the transaction.
     *
     * @return Null if the transaction does not use security settings.
     * @since 1.2.0
     */
    virtual const std::shared_ptr<E> getSecuritySetting() const = 0;

    /**
     * Returns the audit data of the transaction containing all APDU exchanges with the card and the
     * SAM.
     *
     * @return An empty list if there is no audit data.
     * @since 1.2.0
     */
    virtual const std::vector<uint8_t>& getTransactionAuditData() const = 0;

    /**
     * Schedules the execution of a "PSO Compute Signature" SAM command.
     *
     * <p>Once the command is processed, the result will be available in the provided input/output
     * SignatureComputationData object.
     * 
     * <p>The signature may be used for many purposes, for example:
     *
     * <ul>
     *   <li>To add a signature to data recorded in a contactless card or ticket.<br>
     *       <u>Remark</u>: to speed up processing, it is recommended to use a constant signing key
     *       (which is not diversified before ciphering). Instead, the serial number of the card or
     *       ticket should be inserted at the beginning of the data to sign.
     *   <li>To sign some data reported from a terminal to a central system.<br>
     *       <u>Remark</u>: in this case, the terminal SAM contains a signing work key diversified
     *       with its own serial number, guarantying that the data has indeed been signed by this
     *       SAM. The central system SAM uses the master signing key, diversified before signing
     *       with the diversifier set previously by "Select Diversifier" command.
     * </ul>
     *
     * @param data The input/output data containing the parameters of the command.
     * @return The current instance.
     * @throw IllegalArgumentException If the input data is inconsistent.
     * @see SignatureComputationData
     * @since 1.2.0
     */
    virtual T& prepareComputeSignature(std::shared_ptr<SignatureComputationData> data) = 0;

    /**
     * Schedules the execution of a "PSO Verify Signature" SAM command.
     *
     * <p>Once the command is processed, the result will be available in the provided input/output
     * SignatureVerificationData object.
     *
     * @param data The input/output data containing the parameters of the command.
     * @return The current instance.
     * @throw IllegalArgumentException If the input data is inconsistent.
     * @throw SamRevokedException If the signature has been computed in "SAM traceability" mode and
     *        the SAM revocation status check has been requested and the SAM is revoked.
     * @see SignatureVerificationData
     * @since 1.2.0
     */
    virtual T& prepareVerifySignature(std::shared_ptr<SignatureVerificationData> data) = 0;

    /**
     * Process all previously prepared commands.
     *
     * @return The current instance.
     * @throw ReaderIOException If a communication error with the card reader or SAM reader occurs.
     * @throw CardIOException If a communication error with the card occurs.
     * @throw SamIOException If a communication error with the SAM occurs.
     * @throw UnexpectedCommandStatusException If a command returns an unexpected status.
     * @throw InconsistentDataException If inconsistent data have been detected.
     * @throw SessionBufferOverflowException If a secure session is open and multiple session mode
     *        is disabled and the session buffer capacity is not sufficient.
     * @throw CardSignatureNotVerifiableException If a secure session is open and multiple session
     *        mode is enabled and an intermediate session is correctly closed but the SAM is no
     *        longer available to verify the card signature.
     * @throw InvalidCardSignatureException If a secure session is open and multiple session mode is
     *        enabled and an intermediate session is correctly closed but the card signature is
     *        incorrect.
     * @since 1.2.0
     */
    T& processCommands();
};

}
}
}
}
