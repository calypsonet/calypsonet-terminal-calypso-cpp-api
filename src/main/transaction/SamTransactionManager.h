/**************************************************************************************************
 * Copyright (c) 2023 Calypso Networks Association https://calypsonet.org/                        *
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
#include "CalypsoSam.h"
#include "CommonTransactionManager.h"
#include "SamSecuritySetting.h"

/* Calypsonet Terminal Reader */
#include "CardReader.h"

namespace calypsonet {
namespace terminal {
namespace calypso {
namespace transaction {

using namespace calypsonet::terminal::calypso::sam;
using namespace calypsonet::terminal::reader;

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
: virtual public CommonTransactionManager<SamTransactionManager, SamSecuritySetting> {
public:
    /**
     *
     */
    virtual ~SamTransactionManager() = default;

    /**
     * Gets the reader used to communicate with the target SAM on which the transaction is
     * performed.
     *
     * @return A not null reference.
     * @since 1.2.0
     */
    virtual const std::shared_ptr<CardReader> getSamReader() const = 0;

    /**
     * Gets the target SAM on which the transaction is performed.
     *
     * @return A not null CalypsoSam having a CalypsoSam::ProductType different from
     *         CalypsoSam::ProductType::UNKNOWN.
     * @since 1.2.0
     */
    virtual const std::shared_ptr<CalypsoSam> getCalypsoSam() const = 0;

    /**
     * Schedules the execution of a <b>Read Event Counter</b> command to read a single event
     * counter.
     *
     * <p>Once this command is processed, the result is available in CalypsoSam.
     *
     * @param eventCounterNumber The number of the event counter to read (in range [0..26]).
     * @return The current instance.
     * @throw IllegalArgumentException If the provided argument is out of range.
     * @since 1.4.0
     */
    virtual SamTransactionManager& prepareReadEventCounter(const int eventCounterNumber) = 0;

    /**
     * Schedules the execution of a <b>Read Event Counter</b> command to read one or more
     * consecutive event counters.
     *
     * <p>Once this command is processed, the result is available in CalypsoSam.
     *
     * @param fromEventCounterNumber The number of the first event counter to read (in range
     *        [0..26]).
     * @param toEventCounterNumber The number of the last event counter to read (in range [0..26]).
     * @return The current instance.
     * @throw IllegalArgumentException If one of the provided argument is out of range.
     * @since 1.4.0
     */
    virtual SamTransactionManager& prepareReadEventCounters(const int fromEventCounterNumber,
                                                            const int toEventCounterNumber) = 0;

    /**
     * Schedules the execution of a <b>Read Ceilings</b> command to read a single event ceiling.
     *
     * <p>Once this command is processed, the result is available in CalypsoSam.
     *
     * @param eventCeilingNumber The number of the event ceiling to read (in range [0..26]).
     * @return The current instance.
     * @throw IllegalArgumentException If the provided argument is out of range.
     * @since 1.4.0
     */
    virtual SamTransactionManager& prepareReadEventCeiling(const int eventCeilingNumber) = 0;

    /**
     * Schedules the execution of a <b>Read Ceilings</b> command to read one or more consecutive
     * event ceilings.
     *
     * <p>Once this command is processed, the result is available in {@link CalypsoSam}.
     *
     * @param fromEventCeilingNumber The number of the first event ceiling to read (in range
     *        0..26]).
     * @param toEventCeilingNumber The number of the last event ceiling to read (in range [0..26]).
     * @return The current instance.
     * @throw IllegalArgumentException If one of the provided argument is out of range.
     * @since 1.4.0
     */
    virtual SamTransactionManager& prepareReadEventCeilings(const int fromEventCeilingNumber,
                                                            const int toEventCeilingNumber) = 0;

    /**
     * Schedules the execution of a <b>Write Ceilings</b> command to write a single event ceiling.
     *
     * <p>Once this command is processed, the ceiling value available inCalypsoSam is updated.
     *
     * @param eventCeilingNumber The number of the event ceiling to write.
     * @param newValue The desired value for the event ceiling (defined as a positive int <=
     *        16777215 [FFFFFFh]).
     * @return The current instance.
     * @throw IllegalArgumentException If the provided argument is out of range.
     * @since 1.4.0
     */
    virtual SamTransactionManager& prepareWriteEventCeiling(const int eventCeilingNumber,
                                                            const int newValue) = 0;

    /**
     * Schedules the execution of a <b>Write Ceilings</b> command to write multiple event ceilings.
     *
     * <p>Once this command is processed, the ceiling values available in CalypsoSam} are
     * updated.
     *
     * @param fromEventCeilingNumber The number of the first event ceiling to write.
     * @param newValues A list of event ceilings values to be written from the indicated position
     *        (each event ceiling value is defined as a positive int <= 16777215 [FFFFFFh]).
     * @return The current instance.
     * @throw IllegalArgumentException If one of the provided argument is out of range.
     * @since 1.4.0
     */
    virtual SamTransactionManager& prepareWriteEventCeilings(const int fromEventCeilingNumber,
                                                             const std::vector<int>& newValues) = 0;
};

}
}
}
}
