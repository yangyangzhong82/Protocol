# 📄 Protocol

![C++23](https://img.shields.io/badge/C%2B%2B-23-blue)
![xmake](https://img.shields.io/badge/xmake-2.8%2B-3C8CFF)
![License](https://img.shields.io/badge/License-MPL--2.0-brightgreen)

[📄 中文文档](README.zh.md)

A C++23 Minecraft Bedrock network protocol library.

Protocol provides Bedrock packet models, packet ID mapping, and binary
read/write utilities for building high-performance servers, proxies,
analyzers, and protocol test suites.

## 💬 Community

Join our community:
- Discord: `https://discord.gg/gUQ3Pnssrx`
- QQ Group: `1063182638`

## ✨ Highlights

- C++23-first implementation
- Bedrock packet abstraction via `IPacket` and packet factories
- Binary serialization/deserialization primitives:
  - `BinaryStream`
  - `ReadOnlyBinaryStream`
- xmake-based build workflow
- MPL-2.0 licensed

## 🧩 Requirements

- xmake 2.8 or newer
- A C++23-capable compiler

## 🛠️ Build

### 📄 Configure

```bash
xmake f -m release
```

> Default build kind is **shared library**. Use `xmake f --shared=false` for static.

### 📄 Compile

```bash
xmake
```

### 📄 Linux (LLVM/Clang)

```bash
xmake f -p linux -a x86_64 --toolchain=clang -m release
xmake
```

### 📄 Windows (MSVC)

```bash
xmake f -p windows -a x64 --toolchain=msvc -m release
xmake
```

### 📄 Install

```bash
xmake install -o install
```

## 🔌 xmake Integration

If your project also uses xmake:

```lua
add_repositories("local-repo /path/to/Protocol")
add_requires("Protocol")
```

## 📦 Publishing to an xmake-repo

If you want other xmake projects to consume this library through `add_requires`,
you can add a package recipe to your custom xmake-repo.

A ready-to-use example recipe is provided at:

- `xmake-repo/packages/p/protocol/xmake.lua`

> Note: the recipe will prefer `xmake.lua`; if absent, it falls back to CMake installation.

Minimal workflow:

```bash
# 1) Add your repository that stores package recipes
xmake repo --add protocol-repo https://github.com/<you>/xmake-repo.git

# 2) Install package from that repo
xrepo install protocol dev
```

In a consumer project:

```lua
add_repositories("protocol-repo https://github.com/<you>/xmake-repo.git")
add_requires("protocol dev")

target("app")
    set_kind("binary")
    add_files("src/*.cpp")
    add_packages("protocol")
```

## 🚀 Quick Start

```cpp
#include <sculk/protocol/MinecraftPackets.hpp>
#include <sculk/protocol/packet/IPacket.hpp>
#include <sculk/protocol/utility/BinaryStream.hpp>
#include <sculk/protocol/utility/ReadOnlyBinaryStream.hpp>

#include <cstddef>
#include <vector>

int main() {
    using namespace sculk::protocol;

    // Example input from network transport.
    std::vector<std::byte> input{};

    ReadOnlyBinaryStream readStream{input};
    const auto header = MinecraftPackets::readPacketHeader(readStream);
    auto packet = MinecraftPackets::createPacket(header);

    if (packet) {
        const auto readResult = packet->readNoHeader(readStream);
        if (!readResult) {
            return 1;
        }

        std::vector<std::byte> output;
        BinaryStream writeStream{output};
        packet->writeWithHeader(writeStream);
    }

    return 0;
}
```

## 🗂️ Project Layout

- `include/sculk/protocol`: public headers
- `src/sculk/protocol`: implementation
- `xmake.lua`: xmake build script
- `scripts`: development helper scripts

## 🧬 ABI Namespace

Public APIs are versioned with an inline ABI namespace,
for example `sculk::protocol::abi_v944`.

## 🤝 Contributing

Contributions are welcome.

- Open an Issue for bug reports, feature requests, or protocol discussions.
- Open a Pull Request for fixes, improvements, and new packet support.
- Keep changes focused and provide clear descriptions of behavior changes.

## 🙏 Acknowledgments

This open source project was born with support from the closed-source paid project XXX.

Support link: https://afdian.tv/a/GlacieTeam

## ⚖️ License

This project is licensed under the Mozilla Public License 2.0 (MPL-2.0).
See the full text in [LICENSE](LICENSE).

Core MPL-2.0 requirements (summary):

- If you modify MPL-covered files and distribute them, those modified files must remain under MPL-2.0.
- You must keep existing copyright and license notices in covered source files.
- If you distribute binaries/executables, you must make the corresponding covered source code available.
- You may combine this project with code under other licenses in a larger work, as long as MPL obligations for covered files are respected.

This summary is for convenience only. The [LICENSE](LICENSE) file is the authoritative legal text.

### Copyright © 2026 SculkCatalystMC. All rights reserved.
