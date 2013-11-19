#定义编译器
CC=g++

#定义编译时需要添加的选项，如包含头文件的位置
CPPFLAGS=-I$(INCLUDE)

#可执行文件或库
BIN=a.out

all: $(BIN)
#源文件
SRC=2.cpp
BIN_SRC=main2.cpp

#依赖的库
LIBS+=
LDLIBS=$(LIBS:%=-l%)

#链接选项
LDFLAGS=-shared

#编译选项
CPPFLAGS=-fPIC -g

#依赖的库的位置
LIBSPATH+=
LOADLIBES=$(LIBSPATH:%=-L%)
#头文件的位置
INCLUDE+=

#目标文件，根据cpp自动生成
OBJ:=$(SRC:%.cpp=%.o)

#编译
%.o: %.cpp
	g++ $(INCLUDE) $(CPPFLAGS) -c $<

#链接
lib2.so: $(OBJ)
	g++ $< $(LDLIBS) $(LDFLAGS) -o $@

$(BIN): lib2.so main2.o 
	g++ lib2.so main2.o -o $@

#清除
clean:
	-rm -f $(BIN) $(OBJ) lib1.so lib2.so

.PHONY: clean

