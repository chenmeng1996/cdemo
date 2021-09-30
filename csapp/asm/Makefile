
# 编译成汇编文件
compile2asm:
	gcc -Og -S mstore.c

# 编译成二进制目标文件
compile2bin:
	gcc -Og -c mstore.c

# 编译成可执行文件
comple2exec:
	gcc -Og -o prog main.c mstore.c

# 反汇编，将二进制目标文件 或 可执行二进制文件 转换成汇编语言
decompile2asm:
	objdump -d mstore.o