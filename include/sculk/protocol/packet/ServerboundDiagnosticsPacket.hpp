// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "sculk/protocol/packet/IPacket.hpp"
#include <vector>

namespace sculk::protocol::inline abi_v944 {

class ServerboundDiagnosticsPacket : public IPacket {
public:
    struct MemoryCategoryCounter {
        std::uint8_t  mType{};
        std::uint64_t mCurrentBytes{};

        void write(BinaryStream& stream) const;

        [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream);
    };

public:
    float                              mAvgFps{};
    float                              mAvgServerSimTickTimeMS{};
    float                              mAvgClientSimTickTimeMS{};
    float                              mAvgBeginFrameTimeMS{};
    float                              mAvgInputTimeMS{};
    float                              mAvgRenderTimeMS{};
    float                              mAvgEndFrameTimeMS{};
    float                              mAvgRemainderTimePercent{};
    float                              mAvgUnaccountedTimePercent{};
    std::vector<MemoryCategoryCounter> mMemoryCategoryValues{};

public:
    [[nodiscard]] MinecraftPacketIds getId() const noexcept override;

    [[nodiscard]] std::string_view getName() const noexcept override;

    void write(BinaryStream& stream) const override;

    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream) override;
};

} // namespace sculk::protocol::inline abi_v944
