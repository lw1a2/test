#include <stdio.h>
#include <unistd.h>

void bar() {
}

void foo() {
    for (int i = 0; i < 5; i++)
        sleep(1);
}

int main() {
    bar();
	foo();

	return 0;
}
