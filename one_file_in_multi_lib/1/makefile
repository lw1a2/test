#定义编译器
CC=g++

#定义编译时需要添加的选项，如包含头文件的位置
CPPFLAGS=-I$(INCLUDE)

#可执行文件或库
BIN=a.out

all: $(BIN)
#源文件
SRC=1.cpp
BIN_SRC=main.cpp

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
lib1.so: $(OBJ)
	g++ $< $(LDLIBS) $(LDFLAGS) -o $@

lib1_dup.so: $(OBJ)
	g++ $< $(LDLIBS) $(LDFLAGS) -o $@

$(BIN): lib1.so lib1_dup.so main.o
	g++ lib1.so lib1_dup.so main.o -o $@

#清除
clean:
	-rm -f $(BIN) $(OBJ) main.o lib1.so lib1_dup.so

.PHONY: clean
