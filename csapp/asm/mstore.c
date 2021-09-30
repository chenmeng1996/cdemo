//
// Created by admin on 2021/6/29.
//

long mult2(long, long);

void multstore(long x, long y, long *dest) {
    long t = mult2(x, y);
    *dest = t;
}

/**
 * 编译成汇编文件
 * gcc -Og -S mstore.c
 *
 * 编译成二进制目标文件
 * gcc -Og -c mstore.c
 *
 * 反汇编，将二进制目标文件 或 可执行二进制文件 转换成汇编语言
 * objdump -d mstore.o
 *
 * 编译成可执行文件
 * gcc -Og -o prog main.c mstore.c
*/