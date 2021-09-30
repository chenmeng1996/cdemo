# 文件列表：所有.c后缀的文件名
SRCS := $(wildcard *.c)
# 对象列表：将文件列表中的所有*.c替换成output/*.o
# $(patsubst 原模式， 目标模式， 文件列表)
OBJS := $(patsubst %.c,build/%.o,$(SRCS))

# 可执行文件名
TARGET := main
# 输出文件的文件目录
OUTPUT := build

all: $(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)

# 链接
# 后面有很多.o命令
$(TARGET): $(OBJS)
	# gcc -o $(OUTPUT)/$(TARGET) $(OBJS)
	gcc -o $(TARGET) $(OBJS)

# 编译
$(OBJS): $(OUTPUT)/%.o:%.c
	gcc -g -c $< -o $@