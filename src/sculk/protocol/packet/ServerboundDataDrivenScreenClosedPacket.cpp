// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/packet/ServerboundDataDrivenScreenClosedPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds ServerboundDataDrivenScreenClosedPacket::getId() const noexcept {
    return MinecraftPacketIds::ServerboundDataDrivenScreenClosed;
}

std::string_view ServerboundDataDrivenScreenClosedPacket::getName() const noexcept {
    return "ServerboundDataDrivenScreenClosedPacket";
}

void ServerboundDataDrivenScreenClosedPacket::write(BinaryStream& stream) const {
    stream.writeOptional(mFormId, &BinaryStream::writeUnsignedInt);
    stream.writeEnum(mCloseReason, &BinaryStream::writeByte);
}

Result<> ServerboundDataDrivenScreenClosedPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readOptional(mFormId, &ReadOnlyBinaryStream::readUnsignedInt); !status) return status;
    if (auto status = stream.readEnum(mCloseReason, &ReadOnlyBinaryStream::readByte); !status) return status;
    return {};
}

} // namespace sculk::protocol::inline abi_v944
