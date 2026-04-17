# 📄 Protocol

![C++23](https://img.shields.io/badge/C%2B%2B-23-blue)
![xmake](https://img.shields.io/badge/xmake-2.8%2B-3C8CFF)
![许可证](https://img.shields.io/badge/License-MPL--2.0-brightgreen)

[📄 English README](README.md)

一个基于 C++23 的 Minecraft 基岩版网络协议库。

Protocol 提供基岩版数据包模型、数据包 ID 映射，以及二进制读写工具，
可用于构建高性能的服务端、代理、抓包分析器与协议测试工具。

## 💬 社区

加入我们的社区：
- Discord：`https://discord.gg/gUQ3Pnssrx`
- QQ 群：`1063182638`

## ✨ 特性

- 以 C++23 为核心实现
- 通过 `IPacket` 与数据包工厂统一管理 Bedrock 数据包
- 提供二进制序列化/反序列化基础能力：
  - `BinaryStream`
  - `ReadOnlyBinaryStream`
- 使用 xmake 进行构建
- 使用 MPL-2.0 许可证

## 🧩 环境要求

- xmake 2.8 或更高版本
- 支持 C++23 的编译器

## 🛠️ 构建

### 📄 配置

```bash
xmake f -m release
```

> 默认构建产物为 **动态库**。如果需要静态库可使用 `xmake f --shared=false`。

### 📄 编译

```bash
xmake
```

### 📄 Linux（LLVM/Clang）

```bash
xmake f -p linux -a x86_64 --toolchain=clang -m release
xmake
```

### 📄 Windows（MSVC）

```bash
xmake f -p windows -a x64 --toolchain=msvc -m release
xmake
```

### 📄 安装

```bash
xmake install -o install
```

## 🔌 在 xmake 项目中使用

如果你的项目同样使用 xmake：

```lua
add_repositories("local-repo /path/to/Protocol")
add_requires("Protocol")
```

## 📦 发布到 xmake-repo

如果你希望其他 xmake 项目通过 `add_requires` 直接引入本库，
可以在自建 xmake-repo 中添加一个包脚本。

仓库内已提供可直接参考的脚本：

- `xmake-repo/packages/p/protocol/xmake.lua`

> 说明：该包脚本会优先使用 `xmake.lua`，若源码中不存在则自动回退到 CMake 安装流程。

最小流程：

```bash
# 1) 添加存放包脚本的仓库
xmake repo --add protocol-repo https://github.com/<you>/xmake-repo.git

# 2) 从该仓库安装
xrepo install protocol dev
```

在使用方项目中：

```lua
add_repositories("protocol-repo https://github.com/<you>/xmake-repo.git")
add_requires("protocol dev")

target("app")
    set_kind("binary")
    add_files("src/*.cpp")
    add_packages("protocol")
```

## 🚀 快速示例

```cpp
#include <sculk/protocol/MinecraftPackets.hpp>
#include <sculk/protocol/packet/IPacket.hpp>
#include <sculk/protocol/utility/BinaryStream.hpp>
#include <sculk/protocol/utility/ReadOnlyBinaryStream.hpp>

#include <cstddef>
#include <vector>

int main() {
    using namespace sculk::protocol;

    // 假设这里是来自网络层的原始数据。
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

## 🗂️ 目录结构

- `include/sculk/protocol`：公开头文件
- `src/sculk/protocol`：实现代码
- `xmake.lua`：xmake 构建脚本
- `scripts`：开发辅助脚本

## 🧬 ABI 命名空间

公开 API 通过内联 ABI 命名空间进行版本化，
例如 `sculk::protocol::abi_v944`。

## 🤝 欢迎贡献

欢迎任何形式的贡献。

- 你可以通过 Issue 提交 Bug、功能建议和协议讨论。
- 你可以通过 Pull Request 提交修复、优化与新数据包支持。
- 建议保持改动聚焦，并在描述中清晰说明行为变化。

## 🙏 鸣谢

本开源项目的诞生源于闭源付费项目 XXX 的支持。

赞助链接：https://afdian.tv/a/GlacieTeam

## ⚖️ 许可证

本项目采用 Mozilla Public License 2.0（MPL-2.0）开源。
完整许可证文本见 [LICENSE](LICENSE)。

MPL-2.0 核心要求（摘要）：

- 若你修改了受 MPL 覆盖的文件并进行分发，这些被修改的文件需继续以 MPL-2.0 许可发布。
- 需保留受覆盖源码文件中的版权声明与许可证声明。
- 若你分发二进制或可执行形式，需要提供对应的受覆盖源码获取方式。
- 你可以在更大的工程中与其他许可代码组合使用，但受覆盖文件仍需满足 MPL 义务。

以上仅为便于理解的摘要，法律效力以 [LICENSE](LICENSE) 正文为准。

### 版权所有 © 2026 SculkCatalystMC。保留所有权利。
