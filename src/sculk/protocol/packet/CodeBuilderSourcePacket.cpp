// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/packet/CodeBuilderSourcePacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds CodeBuilderSourcePacket::getId() const noexcept { return MinecraftPacketIds::CodeBuilderSource; }

std::string_view CodeBuilderSourcePacket::getName() const noexcept { return "CodeBuilderSourcePacket"; }

void CodeBuilderSourcePacket::write(BinaryStream& stream) const {
    stream.writeByte(mOperation);
    stream.writeByte(mCategory);
    stream.writeByte(mCodeStatus);
}

Result<> CodeBuilderSourcePacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readByte(mOperation); !status) return status;
    if (auto status = stream.readByte(mCategory); !status) return status;
    return stream.readByte(mCodeStatus);
}

} // namespace sculk::protocol::inline abi_v944
