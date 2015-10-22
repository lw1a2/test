all: add gen_test

add: add.c
	gcc -o add add.c -I/usr/local/include/ -llua -ldl -lm

gen_test: gen_test.c
	gcc -g -o gen_test gen_test.c -I/usr/local/include/ -llua -ldl -lm

clean:
	rm -rf add gen_test
