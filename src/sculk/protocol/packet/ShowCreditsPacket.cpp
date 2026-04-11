// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/packet/ShowCreditsPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds ShowCreditsPacket::getId() const noexcept { return MinecraftPacketIds::ShowCredits; }

std::string_view ShowCreditsPacket::getName() const noexcept { return "ShowCreditsPacket"; }

void ShowCreditsPacket::write(BinaryStream& stream) const {
    stream.writeUnsignedVarInt64(mPlayerRuntimeId);
    stream.writeVarInt(mCreditsState);
}

Result<> ShowCreditsPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readUnsignedVarInt64(mPlayerRuntimeId); !status) return status;
    return stream.readVarInt(mCreditsState);
}

} // namespace sculk::protocol::inline abi_v944
