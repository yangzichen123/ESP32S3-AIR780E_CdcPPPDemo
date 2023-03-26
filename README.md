# Linux下通过串口获取模块信息

[![github](https://img.shields.io/badge/Version-V1.0.0-brightgreen.svg)](https://github.com/snowdreams1006)  [![github](https://img.shields.io/badge/Build-passing-brightgreen.svg)](https://github.com/snowdreams1006)  [![github](https://img.shields.io/badge/-Ubuntu-black?logo=Ubuntu)](https://github.com/snowdreams1006)  [![github](https://img.shields.io/badge/Tools-GCC&Cmake-critical.svg)](https://github.com/snowdreams1006)  [![github](https://img.shields.io/badge/Auther-Yangzc-orange.svg)](https://github.com/snowdreams1006) 

本工程使用C语言编写，由Cmake构建，GCC编译，可以从模块挂载的AT串口读取模块的各种数据，支持自行添加AT指令，并且会保存读出的数据到本地。串口波特率默认为115200，数据位：8，停止位：0，奇偶校验位：0。](#技术支持与反馈)

**目录**

- [如何使用](#如何使用)

- [故障和排查](#故障和排查)

- [技术支持和反馈](#技术支持和反馈)

## 如何使用

* 首先保证你的编译环境安装了Cmake和GCC。

* 从Git拉取工程到本地。

* 进入到工程目录下编译，编译指令：``./build.sh -b``，清除指令``./build.sh -c``。

* 确认生成如下目录结构：
  
      ├── atcommand.txt                        #需要读取的AT指令文件
      ├── bin
      │   └── UartAtMoudleGetInfo              #可执行文件
      ├── build
      │   ├── CMakeCache.txt
      │   ├── CMakeFiles
      │   ├── cmake_install.cmake
      │   ├── compile_commands.json
      │   └── Makefile
      ├── build.sh                             #编译脚本
      ├── CMakeLists.txt                       #CmakeList文件
      ├── include                              #头文件夹
      │   └── main.h                
      ├── readme.md
      └── src                                  #C文件夹
          └── main.c

* 进入bin文件夹，同时将atcommand.txt文件放入bin文件夹，使用指令``./UartAtMoudleGetInfo /dev/ttyS1 atcommand.txt``运行程序，其中``/dev/ttyS1``为模块挂载的AT串口号，按照自己实际的环境设置，``atcommand.txt``为需要加载的AT指令文件。注意：程序查询的是默认同一路径下的文件，如果需要查询其他路径请输入绝对地址。默认输出Log的地址与可执行文件同级。

## 故障和排查

* 编译失败
  
  * 请确保你安装了GCC和Cmake，如果需要使用其他编译器，需要修改CmakeLists文件指定编译器名称。
  * 如果提示文件可执行权限问题，请使用``chmod 777 build.sh``将脚本文件设置为可执行文件，这一操作需要在sudo下操作。

* 打开串口被拒绝
  
  * 请在sudo权限下运行生成的文件。
  
  * 确保没有其他程序占用串口。

## 技术支持和反馈

请使用以下方式：

- 有关技术支持，请联系[yangzc@lierda.com]()。

- 对于功能要求和改进，请直接提交issue。

会尽快给你一个答复。


