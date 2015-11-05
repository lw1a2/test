all: add gen_test dostring

add: add.c
	gcc -o add add.c -I/usr/local/include/ -llua -ldl -lm

gen_test: gen_test.c
	gcc -g -o gen_test gen_test.c -I/usr/local/include/ -llua -ldl -lm

dostring: dostring.c
	gcc -g -o dostring dostring.c -I/usr/local/include/ -llua -ldl -lm

clean:
	rm -rf add gen_test dostring
