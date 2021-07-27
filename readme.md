# 使用 GNU Toolchain 进行嵌入式开发  

Keil、IAR 等著名的集成开发环境，为嵌入式开发带来许多便利，但是也掩盖了嵌入式软件开发中一些细节：编译、链接、装载。这三个环节在集成开发环境中，是简单而且理所当然的功能。为了探究 ARM 嵌入式 MCU 的底层系统结构，我使用 GNU Toolchain 来逐一实现 IDE 中一键配置的编译、链接、装载过程。如果你也有兴趣的话，也来和我一起学习吧。

## 使用到的工具  

**GNU Toolchian**: `arm-none-eabi-gcc (GNU Arm Embedded Toolchain 10-2020-q4-major) 10.2.1 20201103`  
**开发板**: `qemu-system-arm` 上的 `lm3s6965evb` 虚拟主板，内核为 `Coretx-M3`。  

## 推荐阅读书籍与参考项目  

**《ARM Assembly Language: Fundamentals and Techniques》**: 详细完整地讲解了 ARM 汇编语言，与编程相关地硬件模型也有完善地讲解。  
**《程序员地自我修养：链接、编译与库》**: 讲解了 C 语言到到可执行文件地过程，是本项目地关键参考资料。  
**《深入理解 BootLoader》**：对于 GNU Toolchain 的使用介绍上值得一看，还介绍了 IAP 在线升级的原理。  
**[Bare-metal C programming on ARM](https://github.com/umanovskis/baremetal-arm)**：这是一个与本项目类似的嵌入式教程，作者从 Qemu 地使用，到 U-boot 引导 Linux 做了十分详细地教程，对我的帮助也很大。  