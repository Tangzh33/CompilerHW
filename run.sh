# 编译安装
# `${CMAKE_C_COMPILER}` 仅用于编译 `.sysu.c`
# 非 SYsU 语言的代码都将直接/间接使用 `${CMAKE_CXX_COMPILER}` 编译（后缀为 `.cc`）
rm -rf $HOME/sysu
cmake -G Ninja \
  -DCMAKE_C_COMPILER=clang \
  -DCMAKE_CXX_COMPILER=clang++ \
  -DCMAKE_INSTALL_PREFIX=$HOME/sysu \
  -DCMAKE_MODULE_PATH=$(llvm-config --cmakedir) \
  -DCPACK_SOURCE_IGNORE_FILES=".git/;tester/third_party/" \
  -B $HOME/sysu/build
cmake --build $HOME/sysu/build
cmake --build $HOME/sysu/build -t install

set -x
for i in {1..3}; do
  # 测试
export PATH=$HOME/sysu/bin:$PATH \
  CPATH=$HOME/sysu/include:$CPATH \
  LIBRARY_PATH=$HOME/sysu/lib:$LIBRARY_PATH \
  LD_LIBRARY_PATH=$HOME/sysu/lib:$LD_LIBRARY_PATH &&
  sysu-compiler --unittest=lexer-${i} "**/*.sysu.c"
done

# 提交打包
# CPACK_SOURCE_IGNORE_FILES=".git/;tester/third_party/" cmake --build $HOME/sysu/build -t package_source
# 解压测试
# python3 -m tarfile -e SYsU-lang-*-Source.tar.gz
