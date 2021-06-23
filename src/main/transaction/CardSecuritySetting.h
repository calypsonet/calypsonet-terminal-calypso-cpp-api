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

#include <memory>

/* Calypsonet Terminal Calypso */
#include "CalypsoSam.h"
#include "WriteAccessLevel.h"

/* Calypsonet Terminal Reader */
#include "CardReader.h"

namespace calypsonet {
namespace terminal {
namespace calypso {
namespace transaction {

using namespace calypsonet::terminal::calypso;
using namespace calypsonet::terminal::calypso::sam;
using namespace calypsonet::terminal::reader;

/**
 * Data to manage the security operations of a Calypso transaction.
 *
 * <p>Fluent setters allow to define all the required parameters, among which the resource profile
 * of the SAM card is the only mandatory one.
 *
 * @since 1.0
 */
class CardSecuritySetting {
public:
    /**
     * Defines the SAM and the reader through which it is accessible to be used to handle the
     * relevant cryptographic operations.
     *
     * @param samReader The SAM reader.
     * @param calypsoSam The Calypso SAM.
     * @return The current instance.
     * @throw IllegalArgumentException If one of the arguments is null or if the product type of
     *        calypsonet::terminal::calypso::sam::CalypsoSam is equal to
     *        calypsonet::terminal::calypso::sam::CalypsoSam::ProductType::UNKNOWN.
     * @since 1.0
     */
    virtual CardSecuritySetting& setSamResource(const std::shared_ptr<CardReader> samReader,
                                                const std::shared_ptr<CalypsoSam> calypsoSam) = 0;

    /**
     * Enables multiple session mode to allow more changes to the card than the session buffer can
     * handle.
     *
     * @return The current instance.
     * @since 1.0
     */
    virtual CardSecuritySetting& enableMultipleSession() = 0;

    /**
     * Enables the ratification mechanism to handle the early removal of the card preventing the
     * terminal from receiving the acknowledgement of the session closing.
     *
     * @return The current instance.
     * @since 1.0
     */
    virtual CardSecuritySetting& enableRatificationMechanism() = 0;

    /**
     * Enables the PIN transmission in plain text.
     *
     * @return The current instance.
     * @since 1.0
     */
    virtual CardSecuritySetting& enablePinPlainTransmission() = 0;

    /**
     * Enables the collection of transaction data for a later security audit.
     *
     * @return The current instance.
     * @since 1.0
     */
    virtual CardSecuritySetting& enableTransactionAudit() = 0;

    /**
     * Enables the retrieval of both loading and debit log records.
     *
     * <p>The default value is false.
     *
     * @return The current instance.
     * @since 1.0
     */
    virtual CardSecuritySetting& enableSvLoadAndDebitLog() = 0;

    /**
     * Allows the SV balance to become negative.
     *
     * <p>The default value is false.
     *
     * @return The current instance.
     * @since 1.0
     */
    virtual CardSecuritySetting& authorizeSvNegativeBalance() = 0;

    /**
     * Defines for a given write access level the KIF value to use for cards that only provide KVC.
     *
     * @param writeAccessLevel The write access level.
     * @param kvc The card's KVC value.
     * @param kif The KIF value to use.
     * @return The current instance.
     * @throw IllegalArgumentException If the provided writeAccessLevel is null.
     * @since 1.0
     */
    virtual CardSecuritySetting& assignKif(const WriteAccessLevel writeAccessLevel,
                                           const uint8_t kvc,
                                           const uint8_t kif) = 0;

    /**
     * Defines for a given write access level the default KIF value to use when it could not be
     * determined by any other means.
     *
     * @param writeAccessLevel The write access level.
     * @param kif The KIF value to use.
     * @return The current instance.
     * @throw IllegalArgumentException If the provided writeAccessLevel is null.
     * @since 1.0
     */
    virtual CardSecuritySetting& assignDefaultKif(const WriteAccessLevel writeAccessLevel,
                                                  const uint8_t kif) = 0;

    /**
     * Defines for a given write access level the KVC value to use for cards that do not provide KVC.
     *
     * @param writeAccessLevel The session level.
     * @param kvc The KVC to use.
     * @return The current instance.
     * @throw IllegalArgumentException If the provided writeAccessLevel is null.
     * @since 1.0
     */
    virtual CardSecuritySetting& assignDefaultKvc(const WriteAccessLevel writeAccessLevel,
                                                  const uint8_t kvc) = 0;

    /**
     * Adds an authorized session key defined by its KIF and KVC values.
     *
     * <p>By default, all keys are accepted. <br>
     * If at least one key is added using this method, then only authorized keys will be accepted.
     *
     * @param kif The KIF value.
     * @param kvc The KVC value.
     * @return The current instance.
     * @since 1.0
     */
    virtual CardSecuritySetting& addAuthorizedSessionKey(const uint8_t kif, const uint8_t kvc) = 0;

    /**
     * Adds an authorized Stored Value key defined by its KIF and KVC values.
     *
     * <p>By default, all keys are accepted. <br>
     * If at least one key is added using this method, then only authorized keys will be accepted.
     *
     * @param kif The KIF value.
     * @param kvc The KVC value.
     * @return The current instance.
     * @since 1.0
     */
    virtual CardSecuritySetting& addAuthorizedSvKey(const uint8_t kif, const uint8_t kvc) = 0;

    /**
     * Sets the KIF/KVC pair of the PIN ciphering key.
     *
     * <p>The default value for both KIF and KVC is 0.
     *
     * @param kif The KIF value.
     * @param kvc The KVC value.
     * @return The current instance.
     * @since 1.0
     */
    virtual CardSecuritySetting& setPinCipheringKey(const uint8_t kif, const uint8_t kvc) = 0;

    /**
     * Gets the associated SAM reader to use for secured operations.
     *
     * @return Null if no SAM reader is set.
     * @since 1.0
     */
    virtual std::shared_ptr<CardReader> getSamReader() const = 0;

    /**
     * Gets the SAM used for secured operations.
     *
     * @return Null if no SAM is set or a calypsonet::terminal::calypso::sam::CalypsoSam having a
     *         calypsonet::terminal::calypso::sam::CalypsoSam::ProductType different from
     *         calypsonet::terminal::calypso::sam::CalypsoSam::ProductType::UNKNOWN.
     * @since 1.0
     */
    virtual const std::shared_ptr<CalypsoSam> getCalypsoSam() const = 0;

    /**
     * Indicates if the multiple session mode is enabled.
     *
     * @return True if the multiple session mode is enabled.
     * @since 1.0
     */
    virtual bool isMultipleSessionEnabled() const = 0;

    /**
     * Indicates if the ratification mechanism is enabled.
     *
     * @return True if the ratification mechanism is enabled.
     * @since 1.0
     */
    virtual bool isRatificationMechanismEnabled() const = 0;

    /**
     * Indicates if the transmission of the PIN in plain text is enabled.
     *
     * @return True if the transmission of the PIN in plain text is enabled.
     * @since 1.0
     */
    virtual bool isPinPlainTransmissionEnabled() const = 0;

    /**
     * Indicates if the transaction audit is enabled.
     *
     * @return True if the transaction audit is enabled.
     * @since 1.0
     */
    virtual bool isTransactionAuditEnabled() const = 0;

    /**
     * Indicates if the retrieval of both load and debit log is enabled.
     *
     * @return True if the retrieval of both load and debit log is enabled.
     * @since 1.0
     */
    virtual bool isSvLoadAndDebitLogEnabled() const = 0;

    /**
     * Indicates if the SV balance is allowed to become negative.
     *
     * @return True if the retrieval of both load and debit log is enabled.
     * @since 1.0
     */
    virtual bool isSvNegativeBalanceAuthorized() const = 0;

    /**
     * Gets the KIF value to use for the provided write access level and KVC
     * value.
     *
     * @param writeAccessLevel The write access level.
     * @param kvc The KVC value.
     * @return Null if no KIF is available.
     * @throw IllegalArgumentException If the provided writeAccessLevel is null.
     * @since 1.0
     */
    virtual const std::shared_ptr<uint8_t> getKif(const WriteAccessLevel writeAccessLevel,
                                                  const uint8_t kvc) const = 0;

    /**
     * Gets the default KIF value for the provided write access level.
     *
     * @param writeAccessLevel The write access level.
     * @return Null if no KIF is available.
     * @throw IllegalArgumentException If the provided argument is null.
     * @since 1.0
     */
    virtual const std::shared_ptr<uint8_t> getDefaultKif(const WriteAccessLevel writeAccessLevel)
        const = 0;

    /**
     * Gets the default KVC value for the provided write access level.
     *
     * @param writeAccessLevel The write access level.
     * @return Null if no KVC is available.
     * @throw IllegalArgumentException If the provided argument is null.
     * @since 1.0
     */
    virtual const std::shared_ptr<uint8_t> getDefaultKvc(const WriteAccessLevel writeAccessLevel)
        const = 0;

    /**
     * Indicates if the KIF/KVC pair is authorized for a session.
     *
     * @param kif The KIF value.
     * @param kvc The KVC value.
     * @return False if KIF or KVC is null or unauthorized.
     * @since 1.0
     */
    virtual bool isSessionKeyAuthorized(const std::shared_ptr<uint8_t> kif,
                                        const std::shared_ptr<uint8_t> kvc) const = 0;

    /**
     * Indicates if the KIF/KVC pair is authorized for a SV operation.
     *
     * @param kif The KIF value.
     * @param kvc The KVC value.
     * @return False if KIF or KVC is null or unauthorized.
     * @since 1.0
     */
    virtual bool isSvKeyAuthorized(const std::shared_ptr<uint8_t> kif,
                                   const std::shared_ptr<uint8_t> kvc) const = 0;

    /**
     * Gets the KIF value of the PIN ciphering key.
     *
     * @return Null if no KIF is available.
     * @since 1.0
     */
    virtual const std::shared_ptr<uint8_t> getPinCipheringKif() const = 0;

    /**
     * Gets the KVC value of the PIN ciphering key.
     *
     * @return Null if no KVC is available.
     * @since 1.0
     */
    virtual const std::shared_ptr<uint8_t> getPinCipheringKvc() const = 0;
};

}
}
}
}
