# 编译安装
# `${CMAKE_C_COMPILER}` 仅用于编译 `.sysu.c`
# 非 SYsU 语言的代码都将直接/间接使用 `${CMAKE_CXX_COMPILER}` 编译（后缀为 `.cc`）
CMAKE="/home/tangzh/applications/cmake-3.26.2-linux-x86_64/bin/cmake"
CMAKE=cmake
rm -rf $HOME/sysu
${CMAKE} --version
${CMAKE} -G Ninja \
    -DCMAKE_C_COMPILER=clang \
    -DCMAKE_CXX_COMPILER=clang++ \
    -DCMAKE_INSTALL_PREFIX=$HOME/sysu \
    -DCMAKE_MODULE_PATH=$(llvm-config --cmakedir) \
    -DCPACK_SOURCE_IGNORE_FILES=".git/;tester/third_party/" \
    -B $HOME/sysu/build
${CMAKE} --build $HOME/sysu/build
${CMAKE} --build $HOME/sysu/build -t install

mv $HOME/sysu/build/compile_commands.json ./.vscode/
# set -x
# for i in {1..3}; do
#   # 测试
# export PATH=$HOME/sysu/bin:$PATH \
#   CPATH=$HOME/sysu/include:$CPATH \
#   LIBRARY_PATH=$HOME/sysu/lib:$LIBRARY_PATH \
#   LD_LIBRARY_PATH=$HOME/sysu/lib:$LD_LIBRARY_PATH &&
#   sysu-compiler --unittest=lexer-${i} "**/*.sysu.c"
# done

# 提交打包
# CPACK_SOURCE_IGNORE_FILES=".git/;tester/third_party/" cmake --build $HOME/sysu/build -t package_source
# 解压测试
# python3 -m tarfile -e SYsU-lang-*-Source.tar.gz

#Parser 测试
cat tester/function_test2020/00_main.sysu.c | ~/sysu/bin/sysu-lexer | ~/sysu/bin/sysu-parser
