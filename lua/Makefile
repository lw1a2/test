all: add gen_test dostring check_lua

add: add.c
	gcc -o add add.c -I/usr/local/include/ -llua -ldl -lm

gen_test: gen_test.c
	gcc -g -o gen_test gen_test.c -I/usr/local/include/ -llua -ldl -lm

dostring: dostring.c
	gcc -g -o dostring dostring.c -I/usr/local/include/ -llua -ldl -lm

check_lua: check_lua.c
	gcc -g -o check_lua check_lua.c -I/usr/local/include/ -llua -ldl -lm

clean:
	rm -rf add gen_test dostring check_lua
