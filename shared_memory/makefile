#定义编译器
CC=g++

#定义编译时需要添加的选项，如包含头文件的位置
CPPFLAGS=-I$(INCLUDE)

#可执行文件或库
WRITER=1
READER=2

all: $(WRITER) $(READER)

#源文件
WRITER_SRC=1.cpp
READER_SRC=2.cpp

#依赖的库
LIBS+=rt
LDLIBS=$(LIBS:%=-l%)

#依赖的库的位置
LIBSPATH+=
LOADLIBES=$(LIBSPATH:%=-L%)
#头文件的位置
INCLUDE+=

#目标文件，根据cpp自动生成
WRITER_OBJ:=$(WRITER_SRC:%.cpp=%.o)

READER_OBJ:=$(READER_SRC:%.cpp=%.o)

#编译
%.o: %.cpp
	g++ $(INCLUDE) -c $<

#链接
$(WRITER): $(WRITER_OBJ)
	g++ $< $(LDLIBS) -o $@

$(READER): $(READER_OBJ)
	g++ $< $(LDLIBS) -o $@

#清除
clean:
	-rm -f $(WRITER_OBJ) $(READER_OBJ) $(WRITER) $(READER)

.PHONY: clean
