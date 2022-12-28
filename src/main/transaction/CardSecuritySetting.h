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

#include <memory>

/* Calypsonet Terminal Calypso */
#include "CalypsoSam.h"
#include "CommonSecuritySetting.h"
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
 * Data to manage the security operations of a Calypso card transaction.
 *
 * @since 1.0.0
 */
class CardSecuritySetting : virtual public CommonSecuritySetting<CardSecuritySetting> {
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
     * @since 1.0.0
     * @deprecated Use setControlSamResource(CardReader, CalypsoSam) instead.
     */
    virtual CardSecuritySetting& setSamResource(const std::shared_ptr<CardReader> samReader,
                                                const std::shared_ptr<CalypsoSam> calypsoSam) = 0;

    /**
     * Enables multiple session mode to allow more changes to the card than the session buffer can
     * handle.
     *
     * @return The current instance.
     * @since 1.0.0
     */
    virtual CardSecuritySetting& enableMultipleSession() = 0;

    /**
     * Enables the ratification mechanism to handle the early removal of the card preventing the
     * terminal from receiving the acknowledgement of the session closing.
     *
     * @return The current instance.
     * @since 1.0.0
     */
    virtual CardSecuritySetting& enableRatificationMechanism() = 0;

    /**
     * Enables the PIN transmission in plain text.
     *
     * @return The current instance.
     * @since 1.0.0
     */
    virtual CardSecuritySetting& enablePinPlainTransmission() = 0;

    /**
     * Enables the retrieval of both loading and debit log records.
     *
     * <p>The default value is false.
     *
     * @return The current instance.
     * @since 1.0.0
     */
    virtual CardSecuritySetting& enableSvLoadAndDebitLog() = 0;

    /**
     * Allows the SV balance to become negative.
     *
     * <p>The default value is false.
     *
     * @return The current instance.
     * @since 1.0.0
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
     * @since 1.0.0
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
     * @since 1.0.0
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
     * @since 1.0.0
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
     * @since 1.0.0
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
     * @since 1.0.0
     */
    virtual CardSecuritySetting& addAuthorizedSvKey(const uint8_t kif, const uint8_t kvc) = 0;

    /**
     * Sets the KIF/KVC pair of the PIN verification ciphering key.
     *
     * <p>The default value for both KIF and KVC is 0.
     *
     * @param kif The KIF value.
     * @param kvc The KVC value.
     * @return The current instance.
     * @since 1.0.0
     */
    virtual CardSecuritySetting& setPinVerificationCipheringKey(const uint8_t kif,
                                                                const uint8_t kvc) = 0;

    /**
     * Sets the KIF/KVC pair of the PIN modification ciphering key.
     *
     * <p>The default value for both KIF and KVC is 0.
     *
     * @param kif The KIF value.
     * @param kvc The KVC value.
     * @return The current instance.
     * @since 1.0.0
     */
    virtual CardSecuritySetting& setPinModificationCipheringKey(const uint8_t kif,
                                                                const uint8_t kvc) = 0;
};

}
}
}
}
