#定义编译器
CC=g++

CPPFLAGS=-fPIC

#源文件
SRC=1.cpp 2.cpp 3.cpp 4.cpp 5.cpp 6.cpp 

#目标文件，根据cpp自动生成
OBJ:=$(SRC:%.cpp=%.o)

all: $(OBJ)

#清除
clean:
	-rm -f $(OBJ)

.PHONY: all clean
