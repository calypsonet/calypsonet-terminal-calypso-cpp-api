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

#include <cstdint>
#include <vector>
#include <string>

/* Calypsonet Terminal Calypso */
#include "CalypsoCard.h"
#include "CardSecuritySetting.h"
#include "GetDataTag.h"
#include "SearchCommandData.h"
#include "SelectFileControl.h"
#include "SvAction.h"
#include "SvOperation.h"

/* Calypsonet Terminal Reader */
#include "CardReader.h"

/* Keyple Core Util */
#include "RuntimeException.h"

namespace calypsonet {
namespace terminal {
namespace calypso {
namespace transaction {

using namespace calypsonet::terminal::calypso;
using namespace calypsonet::terminal::calypso::card;
using namespace calypsonet::terminal::calypso::transaction;
using namespace calypsonet::terminal::reader;

/**
 * Service providing the high-level API to manage transactions with a Calypso card.
 *
 * <p>Depending on the type of operations required, the presence of a SAM may be necessary.
 *
 * <p>The calypsonet::terminal::calypso::card::CalypsoCard object provided to the build is kept and
 * updated at each step of using the service. It is the main container of the data handled during
 * the transaction and acts as a card image.
 *
 * <p>There are two main steps in using the methods of this service:
 *
 * <ul>
 *   <li>A command preparation step during which the application invokes prefixed "prepare" methods
 *       that will add to an internal list of commands to be executed by the card. The incoming data
 *       to the card are placed in calypsonet::terminal::calypso::card::CalypsoCard.
 *   <li>A processing step corresponding to the prefixed "process" methods, which will carry out the
 *       communications with the card and if necessary the SAM. The outgoing data from the card are
 *       placed in calypsonet::terminal::calypso::card::CalypsoCard.
 * </ul>
 *
 * <p>Technical or data errors, security conditions, etc. are reported as exceptions.
 *
 * <p>For all "prepare" type commands, unless otherwise specified, here are the ranges of values
 * checked for the various parameters:
 *
 * <ul>
 *   <li>SFI: [0..30] (0 indicates the current EF)
 *   <li>Record number: [1..250]
 *   <li>Counter number: [1..83]
 *   <li>Counter value: [0..16777215]
 *   <li>Offset: [0..249] or [0..32767] for binary files (0 indicates the first byte)
 *   <li>Input data length: [1..250] or [1..32767] for binary files
 * </ul>
 *
 * @since 1.0.0
 */
class CardTransactionManager {
public:
    /**
     * Gets the reader used to communicate with the card on which the transaction is performed.
     *
     * @return A not null reference.
     * @since 1.0.0
     */
    virtual const std::shared_ptr<CardReader> getCardReader() const = 0;

    /**
     * Gets the card on which the transaction is performed.
     *
     * @return A not null calypsonet::terminal::calypso::card::CalypsoCard having a
     *         calypsonet::terminal::calypso::card::CalypsoCard::ProductType different from
     *         calypsonet::terminal::calypso::card::CalypsoCard::ProductType::UNKNOWN.
     * @since 1.0.0
     */
    virtual const std::shared_ptr<CalypsoCard> getCalypsoCard() const = 0;

    /**
     * Gets the settings defining the security parameters of the transaction.
     *
     * @return Null if the transaction does not use security settings.
     * @since 1.0.0
     */
    virtual const std::shared_ptr<CardSecuritySetting> getCardSecuritySetting() const = 0;

    /**
     * Gets the audit data of the transaction.
     *
     * @return Null if there is no audit data.
     * @since 1.0.0
     */
    virtual const std::string getTransactionAuditData() const = 0;

    /**
     * Schedules the execution of a <b>Select File</b> command based on the file's LID.
     *
     * <p>Once this command is processed, the result is available in
     * calypsonet::terminal::calypso::card::CalypsoCard through the
     * CalypsoCard#getFileBySfi(byte)/CalypsoCard#getFileByLid(short) and
     * ElementaryFile::getHeader() methods.
     *
     * @param lid The LID of the EF to select.
     * @return The current instance.
     * @throw IllegalArgumentException If the provided lid is not 2 bytes long.
     * @since 1.0.0
     * @deprecated Use prepareSelectFile(uint16_t) method instead.
     */
    virtual CardTransactionManager& prepareSelectFile(const std::vector<uint8_t>& lid) = 0;

    /**
     * Schedules the execution of a <b>Select File</b> command to select an EF by its LID in the
     * current DF
     *
     * <p>Once this command is processed, the result is available in CalypsoCard through the
     * CalypsoCard::getFileBySfi(byte)/CalypsoCard#getFileByLid(short) and
     * ElementaryFile#getHeader() methods.
     *
     * <p>Caution: the command will fail if the selected file is not an EF.
     *
     * @param lid The LID of the EF to select.
     * @return The current instance.
     * @since 1.1.0
     */
    virtual CardTransactionManager& prepareSelectFile(const uint16_t lid) = 0;

    /**
     * Schedules the execution of a <b>Select File</b> command using a navigation selectFileControl
     * defined by the ISO standard.
     *
     * <p>Once this command is processed, the result is available in
     * calypsonet::terminal::calypso::card::CalypsoCard through the
     * ElementaryFile#getHeader() methods.
     *
     * @param selectFileControl A calypsonet::terminal::calypso::card::SelectFileControl enum entry.
     * @return The current instance.
     * @throw IllegalArgumentException If selectFileControl is null.
     * @since 1.0.0
     */
    virtual CardTransactionManager& prepareSelectFile(const SelectFileControl selectFileControl) = 0;

    /**
     * Adds a command APDU to retrieve the data indicated by the provided tag.
     *
     * <p>The data returned by the command is used to update the current
     * calypsonet::terminal::calypso::card::CalypsoCard object.
     *
     * @param tag The tag to use.
     * @return The object instance.
     * @throw IllegalArgumentException If tag is null.
     * @throw UnsupportedOperationException If the Get Data command with the provided tag is not
     *        supported.
     * @since 1.0.0
     */
    virtual CardTransactionManager& prepareGetData(const GetDataTag tag) = 0;

    /**
     * Schedules the execution of a <b>Read Records</b> command to read a single record from the
     * indicated EF.
     *
     * <p>Once this command is processed, the result is available in
     * calypsonet::terminal::calypso::card::CalypsoCard.
     *
     * <p>Depending on whether we are inside a secure session, there are two types of
     * behavior following this command:
     *
     * <ul>
     *   <li>Outside a secure session (best effort mode): the following "process" command will not
     *       fail whatever the existence of the targeted file or record (the CalypsoCard
     *       object may not be filled).
     *   <li>Inside a secure session in contactless mode (strict mode): the following "process"
     *       command will fail if the targeted file or record does not exist (the CalypsoCard
     *       object is always filled or an exception is raised when the reading failed).
     * </ul>
     *
     * <p><b>This method should not be used inside a secure session in contact mode</b> because
     * additional exchanges with the card will be operated and will corrupt the security of the
     * session. Instead, use the method prepareReadRecordFile(byte, int, int, int) for this
     * case and provide valid parameters.
     *
     * @param sfi The SFI of the EF to read.
     * @param recordNumber The record to read.
     * @return The current instance.
     * @throw IllegalArgumentException If one of the provided arguments is out of range.
     * @throws IllegalStateException If this method is invoked inside a secure session in contact
     *         mode.
     * @since 1.0.0
     * @deprecated Use prepareReadRecords(const uint8_t, const int) method instead.
     */
    virtual CardTransactionManager& prepareReadRecordFile(const uint8_t sfi, const int recordNumber)
        = 0;

    /**
     * Schedules the execution of a <b>Read Records</b> command to read one or more records from the
     * indicated EF.
     *
     * <p>Once this command is processed, the result is available in
     * calypsonet::terminal::calypso::card::CalypsoCard.
     *
     * <p>Depending on whether we are inside a secure session, there are two types of
     * behavior following this command:
     *
     * <ul>
     *   <li>Outside a secure session (best effort mode): the following "process" command will not
     *       fail whatever the existence of the targeted file or record (the {@link CalypsoCard}
     *       object may not be filled).
     *   <li>Inside a secure session (strict mode): the following "process" command will fail if the
     *       targeted file or record does not exist (the {@link CalypsoCard} object is always filled
     *       or an exception is raised when the reading failed).<br>
     *       Invalid parameters could lead to additional exchanges with the card and thus corrupt
     *       the security of the session.
     * </ul>
     *
     * @param sfi The SFI of the EF.
     * @param firstRecordNumber The record to read (or first record to read in case of several
     *        records)
     * @param numberOfRecords The number of records expected.
     * @param recordSize The record length.
     * @return The current instance.
     * @throw IllegalArgumentException If one of the provided argument is out of range.
     * @since 1.0.0
     * @deprecated Use prepareReadRecords(const uint8_t, const int, const int, const int) method
     *            instead.
     */
    virtual CardTransactionManager& prepareReadRecordFile(const uint8_t sfi,
                                                          const int firstRecordNumber,
                                                          const int numberOfRecords,
                                                          const int recordSize) = 0;

    /**
     * Schedules the execution of a <b>Read Records</b> command to reads a record of the indicated
     * EF, which should be a counter file.
     *
     * <p>The record will be read up to the counter location indicated in parameter.<br>
     * Thus, all previous counters will also be read.
     *
     * <p>Once this command is processed, the result is available in
     * calypsonet::terminal::calypso::card::CalypsoCard.
     *
     * <p>Depending on whether we are inside a secure session, there are two types of behavior
     * following this command:
     *
     * <ul>
     *   <li>Outside a secure session (best effort mode): the following "process" command will not
     *       fail whatever the existence of the targeted file or counter (the  CalypsoCard
     *       object may not be filled).
     *   <li>Inside a secure session (strict mode): the following "process" command will fail if the
     *       targeted file or counter does not exist (the  CalypsoCard object is always filled
     *       or an exception is raised when the reading failed).<br>
     *       Invalid parameters could lead to additional exchanges with the card and thus corrupt the
     *       security of the session.
     * </ul>
     *
     * @param sfi The SFI of the EF.
     * @param countersNumber The number of the last counter to be read.
     * @return The current instance.
     * @throw IllegalArgumentException If one of the provided argument is out of range.
     * @since 1.0.0
     * @deprecated Use prepareReadCounter(const uint8_t, const int) method instead.
     */
    virtual CardTransactionManager& prepareReadCounterFile(const uint8_t sfi,
                                                           const int countersNumber) = 0;

    /**
     * Schedules the execution of a <b>Read Records</b> command to read a single record from the
     * indicated EF.
     *
     * <p>Once this command is processed, the result is available in CalypsoCard.
     *
     * <p>Depending on whether we are inside a secure session, there are two types of behavior
     * following this command:
     *
     * <ul>
     *   <li>Outside a secure session (best effort mode): the following "process" command will not
     *       fail whatever the existence of the targeted file or record (the CalypsoCard
     *       object may not be filled).
     *   <li>Inside a secure session in contactless mode (strict mode): the following "process"
     *       command will fail if the targeted file or record does not exist (the CalypsoCard
     *       object is always filled or an exception is raised when the reading failed).
     * </ul>
     *
     * <p><b>This method should not be used inside a secure session in contact mode</b> because
     * additional exchanges with the card will be operated and will corrupt the security of the
     * session. Instead, use the method
     * prepareReadRecordFile(const uint8_t, const int, const int, const int) for this case and
     * provide valid parameters.
     *
     * @param sfi The SFI of the EF to read.
     * @param recordNumber The record to read.
     * @return The current instance.
     * @throws IllegalArgumentException If one of the provided arguments is out of range.
     * @throws IllegalStateException If this method is invoked inside a secure session in contact
     *     mode.
     * @since 1.1.0
     */
    virtual CardTransactionManager& prepareReadRecord(const uint8_t sfi, const int recordNumber)
        = 0;

    /**
     * Schedules the execution of a <b>Read Records</b> command to read one or more records from the
     * indicated EF.
     *
     * <p>Once this command is processed, the result is available in CalypsoCard.
     *
     * <p>Depending on whether we are inside a secure session, there are two types of behavior
     * following this command:
     *
     * <ul>
     *   <li>Outside a secure session (best effort mode): the following "process" command will not
     *       fail whatever the existence of the targeted file or record (the CalypsoCard
     *       object may not be filled).
     *   <li>Inside a secure session (strict mode): the following "process" command will fail if the
     *       targeted file or record does not exist (the CalypsoCard object is always filled
     *       or an exception is raised when the reading failed).<br>
     *       Invalid parameters could lead to additional exchanges with the card and thus corrupt the
     *       security of the session.
     * </ul>
     *
     * @param sfi The SFI of the EF.
     * @param fromRecordNumber The number of the first record to read.
     * @param toRecordNumber The number of the last record to read.
     * @param recordSize The record length.
     * @return The current instance.
     * @throws IllegalArgumentException If one of the provided argument is out of range.
     * @since 1.1.0
     */
    virtual CardTransactionManager& prepareReadRecords(const uint8_t sfi,
                                                       const int fromRecordNumber,
                                                       const int toRecordNumber,
                                                       const int recordSize) = 0;

    /**
     * Schedules the execution of one or multiple <b>Read Record Multiple</b> commands to read all or
     * parts of multiple records of the indicated EF.
     *
     * <p>Once this command is processed, the result is available in CalypsoCard.
     *
     * <p>Depending on whether we are inside a secure session, there are two types of behavior
     * following this command:
     *
     * <ul>
     *   <li>Outside a secure session (best effort mode): the following "process" command will not
     *       fail whatever the existence of the targeted file or the validity of the offset and number
     *       of bytes to read (the CalypsoCard object may not be filled).
     *   <li>Inside a secure session (strict mode): the following "process" command will fail if the
     *       targeted file does not exist or if the offset and number of bytes to read are not valid
     *       (the CalypsoCard object is always filled or an exception is raised when the
     *       reading failed).<br>
     *       Invalid parameters could lead to additional exchanges with the card and thus corrupt the
     *       security of the session.
     * </ul>
     *
     * @param sfi The SFI of the EF.
     * @param fromRecordNumber The number of the first record to read.
     * @param toRecordNumber The number of the last record to read.
     * @param offset The offset in the records where to start reading (0 indicates the first byte).
     * @param nbBytesToRead The number of bytes to read from each record.
     * @return The current instance.
     * @throws UnsupportedOperationException If this command is not supported by this card.
     * @throws IllegalArgumentException If one of the provided argument is out of range.
     * @since 1.1.0
     */
    virtual CardTransactionManager& prepareReadRecordsPartially(const uint8_t sfi,
                                                                const int fromRecordNumber,
                                                                const int toRecordNumber,
                                                                const int offset,
                                                                const int nbBytesToRead) = 0;

    /**
     * Schedules the execution of one or multiple <b>Read Binary</b> commands to read all or part of
     * the indicated Binary EF.
     *
     * <p>Once this command is processed, the result is available in CalypsoCard.
     *
     * <p>Depending on whether we are inside a secure session, there are two types of behavior
     * following this command:
     *
     * <ul>
     *   <li>Outside a secure session (best effort mode): the following "process" command will not
     *       fail whatever the existence of the targeted file or the validity of the offset and number
     *       of bytes to read (the CalypsoCard object may not be filled).
     *   <li>Inside a secure session (strict mode): the following "process" command will fail if the
     *       targeted file does not exist or if the offset and number of bytes to read are not valid
     *       (the CalypsoCard object is always filled or an exception is raised when the
     *       reading failed).<br>
     *       Invalid parameters could lead to additional exchanges with the card and thus corrupt the
     *       security of the session.
     * </ul>
     *
     * @param sfi The SFI of the EF.
     * @param offset The offset (0 indicates the first byte).
     * @param nbBytesToRead The number of bytes to read.
     * @return The current instance.
     * @throws UnsupportedOperationException If this command is not supported by this card.
     * @throws IllegalArgumentException If one of the provided argument is out of range.
     * @since 1.1.0
     */
    virtual CardTransactionManager& prepareReadBinary(const uint8_t sfi,
                                                      const int offset,
                                                      const int nbBytesToRead) = 0;

    /**
     * Schedules the execution of a <b>Read Records</b> command to reads a record of the indicated EF,
     * which should be a counter file.
     *
     * <p>The record will be read up to the counter location indicated in parameter.<br>
     * Thus, all previous counters will also be read.
     *
     * <p>Once this command is processed, the result is available in CalypsoCard.
     *
     * <p>Depending on whether we are inside a secure session, there are two types of behavior
     * following this command:
     *
     * <ul>
     *   <li>Outside a secure session (best effort mode): the following "process" command will not
     *       fail whatever the existence of the targeted file or counter (the CalypsoCard
     *       object may not be filled).
     *   <li>Inside a secure session (strict mode): the following "process" command will fail if the
     *       targeted file or counter does not exist (the CalypsoCard object is always filled
     *       or an exception is raised when the reading failed).<br>
     *       Invalid parameters could lead to additional exchanges with the card and thus corrupt the
     *       security of the session.
     * </ul>
     *
     * @param sfi The SFI of the EF.
     * @param nbCountersToRead The number of counters to read.
     * @return The current instance.
     * @throws IllegalArgumentException If one of the provided argument is out of range.
     * @since 1.1.0
     */
    virtual CardTransactionManager& prepareReadCounter(const uint8_t sfi,
                                                       const int nbCountersToRead) = 0;

    /**
     * Schedules the execution of a <b>Search Record Multiple</b> command to search data in the
     * records of the indicated EF, from a given record to the last record of the file. It will
     * return the list of record numbers containing these data, and if requested it will read the
     * first record content.
     *
     * <p>The command is only possible with a Linear, Cyclic, Counters or Simulated Counter EF.
     *
     * <p>The command searches if the given data are present in the records of the file. During the
     * search, an optional mask is applied. The mask allows to specify precisely the bits to be
     * taken into account in the comparison.
     *
     * <p>See SearchCommandData class for a description of the parameters.
     *
     * <p>Once this command is processed, the result is available in the provided input/output
     * SearchCommandData object, and the content of the first matching record in CalypsoCard
     * if requested.
     *
     * <p>Depending on whether we are inside a secure session, there are two types of behavior
     * following this command:
     *
     * <ul>
     *   <li>Outside a secure session (best effort mode): the following "process" command will not
     *       fail whatever the existence of the targeted file or the validity of the record number
     *       and offset (the SearchCommandData and CalypsoCard objects may not be updated).
     *   <li>Inside a secure session (strict mode): the following "process" command will fail if the
     *       targeted file does not exist or if the record number and the offset are not valid (the
     *       SearchCommandData and CalypsoCard objects are always filled or an
     *       exception is raised when the reading failed).
     * </ul>
     *
     * @param data The input/output data containing the parameters of the command.
     * @return The current instance.
     * @throws IllegalArgumentException If the input data is inconsistent.
     * @since 1.1.0
     */
    virtual CardTransactionManager& prepareSearchRecords(
        const std::shared_ptr<SearchCommandData> data);

    /**
     * Schedules the execution of a <b>Verify Pin</b> command without PIN presentation in order to
     * get the attempt counter.
     *
     * <p>The PIN status will be made available in CalypsoCard after the execution of process
     * command.
     * <br>
     * Adds it to the list of commands to be sent with the next process command.
     *
     * <p>See calypsonet::terminal::calypso::card::CalypsoCard::isPinBlocked() and
     * calypsonet::terminal::calypso::card::CalypsoCard::getPinAttemptRemaining() methods.
     *
     * @return The current instance.
     * @throw UnsupportedOperationException If the PIN feature is not available for this card.
     * @since 1.0.0
     */
    virtual CardTransactionManager& prepareCheckPinStatus() = 0;

    /**
     * Schedules the execution of a <b>Append Record</b> command to adds the data provided in the
     * indicated cyclic file.
     *
     * <p>A new record is added, the oldest record is deleted.
     *
     * <p>Note: calypsonet::terminal::calypso::card::CalypsoCard is filled with the provided input
     * data.
     *
     * @param sfi The sfi to select.
     * @param recordData The new record data to write.
     * @return The current instance.
     * @throw IllegalArgumentException If one of the provided argument is out of range.
     * @since 1.0.0
     */
    virtual CardTransactionManager& prepareAppendRecord(const uint8_t sfi,
                                                        const std::vector<uint8_t>& recordData) = 0;

    /**
     * Schedules the execution of a <b>Update Record</b> command to overwrites the target file's
     * record contents with the provided data.
     *
     * <p>If the input data is shorter than the record size, only the first bytes will be
     * overwritten.
     *
     * <p>Note: calypsonet::terminal::calypso::card::CalypsoCard is filled with the provided input
     * data.
     *
     * @param sfi The sfi to select.
     * @param recordNumber The record to update.
     * @param recordData The new record data. If length {@code <} RecSize, bytes beyond length are
     *        left unchanged.
     * @return The current instance.
     * @throw IllegalArgumentException If one of the provided argument is out of range.
     * @since 1.0.0
     */
    virtual CardTransactionManager& prepareUpdateRecord(const uint8_t sfi,
                                                        const int recordNumber,
                                                        const std::vector<uint8_t> recordData) = 0;

    /**
     * Schedules the execution of a <b>Write Record</b> command to updates the target file's record
     * contents with the result of a binary OR between the existing data and the provided data.
     *
     * <p>If the input data is shorter than the record size, only the first bytes will be
     * overwritten.
     *
     * <p>Note: calypsonet::terminal::calypso::card::CalypsoCard is filled with the provided input
     * data.
     *
     * @param sfi The sfi to select.
     * @param recordNumber The record to write.
     * @param recordData The data to overwrite in the record. If length {@code <} RecSize, bytes.
     *        beyond length are left unchanged.
     * @return The current instance.
     * @throw IllegalArgumentException If one of the provided argument is out of range.
     * @since 1.0.0
     */
    virtual CardTransactionManager& prepareWriteRecord(const uint8_t sfi,
                                                       const int recordNumber,
                                                       const std::vector<uint8_t> recordData) = 0;

    /**
     * Schedules the execution of a <b>Update Binary</b> command to replace the indicated data of a
     * Binary file with the new data given from the indicated offset.
     *
     * <p>The data of the file before the offset and after the data given are left unchanged.
     *
     * <p>Note: CalypsoCard is filled with the provided input data.
     *
     * @param sfi The SFI of the EF to select.
     * @param offset The offset (0 indicates the first byte).
     * @param data The new data.
     * @return The current instance.
     * @throws UnsupportedOperationException If this command is not supported by this card.
     * @throws IllegalArgumentException If one of the provided argument is out of range.
     * @since 1.1.0
     */
    virtual CardTransactionManager& prepareUpdateBinary(const uint8_t sfi,
                                                        const int offset,
                                                        const std::vector<uint8_t>& data) = 0;

    /**
     * Schedules the execution of a <b>Write Binary</b> command to write over the indicated data of a
     * Binary file. The new data will be the result of a binary OR operation between the existing data
     * and the data given in the command from the indicated offset.
     *
     * <p>The data of the file before the offset and after the data given are left unchanged.
     *
     * <p>Note: CalypsoCard is computed with the provided input data.
     *
     * @param sfi The SFI of the EF to select.
     * @param offset The offset (0 indicates the first byte).
     * @param data The data to write over the existing data.
     * @return The current instance.
     * @throws UnsupportedOperationException If this command is not supported by this card.
     * @throws IllegalArgumentException If one of the provided argument is out of range.
     * @since 1.1.0
     */
    virtual CardTransactionManager& prepareWriteBinary(const uint8_t sfi,
                                                       const int offset,
                                                       const std::vector<uint8_t>&  data) = 0;

    /**
     * Schedules the execution of a <b>Increase</b> command to increase the target counter.
     *
     * <p>Note 1: CalypsoCard is updated with the provided input data.
     *
     * <p>Note 2: in the case where this method is invoked before the invocation of
     * processClosing(), the counter must have been read previously otherwise an
     * IllegalStateException will be raised during the execution of processClosing().
     *
     * @param sfi SFI of the EF to select.
     * @param counterNumber The number of the counter (must be zero in case of a simulated counter).
     * @param incValue Value to add to the counter (defined as a positive int {@code <=} 16777215
     *        [FFFFFFh])
     * @return The current instance.
     * @throw IllegalArgumentException If one of the provided argument is out of range.
     * @since 1.0.0
     */
    virtual CardTransactionManager& prepareIncreaseCounter(const uint8_t sfi,
                                                           const int counterNumber,
                                                           const int incValue) = 0;

    /**
     * Schedules the execution of a <b>Decrease</b> command to decrease the target counter.
     *
     * <p>Note 1: CalypsoCard is updated with the provided input data.
     *
     * <p>Note 2: in the case where this method is invoked before the invocation of
     * processClosing(), the counter must have been read previously otherwise an
     * IllegalStateException will be raised during the execution of #processClosing().
     *
     * @param sfi SFI of the EF to select.
     * @param counterNumberToIncValueMap The map containing the counter numbers to be incremented
     *        and their associated increment values.
     * @return The current instance.
     * @throws UnsupportedOperationException If the increase multiple command is not available for
     *         this card.
     * @throws IllegalArgumentException If one of the provided argument is out of range or if the
     *         map is null or empty.
     * @since 1.1.0
     */
    virtual CardTransactionManager& prepareDecreaseCounter(
        const uint8_t sfi, const std::map<int, int> counterNumberToIncValueMap) = 0;

    /**
     * Schedules the execution of a <b>Increase Multiple</b> command to increase multiple target
     * counters at the same time.
     *
     * <p>Note 1: CalypsoCard is updated with the provided input data.
     *
     * <p>Note 2: in the case where this method is invoked before the invocation of
     * processClosing(), the counter must have been read previously otherwise an
     * IllegalStateException} will be raised during the execution of processClosing().
     *
     * @param sfi SFI of the EF to select.
     * @param counterNumber The number of the counter (must be zero in case of a simulated counter).
     * @param decValue Value to subtract to the counter (defined as a positive int {@code <=}
     *        16777215 [FFFFFFh])
     * @return The current instance.
     * @throws IllegalArgumentException If one of the provided argument is out of range.
     * @since 1.0.0
     */
    virtual CardTransactionManager& prepareDecreaseCounter(const uint8_t sfi,
                                                           const int counterNumber,
                                                           const int decValue);

    /**
     * Schedules the execution of a <b>Decrease Multiple</b> command to decrease multiple target
     * counters at the same time.
     *
     * <p>Note 1: CalypsoCard is updated with the provided input data.
     *
     * <p>Note 2: in the case where this method is invoked before the invocation of
     * processClosing(), the counter must have been read previously otherwise an
     * IllegalStateException} will be raised during the execution of processClosing().
     *
     * @param sfi SFI of the EF to select.
     * @param counterNumberToDecValueMap The map containing the counter numbers to be decremented
     *        and their associated decrement values.
     * @return The current instance.
     * @throws UnsupportedOperationException If the decrease multiple command is not available for
     *         this card.
     * @throws IllegalArgumentException If one of the provided argument is out of range or if the
     *         map is null or empty.
     * @since 1.1.0
     */
    virtual CardTransactionManager& prepareDecreaseCounters(
        const uint8_t sfi, const std::map<int, int> counterNumberToDecValueMap) = 0;

    /**
     * Schedules the execution of a command to set the value of the target counter.
     *
     * <p>It builds an Increase or Decrease command and add it to the list of commands to be sent
     * with the next <b>process</b> command in order to set the target counter to the specified
     * value.<br> The operation (Increase or Decrease) is selected according to whether the
     * difference between the current value and the desired value is negative (Increase) or positive
     * (Decrease).
     *
     * <p>Note: it is assumed here that:<br>
     *
     * <ul>
     *   <li>the counter value has been read before,
     *   <li>the type of session (and associated access rights) is consistent with the requested
     *       operation: reload session if the counter is to be incremented, debit if it is to be
     *       decremented.<br>
     *       No control is performed on this point by this method; the closing of the session will
     *       determine the success of the operation..
     * </ul>
     *
     * @param counterNumber {@code >=} 1: Counters file, number of the counter. 0: Simulated.
     *        Counter file.
     * @param sfi SFI of the EF to select.
     * @param newValue The desired value for the counter (defined as a positive int {@code <=}
     *        16777215 [FFFFFFh])
     * @return The current instance.
     * @throw IllegalArgumentException If one of the provided argument is out of range.
     * @throw IllegalStateException If the current counter value is unknown.
     * @since 1.0.0
     */
    virtual CardTransactionManager& prepareSetCounter(const uint8_t sfi,
                                                      const int counterNumber,
                                                      const int newValue) = 0;

    /**
     * Schedules the execution of a <b>SV Get</b> command to prepare an SV operation or simply
     * retrieves the current SV status.
     *
     * <p>Once this command is processed, the result is available in
     * calypsonet::terminal::calypso::card::CalypsoCard.
     *
     * <p>See the methods CalypsoCard#getSvBalance(),
     * CalypsoCard#getSvLoadLogRecord(), CalypsoCard#getSvDebitLogLastRecord(),
     * CalypsoCard#getSvDebitLogAllRecords().
     *
     * @param svOperation Informs about the nature of the intended operation: debit or reload.
     * @param svAction The type of action: DO a debit or a positive reload, UNDO an undebit or a.
     *        negative reload
     * @return The current instance.
     * @throw IllegalArgumentException If one of the arguments is null.
     * @throw UnsupportedOperationException If the SV feature is not available for this card.
     * @since 1.0.0
     */
    virtual CardTransactionManager& prepareSvGet(const SvOperation svOperation,
                                                 const SvAction svAction) = 0;

    /**
     * Schedules the execution of a <b>SV Reload</b> command to increase the current SV balance and
     * using the provided additional data.
     *
     * <p>Note #1: a communication with the SAM is done here.
     *
     * <p>Note #2: the key used is the reload key.
     *
     * @param amount The value to be reloaded, positive or negative integer in the range.
     *        -8388608..8388607
     * @param date 2-byte free value.
     * @param time 2-byte free value.
     * @param free 2-byte free value.
     * @return The current instance.
     * @throw IllegalArgumentException If one of the provided argument is out of range.
     * @throw UnsupportedOperationException If the SV feature is not available for this card.
     * @throw CardTransactionException If a functional error occurs (including card and SAM IO
     *        errors)
     * @since 1.0.0
     */
    virtual CardTransactionManager& prepareSvReload(const int amount,
                                                    const std::vector<uint8_t>& date,
                                                    const std::vector<uint8_t>& time,
                                                    const std::vector<uint8_t>& free) = 0;

    /**
     * Schedules the execution of a <b>SV Reload</b> command to increase the current SV balance.
     *
     * <p>Note #1: the optional SV additional data are set to zero.
     *
     * <p>Note #2: a communication with the SAM is done here.
     *
     * <p>Note #3: the key used is the reload key.
     *
     * @param amount The value to be reloaded, positive integer in the range 0..8388607 for a DO.
     *        action, in the range 0..8388608 for an UNDO action.
     * @return The current instance.
     * @throw IllegalArgumentException If the provided argument is out of range.
     * @throw UnsupportedOperationException If the SV feature is not available for this card.
     * @throw CardTransactionException If a functional error occurs (including card and SAM IO
     *        errors)
     * @since 1.0.0
     */
    virtual CardTransactionManager& prepareSvReload(const int amount) = 0;

    /**
     * Schedules the execution of a <b>SV Debit</b> or <b>SV Undebit</b> command to increase the
     * current SV balance or to partially or totally cancels the last SV debit command and using the
     * provided additional data.
     *
     * <p>It consists in decreasing the current balance of the SV by a certain amount or canceling a
     * previous debit according to the type operation chosen in when invoking the previous SV Get
     * command.
     *
     * <p>Note #1: a communication with the SAM is done here.
     *
     * <p>Note #2: the key used is the reload key.
     *
     * @param amount The amount to be subtracted or added, positive integer in the range 0..32767
     *        when subtracted and 0..32768 when added.
     * @param date 2-byte free value.
     * @param time 2-byte free value.
     * @return The current instance.
     * @throw IllegalArgumentException If one of the provided argument is out of range.
     * @since 1.0.0
     */
    virtual CardTransactionManager& prepareSvDebit(const int amount,
                                                   const std::vector<uint8_t> date,
                                                   const std::vector<uint8_t> time) = 0;

    /**
     * Schedules the execution of a <b>SV Debit</b> or <b>SV Undebit</b> command to increase the
     * current SV balance or to partially or totally cancels the last SV debit command.
     *
     * <p>It consists in decreasing the current balance of the SV by a certain amount or canceling a
     * previous debit.
     *
     * <p>Note #1: the optional SV additional data are set to zero.
     *
     * <p>Note #2: a communication with the SAM is done here.
     *
     * <p>Note #3: the key used is the reload key.The information fields such as date and time are
     * set to 0. The extraInfo field propagated in Logs are automatically generated with the type of
     * transaction and amount.
     *
     * <p>Note #4: operations that would result in a negative balance are forbidden (SV Exception
     * raised).
     *
     * <p>Note #5: the key used is the debit key
     *
     * @param amount The amount to be subtracted or added, positive integer in the range 0..32767
     *        when subtracted and 0..32768 when added.
     * @return The current instance.
     * @throw IllegalArgumentException If one of the provided argument is out of range.
     * @since 1.0.0
     */
    virtual CardTransactionManager& prepareSvDebit(const int amount) = 0;

    /**
     * Schedules the execution of <b>Read Records</b> commands to read all SV logs.
     *
     * <p>Note: this method requires that the selected application is of type Store Value (file
     * structure 20h).
     *
     * <p>The SV transaction logs are contained in two files with fixed identifiers:
     *
     * <ul>
     *   <li>The file whose SFI is 14h contains 1 record containing the unique reload log.
     *   <li>The file whose SFI is 15h contains 3 records containing the last three debit logs.
     * </ul>
     *
     * <p>At the end of this reading operation, the data will be accessible in CalypsoCard in raw
     * format via the standard commands for accessing read files or in the form of dedicated objects
     * (see calypsonet::terminal::calypso::card::CalypsoCard#getSvLoadLogRecord() and
     * calypsonet::terminal::calypso::card::CalypsoCard::getSvDebitLogAllRecords())
     *
     * <p>At the end of this reading operation, the data will be accessible in CalypsoCard in
     * raw format via the standard commands for accessing read files or in the form of dedicated
     * objects (see CalypsoCard::getSvLoadLogRecord() and CalypsoCard::getSvDebitLogAllRecords()).
     *
     * <p>See the methods CalypsoCard#getSvBalance(), CalypsoCard#getSvLoadLogRecord(),
     * CalypsoCard#getSvDebitLogLastRecord(), CalypsoCard#getSvDebitLogAllRecords().
     *
     * @return The current instance.
     * @throw UnsupportedOperationException If the application is not of type Stored Value.
     * @since 1.0.0
     */
    virtual CardTransactionManager& prepareSvReadAllLogs() = 0;

    /**
     * Schedules the execution of a <b>Invalidate</b> command.
     *
     * <p>This command is usually executed within a secure session with the DEBIT key (depends on the
     * access rights given to this command in the file structure of the card).
     *
     * @throw IllegalStateException If the card is already invalidated.
     * @return The current instance.
     * @since 1.0.0
     */
    virtual CardTransactionManager& prepareInvalidate() = 0;

    /**
     * Schedules the execution of a <b>Rehabilitate</b> command.
     *
     * <p>This command is usually executed within a secure session with the PERSONALIZATION key
     * (depends on the access rights given to this command in the file structure of the card).
     *
     * @return The current instance.
     * @throw IllegalStateException If the card is not invalidated.
     * @since 1.0.0
     */
    virtual CardTransactionManager& prepareRehabilitate() = 0;

    /**
     * Requests the closing of the card channel.
     *
     * <p>If this command is called before a "process" command (except for processOpening) then the
     * last transmission to the card will be associated with the indication CLOSE_AFTER in order to
     * close the card channel.
     *
     * <p>Note: this command must imperatively be called at the end of any transaction, whether it
     * ended normally or not.
     *
     * <p>In case the transaction was interrupted (exception), an additional invocation of
     * processCardCommands must be made to effectively close the channel.
     *
     * @return The current instance.
     * @since 1.0.0
     */
    virtual CardTransactionManager& prepareReleaseCardChannel() = 0;

    /**
     * Process all previously prepared card commands outside or inside a Secure Session.
     *
     * <ul>
     *   <li>All APDUs resulting from prepared commands are grouped and sent to the card.
     *   <li>The calypsonet::terminal::calypso::card::CalypsoCard object is updated with the result
     *       of the executed commands.
     *   <li>If a secure session is opened, except in the case where reloading or debit SV
     *       operations have been prepared, the invocation of this method does not generate
     *       communication with the SAM. The data necessary for the calculation of the terminal
     *       signature are kept to be sent to the SAM at the time of the invocation of
     *       processClosing().<br>
     *       The card channel is kept open.
     *   <li>If no secure session is opened, the card channel is closed depending on whether or not
     *       prepareReleaseCardChannel has been called.
     *   <li>The card session buffer overflows are managed in the same way as in processOpening().
     *       For example, when the multiple session mode is enabled, the commands are separated in
     *       as many sessions as necessary to respect the capacity of the card buffer.
     * </ul>
     *
     * @return The current instance.
     * @throw CardTransactionException If a functional error occurs (including card and SAM IO
     *        errors)
     * @since 1.0.0
     */
    virtual CardTransactionManager& processCardCommands() = 0;

    /**
     * Performs a PIN verification, in order to authenticate the cardholder and/or unlock access to
     * certain card files.
     *
     * <p>This command can be performed both in and out of a secure session. The PIN code can be
     * transmitted in plain text or encrypted according to the parameter set in CardSecuritySetting
     * (by default the transmission is encrypted).
     *
     * <p>If the execution is done out of session but an encrypted transmission is requested, then
     * CardTransactionManager must be constructed with CardSecuritySetting
     *
     * <p>If CardTransactionManager is constructed without CardSecuritySetting the
     * transmission in done in plain.
     *
     * <p>The card channel is closed if prepareReleaseCardChannel is called before this command.
     *
     * @param pin The PIN code value (4-byte long byte array).
     * @return The current instance.
     * @throw UnsupportedOperationException If the PIN feature is not available for this card
     * @throw IllegalArgumentException If the provided argument is out of range.
     * @throw IllegalStateException If commands have been prepared before invoking this process
     *        method.
     * @throw CardTransactionException If a functional error occurs (including card and SAM IO
     *        errors)
     * @since 1.0.0
     */
    virtual CardTransactionManager& processVerifyPin(const std::vector<uint8_t>& pin) = 0;

    /**
     * Invokes processVerifyPin() with a string converted into an array of bytes as argument.
     *
     * <p>The provided String is converted into an array of bytes and processed with {@link
     * processVerifyPin().
     *
     * <p>E.g. "1234" will be transmitted as { 0x31,0x32,0x33,0x34 }
     *
     * @param pin An ASCII string (4-character long).
     * @return The current instance.
     * @throw UnsupportedOperationException If the PIN feature is not available for this card
     * @throw IllegalArgumentException If the provided argument is out of range.
     * @throw IllegalStateException If commands have been prepared before invoking this process
     *        method.
     * @throw CardTransactionException If a functional error occurs (including card and SAM IO
     *        errors)
     * @since 1.0.0
     */
    virtual CardTransactionManager& processVerifyPin(const std::string& pin) = 0;

    /**
     * Replaces the current PIN with the new value provided.
     *
     * <p>This command can be performed only out of a secure session. The new PIN code can be
     * transmitted in plain text or encrypted according to the parameter set in CardSecuritySetting
     * (by default the transmission is encrypted).
     *
     * <p>When the PIN is transmitted plain, this command must be preceded by a successful Verify
     * PIN command (see processVerifyPin(byte[])).
     *
     * @param newPin The new PIN code value (4-byte long byte array).
     * @return The current instance.
     * @throws UnsupportedOperationException If the PIN feature is not available for this card.
     * @throws IllegalArgumentException If the provided argument is out of range.
     * @throws IllegalStateException If the command is executed while a secure session is open.
     * @throws CardTransactionException If a functional error occurs (including card and SAM IO
     *         errors).
     * @since 1.0.0
     */
    virtual CardTransactionManager& processChangePin(const std::vector<uint8_t>& newPin) = 0;

    /**
     * Replaces one of the current card keys with another key present in the SAM.
     *
     * <p>This command can be performed only out of a secure session.
     *
     * <p>The change key process transfers the key from the SAM to the card. The new key is
     * diversified by the SAM from a primary key and encrypted using the indicated issuer key to
     * secure the transfer to the card. All provided KIFs and KVCs must be present in the SAM.
     *
     * @param keyIndex The index of the key to be replaced (1 for the issuer key, 2 for the load
     *        key, 3 for the debit key).
     * @param newKif The KIF of the new key.
     * @param newKvc The KVC of the new key.
     * @param issuerKif The KIF of the current card's issuer key.
     * @param issuerKvc The KVC of the current card's issuer key.
     * @return The current instance.
     * @throws UnsupportedOperationException If the Change Key command is not available for this
     *         card.
     * @throws IllegalArgumentException If the provided key index is out of range.
     * @throws IllegalStateException If the command is executed while a secure session is open.
     * @since 1.1.0
     */
    virtual CardTransactionManager& processChangeKey(const int keyIndex,
                                                     const uint8_t newKif,
                                                     const uint8_t newKvc,
                                                     const uint8_t issuerKif,
                                                     const uint8_t issuerKvc) = 0;

    /**
     * Opens a Calypso Secure Session and then executes all previously prepared commands.
     *
     * <p>It is the starting point of the sequence:
     *
     * <ul>
     *   <li>{@code processOpening(WriteAccessLevel)}
     *   <li>[{@link #processCardCommands()}]
     *   <li>[...]
     *   <li>[{@link #processCardCommands()}]
     *   <li>{@link #processClosing()}
     * </ul>
     *
     * <p>Each of the steps in this sequence may or may not be preceded by the preparation of one or
     * more commands and ends with an update of the calypsonet::terminal::calypso::card::CalypsoCard
     * object provided when calypsonet::terminal::calypso::transaction::CardTransactionManager was
     * created.
     *
     * <p>As a prerequisite for invoking this method, since the Calypso Secure Session involves the
     * use of a SAM, the CardTransactionManager must have been built in secure mode, i.e. the
     * constructor used must be the one expecting a reference to a valid
     * calypsonet::terminal::calypso::card::CardSecuritySetting object, otherwise a
     * keyple::core::util::cpp::exception::IllegalStateException is raised.
     *
     * <p>The secure session is opened with the calypsonet::terminal::calypso::WriteAccessLevel
     * passed as an argument depending on whether it is a personalization, reload or debit
     * transaction profile.
     *
     * <p>The possible overflow of the internal session buffer of the card is managed in two ways
     * depending on the setting chosen in
     * calypsonet::terminal::calypso::transaction::CardSecuritySetting.
     *
     * <ul>
     *   <li>If the session was opened with the default atomic mode and the previously prepared
     *       commands will cause the buffer to be exceeded, then an AtomicTransactionException
     *       is raised and no transmission to the card is made. <br>
     *   <li>If the session was opened with the multiple session mode and the buffer is to be
     *       exceeded then a split into several secure sessions is performed automatically. However,
     *       regardless of the number of intermediate sessions performed, a secure session is opened
     *       at the end of the execution of this method.
     * </ul>
     *
     * <p>Be aware that in the "MULTIPLE" case we lose the benefit of the atomicity of the secure
     * session.
     *
     * <p><b>Card and SAM exchanges in detail</b>
     *
     * <p>When executing this method, communications with the card and the SAM are (in that order) :
     *
     * <ul>
     *   <li>Sending the card diversifier (Calypso card serial number) to the SAM and receiving the
     *       terminal challenge
     *   <li>Grouped sending to the card of
     *       <ul>
     *         <li>the open secure session command including the challenge terminal.
     *         <li>all previously prepared commands
     *       </ul>
     *   <li>Receiving grouped responses and updating
     *       calypsonet::terminal::calypso::card::CalypsoCard with the collected data.
     * </ul>
     *
     * For optimization purposes, if the first command prepared is the reading of a single record of
     * a card file then this one is replaced by a setting of the session opening command allowing
     * the retrieval of this data in response to this command.
     *
     * <p>Please note that the CAAD mechanism may require a file to be read before being modified.
     * For this mechanism to work properly, this reading must not be placed in the first position of
     * the prepared commands in order to be correctly taken into account by the SAM.
     *
     * <p><b>Other operations carried out</b>
     *
     * <ul>
     *   <li>The card KIF, KVC and card challenge received in response to the open secure session
     *       command are kept for a later initialization of the session's digest (see
     *       processClosing()).
     *   <li>All data received in response to the open secure session command and the responses to
     *       the prepared commands are also stored for later calculation of the digest.
     *   <li>If a list of authorized KVCs has been defined in
     *       calypsonet::terminal::calypso::transaction::CardSecuritySetting and the KVC
     *       of the card does not belong to this list then an UnauthorizedKeyException is
     *       thrown.
     * </ul>
     *
     * <p>All unexpected results (communication errors, data or security errors, etc. are notified
     * to the calling application through dedicated exceptions.
     *
     * <p><i>Note: to understand in detail how the secure session works please refer to the card
     * specification documents.</i>
     *
     * @param writeAccessLevel An calypsonet::terminal::calypso::WriteAccessLevel enum entry.
     * @return The current instance.
     * @throw IllegalArgumentException If the provided argument is null.
     * @throw IllegalStateException If no
     *        calypsonet::terminal::calypso::transaction::CardSecuritySetting is available
     * @throw CardTransactionException If a functional error occurs (including card and SAM IO
     *        errors)
     * @since 1.0.0
     */
    virtual CardTransactionManager& processOpening(const WriteAccessLevel writeAccessLevel) = 0;

    /**
     * Terminates the Secure Session sequence started with processOpening().
     *
     * <p><b>Nominal case</b>
     *
     * <p>The previously prepared commands are integrated into the calculation of the session digest
     * by the SAM before execution by the card by anticipating their responses.
     *
     * <p>Thus, the session closing command containing the terminal signature is integrated into the
     * same APDU group sent to the card via a final card request.
     *
     * <p>Upon reception of the response from the card, the signature of the card is verified with
     * the SAM.
     *
     * <p>If the method terminates normally, it means that the secure session closing and all
     * related security checks have been successful; conversely, if one of these operations fails,
     * an exception is raised.
     *
     * <p><b>Stored Value</b>
     *
     * <p>If the SV counter was debited or reloaded during the session, an additional verification
     * specific to the SV is performed by the SAM.
     *
     * <p><b>Ratification</b>
     *
     * <p>A ratification command is added after the close secure session command when the
     * communication is done in a contactless mode.
     *
     * <p>The logical channel is closed or left open depending on whether the
     * #prepareReleaseCardChannel() method has been called before or not.
     *
     * <p><b>Card and SAM exchanges in detail</b>
     *
     * <ul>
     *   <li>All the data exchanged with the card so far, to which are added the last prepared
     *       orders and their anticipated answers, are sent to the SAM for the calculation of the
     *       session digest. The terminal signature calculation request is also integrated in the
     *       same group of SAM Apdu.
     *   <li>All previously prepared commands are sent to the card along with the session closing
     *       command and possibly the ratification command within a single card request.
     *   <li>The responses received from the card are integrated into CalypsoCard. <br>
     *       Note: the reception of the answers of this final card request from the card is tolerant
     *       to the non-reception of the answer to the ratification order.
     *   <li>The data received from the card in response to the logout (card session signature and
     *       possibly SV signature) are sent to the SAM for verification.
     * </ul>
     *
     * @return The current instance.
     * @throws IllegalStateException If no session is open.
     * @throws CardTransactionException If a functional error occurs (including card and SAM IO
     *         errors).
     * @since 1.0.0
     */
    virtual CardTransactionManager& processClosing() = 0;

    /**
     * Aborts a Secure Session.
     *
     * <p>Send the appropriate command to the card
     *
     * <p>Clean up internal data and status.
     *
     * @return The current instance.
     * @throw IllegalStateException If no session is open.
     * @throw CardTransactionException If a functional error occurs (including card and SAM IO
     *     errors)
     * @since 1.0.0
     */
    virtual CardTransactionManager& processCancel() = 0;
};

}
}
}
}
