#include <stdio.h>
#include <unistd.h>

void bar() {
}

void foo() {
    sleep(1);
}

int main() {
    for (int i = 0; i < 5; i++) {
        bar();
    	foo();
    }

	return 0;
}
