cmake_minimum_required(VERSION 3.12)

# 指定项目名称和C++标准
project(lifegame)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 指定编译器路径（使用SFML官网提供的对应版本的mingw编译器）
set(CMAKE_CXX_COMPILER "C:/mingw_sfml/winlibs-x86_64-posix-seh-gcc-14.2.0-mingw-w64ucrt-12.0.0-r2/mingw64/bin/g++.exe")

# 手动指定SFML路径
set(SFML_ROOT "C:/mingw_sfml/SFML-3.0.0-windows-gcc-14.2.0-mingw-64-bit/SFML-3.0.0")
set(SFML_INCLUDE_DIR "${SFML_ROOT}/include")
set(SFML_LIB_DIR "${SFML_ROOT}/lib")

# 启用SFML静态链接
set(SFML_STATIC_LIBRARIES ON)

# 包含SFML头文件和库目录
include_directories(${SFML_INCLUDE_DIR})
link_directories(${SFML_LIB_DIR})

# 添加可执行文件
add_executable(${PROJECT_NAME} src/main.cpp)

# 静态链接时需定义SFML_STATIC宏
target_compile_definitions(${PROJECT_NAME} PRIVATE SFML_STATIC)

# 集中管理SFML静态库依赖
set(SFML_LIBS
    ${SFML_LIB_DIR}/libsfml-graphics-s.a
    ${SFML_LIB_DIR}/libsfml-window-s.a
    ${SFML_LIB_DIR}/libsfml-system-s.a
    ${SFML_LIB_DIR}/libsfml-audio-s.a
    ${SFML_LIB_DIR}/libsfml-network-s.a
)

# 链接SFML静态库及Windows系统依赖库
# -lopengl32 -lgdi32 -lwinmm -lfreetype 是SFML静态库所需的系统库
# 如需音频支持可加 -lopenal32 -lflac -lvorbisenc -lvorbisfile -lvorbis -logg
# 如遇缺少依赖可根据报错补充

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${SFML_LIBS}
    -lopengl32
    -lgdi32
    -lwinmm
    -lfreetype
)

# 静态链接C++标准库和GCC运行库，避免分发时缺少DLL
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")

# 可选：设置Debug/Release构建类型
# set(CMAKE_BUILD_TYPE Debug)

# 说明：
# 1. 若仍有缺失DLL报错，请用Dependency Walker等工具检查依赖，补充缺失的库。
# 2. 若SFML版本与MinGW不完全匹配，建议自行编译SFML源码。
# 3. 如需添加多个源文件，可在add_executable中补充。