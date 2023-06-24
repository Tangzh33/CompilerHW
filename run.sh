# 编译安装
# `${CMAKE_C_COMPILER}` 仅用于编译 `.sysu.c`
# 非 SYsU 语言的代码都将直接/间接使用 `${CMAKE_CXX_COMPILER}` 编译（后缀为 `.cc`）
CMAKE="/home/tangzh/applications/cmake-3.26.2-linux-x86_64/bin/cmake"
CMAKE=cmake

if [ $1 = "compile" ]; then
    rm -rf $HOME/sysu
    ${CMAKE} --version
    ${CMAKE} -G Ninja \
        -DCMAKE_EXPORT_COMPILE_COMMANDS=1 \
        -DCMAKE_C_COMPILER=clang \
        -DCMAKE_CXX_COMPILER=clang++ \
        -DCMAKE_INSTALL_PREFIX=$HOME/sysu \
        -DCMAKE_MODULE_PATH=$(llvm-config --cmakedir) \
        -DCPACK_SOURCE_IGNORE_FILES=".git/;tester/third_party/" \
        -B $HOME/sysu/build
    ${CMAKE} --build $HOME/sysu/build
    ${CMAKE} --build $HOME/sysu/build -t install
    mv $HOME/sysu/build/compile_commands.json ./.vscode/
fi
if [ $1 = "official_test" ]; then
    for i in 1; do
        set -x
        # 测试
    export PATH=$HOME/sysu/bin:$PATH \
        CPATH=$HOME/sysu/include:$CPATH \
        LIBRARY_PATH=$HOME/sysu/lib:$LIBRARY_PATH \
        LD_LIBRARY_PATH=$HOME/sysu/lib:$LD_LIBRARY_PATH &&
        sysu-compiler --unittest=benchmark_generator_and_optimizer_1 "**/*.sysu.c"
        set +x
    done
fi
if [ $1 = "pack" ]; then
    # 提交打包
    CPACK_SOURCE_IGNORE_FILES=".git/;tester/third_party/" cmake --build $HOME/sysu/build -t package_source
    # 解压测试
    python3 -m tarfile -e SYsU-lang-*-Source.tar.gz
fi
if [ $1 = "parser_tmp_1" ]; then
    #Parser 测试
    # cat tmp/tmp.c | ~/sysu/bin/sysu-lexer | ~/sysu/bin/sysu-parser 2>&1 | tee tmp/myout.json
    export PATH=$HOME/sysu/bin:$PATH \
    CPATH=$HOME/sysu/include:$CPATH \
    LIBRARY_PATH=$HOME/sysu/lib:$LIBRARY_PATH \
    LD_LIBRARY_PATH=$HOME/sysu/lib:$LD_LIBRARY_PATH && /home/tangzh/sysu/bin/sysu-preprocessor tmp/tmp.c | clang -cc1 -dump-tokens
    export PATH=$HOME/sysu/bin:$PATH \
    CPATH=$HOME/sysu/include:$CPATH \
    LIBRARY_PATH=$HOME/sysu/lib:$LIBRARY_PATH \
    LD_LIBRARY_PATH=$HOME/sysu/lib:$LD_LIBRARY_PATH && /home/tangzh/sysu/bin/sysu-preprocessor tmp/tmp.c | clang -cc1 -dump-tokens 2>&1 | ~/sysu/bin/sysu-parser 2>&1 | tee tmp/myout.json
fi
# cat tester/function_test2020/00_main.sysu.c | ~/sysu/bin/sysu-lexer | ~/sysu/bin/sysu-parser
if [ $1 = "parser_tmp_2" ]; then
    export PATH=$HOME/sysu/bin:$PATH \
    CPATH=$HOME/sysu/include:$CPATH \
    LIBRARY_PATH=$HOME/sysu/lib:$LIBRARY_PATH \
    LD_LIBRARY_PATH=$HOME/sysu/lib:$LD_LIBRARY_PATH && /home/tangzh/sysu/bin/sysu-preprocessor tmp/tmp.c | clang -cc1 -ast-dump=json > tmp/clangout.json 
    ( export PATH=$HOME/sysu/bin:$PATH \
    CPATH=$HOME/sysu/include:$CPATH \
    LIBRARY_PATH=$HOME/sysu/lib:$LIBRARY_PATH \
    LD_LIBRARY_PATH=$HOME/sysu/lib:$LD_LIBRARY_PATH &&
    clang -E tmp/tmp.c |
    clang -cc1 -ast-dump 2>&1)
fi
if [ $1 = "tmp_1" ]; then
    #Generator 测试
    export PATH=$HOME/sysu/bin:$PATH \
    CPATH=$HOME/sysu/include:$CPATH \
    LIBRARY_PATH=$HOME/sysu/lib:$LIBRARY_PATH \
    LD_LIBRARY_PATH=$HOME/sysu/lib:$LD_LIBRARY_PATH && /home/tangzh/sysu/bin/sysu-preprocessor tmp/tmp.c | clang -cc1 -ast-dump=json > tmp/clangout.json 
    export PATH=$HOME/sysu/bin:$PATH \
    CPATH=$HOME/sysu/include:$CPATH \
    LIBRARY_PATH=$HOME/sysu/lib:$LIBRARY_PATH \
    LD_LIBRARY_PATH=$HOME/sysu/lib:$LD_LIBRARY_PATH &&
    clang -E tmp/tmp.c |
    clang -cc1 -ast-dump
    export PATH=$HOME/sysu/bin:$PATH \
    CPATH=$HOME/sysu/include:$CPATH \
    LIBRARY_PATH=$HOME/sysu/lib:$LIBRARY_PATH \
    LD_LIBRARY_PATH=$HOME/sysu/lib:$LD_LIBRARY_PATH && /home/tangzh/sysu/bin/sysu-preprocessor tmp/tmp.c | clang -cc1 -ast-dump=json | ~/sysu/bin/sysu-generator 2>&1 | tee tmp/myout.txt
    export PATH=$HOME/sysu/bin:$PATH \
    CPATH=$HOME/sysu/include:$CPATH \
    LIBRARY_PATH=$HOME/sysu/lib:$LIBRARY_PATH \
    LD_LIBRARY_PATH=$HOME/sysu/lib:$LD_LIBRARY_PATH && /home/tangzh/sysu/bin/sysu-preprocessor tmp/tmp.c | 
    clang -cc1 -ast-dump=json | ~/sysu/bin/sysu-generator |
    lli --load=libsysy.so --load=libsysu.so
    echo $?
fi
# cat tester/function_test2020/00_main.sysu.c | ~/sysu/bin/sysu-lexer | ~/sysu/bin/sysu-parser
if [ $1 = "tmp_2" ]; then
    export PATH=$HOME/sysu/bin:$PATH \
    CPATH=$HOME/sysu/include:$CPATH \
    LIBRARY_PATH=$HOME/sysu/lib:$LIBRARY_PATH \
    LD_LIBRARY_PATH=$HOME/sysu/lib:$LD_LIBRARY_PATH &&   clang -E tmp/tmp.c |   clang -cc1 -O0 -S -emit-llvm 2>&1 | tee tmp/clangout.txt 
    export PATH=$HOME/sysu/bin:$PATH \
    CPATH=$HOME/sysu/include:$CPATH \
    LIBRARY_PATH=$HOME/sysu/lib:$LIBRARY_PATH \
    LD_LIBRARY_PATH=$HOME/sysu/lib:$LD_LIBRARY_PATH &&   clang -E tmp/tmp.c |   clang -cc1 -O0 -S -emit-llvm |
    lli --load=libsysy.so --load=libsysu.so
    echo $?
fi

if [ $1 = "debug" ]; then

    export PATH=$HOME/sysu/bin:$PATH \
    CPATH=$HOME/sysu/include:$CPATH \
    LIBRARY_PATH=$HOME/sysu/lib:$LIBRARY_PATH \
    LD_LIBRARY_PATH=$HOME/sysu/lib:$LD_LIBRARY_PATH && /home/tangzh/sysu/bin/sysu-preprocessor tmp/tmp.c | clang -cc1 -ast-dump=json > tmp/clangout.json 
    gdb -x debug.gdb    
fi
