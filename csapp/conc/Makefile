CSAPP_INC = ../rio
CSAPP_SRC = ../rio

# 编译器
CC = gcc
# 预处理和编译选项
CFLAGS = -Og -Wall -I $(CSAPP_INC) -I .
# 链接选项
LDLIBS = -lpthread -lm


PROGS = echo_server_p\
	echo_server_s\
	echo_server_t\
	echo_client\
	echo_server_prethreding\
	hello\
	race\
	unrace\
	sharing\
	badcnt\
	goodcnt


$(PROGS): $(CSAPP_SRC)/csapp.o
$(CSAPP_SRC)/csapp.o: $(CSAPP_SRC)/csapp.c $(CSAPP_INC)/csapp.h

echo_client: echo_client.o echo.o
echo_server_p: echo_server_p.o echo.o
echo_server_s: echo_server_s.o echo.o
echo_server_t: echo_server_t.o echo.o
echo_server_prethreding: echo_server_prethreding.o echo-cnt.o sbuf.o

clean:
	rm ./*.o