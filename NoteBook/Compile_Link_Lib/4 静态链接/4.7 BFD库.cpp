// !! 4.7　BFD 库

由于现代的硬件和软件平台种类非常繁多, 它们之间千差万别, 比如, 硬件中 CPU 有 8 位的、16 位的, 一直到 64 位的; 字节序有大端的也有小端的; 有些有 MMU 有些没有; 有些对
访问内存地址对齐有着特殊要求, 比如 MIPS, 而有些则没有, 比如 x86。软件平台有些支持动态链接, 而有些不支持; 有些支持调试, 有些又不支持。这些五花八门的软硬件平台基础导致了
每个平台都有它独特的目标文件格式, 即使同一个格式比如 ELF 在不同的软硬件平台都有着不同的变种。

'种种差异导致编译器和链接器很难处理不同平台之间的目标文件', 特别是对于像 GCC 和 binutils 这种跨平台的工具来说, 最好有一种统一的接口来处理这些不同格式之间的差异。

BFD 库 (Binary File Descriptor library) 就是这样的一个 GNU 项目, 它的目标就是希望通过一种统一的接口来处理不同的目标文件格式。

BFD 这个项目本身是 binutils 项目的一个子项目。

现在 GCC (更具体地讲是 GNU 汇编器 GAS, GNU Assembler)、链接器 ld、调试器 GDB 及 binutils 的其他工具都通过 BFD 库来处理目标文件, 而不是直接操作目标文件。



