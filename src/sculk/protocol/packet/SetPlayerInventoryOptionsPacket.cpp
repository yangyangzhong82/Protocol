// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/packet/SetPlayerInventoryOptionsPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds SetPlayerInventoryOptionsPacket::getId() const noexcept {
    return MinecraftPacketIds::SetPlayerInventoryOptions;
}

std::string_view SetPlayerInventoryOptionsPacket::getName() const noexcept { return "SetPlayerInventoryOptionsPacket"; }

void SetPlayerInventoryOptionsPacket::write(BinaryStream& stream) const {
    stream.writeVarInt(mLeftInventoryTab);
    stream.writeVarInt(mRightInventoryTab);
    stream.writeBool(mFiltering);
    stream.writeVarInt(mLayoutInventory);
    stream.writeVarInt(mLayoutCraft);
}

Result<> SetPlayerInventoryOptionsPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readVarInt(mLeftInventoryTab); !status) return status;
    if (auto status = stream.readVarInt(mRightInventoryTab); !status) return status;
    if (auto status = stream.readBool(mFiltering); !status) return status;
    if (auto status = stream.readVarInt(mLayoutInventory); !status) return status;
    return stream.readVarInt(mLayoutCraft);
}

} // namespace sculk::protocol::inline abi_v944
