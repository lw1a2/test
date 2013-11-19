#一个makefile模板

#定义编译器
CC=gcc

#定义编译时需要添加的选项，如包含头文件的位置
#CPPFLAGS=
CFLAGS=

#可执行文件或库
BIN=usermode_netlink

#源文件
SRC=usermode_netlink.c

#依赖的库，如-lrt
LIBS+=

#依赖的库的位置，如-L/lib
LIBSPATH+=

#头文件的位置，如-I/test
INCLUDE+=

#调试开关
#DEBUG=-g
DEBUG=

#目标文件，根据cpp自动生成
OBJ:=$(SRC:%.c=%.o)

#默认目标
all: $(BIN)

#生成目标文件的规则
%.o: %.c
	$(CC) $(INCLUDE) $(DEBUG) -c $<

#生成可执行文件或库的规则
$(BIN): $(OBJ)
	$(CC) $(LIBSPATH) $(LIBS) $(DEBUG) -o $@ $(OBJ)

#依赖关系文件（.dep），根据cpp自动生成
%.dep: %.c
	@set -e; rm -f $@; \
		$(CC) -MM $(CPPFLAGS) $< > $@.$$$$; \
		sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
		rm -f $@.$$$$

#将依赖关系文件包含进来
#这里有个问题无法解决：假设main.cpp原来依赖于1.h，现在将1.h删掉，并且修改main.cpp，删除掉#include "1.h",
#则此时无法正确更新main.d，会报错
include $(SRC:%.c=%.dep)

#清除
clean:
	-rm -f *.o $(BIN) *.dep

.PHONY: all clean

