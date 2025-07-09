cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_COMPILER "C:/mingw_sfml/winlibs-x86_64-posix-seh-gcc-14.2.0-mingw-w64ucrt-12.0.0-r2/mingw64/bin/g++.exe")
project(lifegame)

#set(CMAKE_BUILD_TYPE Debug)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 手动指定SFML路径
set(SFML_INCLUDE_DIR "C:/mingw_sfml/SFML-3.0.0-windows-gcc-14.2.0-mingw-64-bit/SFML-3.0.0/include")
set(SFML_LIB_DIR "C:/mingw_sfml/SFML-3.0.0-windows-gcc-14.2.0-mingw-64-bit/SFML-3.0.0/lib")

set(SFML_STATIC_LIBRARIES ON)  # 启用静态链接

include_directories(${SFML_INCLUDE_DIR})
link_directories(${SFML_LIB_DIR})

# 添加可执行文件
add_executable(${PROJECT_NAME} src/main.cpp)  # 替换为你的源文件

# 静态链接需要定义宏
target_compile_definitions(${PROJECT_NAME} PRIVATE SFML_STATIC)

# 链接静态库
target_link_libraries(${PROJECT_NAME} PRIVATE
    ${SFML_LIB_DIR}/libsfml-graphics-s.a
    ${SFML_LIB_DIR}/libsfml-window-s.a
    ${SFML_LIB_DIR}/libsfml-system-s.a
    ${SFML_LIB_DIR}/libsfml-audio-s.a
    ${SFML_LIB_DIR}/libsfml-network-s.a
    -lopengl32
    -lgdi32
    -lwinmm
    -lfreetype
)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")