# 编译
compile:
	gcc -c addvec.c multvec.c main2.c

# 创建一个静态库
build-static-library: compile
	ar rcs libvector.a addvec.o multvec.o

# 创建一个动态库
build-shared-library: compile
	gcc -shared -fpic -o libvector.so addvec.c multvec.c

# 链接静态库，生成可执行文件
build: compile build-static-library
	gcc -o prog2c main2.o ./libvector.a

# 链接动态库，生成可执行文件
build2: compile build-shared-library
	gcc -o prog2b main2.o ./libvector.so

# 运行时动态链接动态库，生成可执行文件
build3: build2
	gcc -rdynamic -o prog2r dll.c -ldl

run: build
	./prog2c

run2: build2
	./prog2b

run3: build3
	./prog2r