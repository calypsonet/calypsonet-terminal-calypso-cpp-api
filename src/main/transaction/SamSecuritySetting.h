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

namespace calypsonet {
namespace terminal {
namespace calypso {
namespace transaction {

/**
 * Data to manage the security operations of a Calypso SAM transaction.
 *
 * @since 1.2.0
 */
class SamSecuritySetting final : public CommonSecuritySetting<SamSecuritySetting> {
public:
    /**
     * 
     */
    virtual ~SamSecuritySetting() = default;
};

}
}
}
}
