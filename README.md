### 环境配置

1. 按[SFML](https://www.sfml-dev.org/download/sfml/3.0.0/)官方文档配置环境
2. 将.vscode内的文件和CMakeLists.txt中的SFML3.0对应的C++标准库和SFML 3.0 库路径修改为自己的文件路径

运行ttf_to_bin.py脚本可以将arial.ttf转换为数组文件，让SFML从内存中调用

### 编译指令

```
cmake -B build
cmake --build build
```

将字体文件arial.ttf放在build文件夹下

### 启用调试 (F5)

```
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```
