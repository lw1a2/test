#һ��makefileģ��

#���������
CC=gcc

#�������ʱ��Ҫ���ӵ�ѡ������ͷ�ļ���λ��
#CPPFLAGS=
CFLAGS=

#��ִ���ļ����
BIN=usermode_netlink

#Դ�ļ�
SRC=usermode_netlink.c

#�����Ŀ⣬��-lrt
LIBS+=

#�����Ŀ��λ�ã���-L/lib
LIBSPATH+=

#ͷ�ļ���λ�ã���-I/test
INCLUDE+=

#���Կ���
#DEBUG=-g
DEBUG=

#Ŀ���ļ�������cpp�Զ�����
OBJ:=$(SRC:%.c=%.o)

#Ĭ��Ŀ��
all: $(BIN)

#����Ŀ���ļ��Ĺ���
%.o: %.c
	$(CC) $(INCLUDE) $(DEBUG) -c $<

#���ɿ�ִ���ļ����Ĺ���
$(BIN): $(OBJ)
	$(CC) $(LIBSPATH) $(LIBS) $(DEBUG) -o $@ $(OBJ)

#������ϵ�ļ���.dep��������cpp�Զ�����
%.dep: %.c
	@set -e; rm -f $@; \
		$(CC) -MM $(CPPFLAGS) $< > $@.$$$$; \
		sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
		rm -f $@.$$$$

#��������ϵ�ļ���������
#�����и������޷����������main.cppԭ��������1.h�����ڽ�1.hɾ���������޸�main.cpp��ɾ����#include "1.h",
#���ʱ�޷���ȷ����main.d���ᱨ��
include $(SRC:%.c=%.dep)

#���
clean:
	-rm -f *.o $(BIN) *.dep

.PHONY: all clean
