#include <stdio.h>
#include <string.h>

int main() {
    char buf[1024] = "aaa\r\nGET /index.html HTTP/1.1\r\n";
    char *token;
    char *saveptr = NULL;

    token = strtok_r(buf, "\r\n", &saveptr);
    while (token != NULL) {
        printf("%s\n", token);
        token = strtok_r(NULL, "\r\n", &saveptr);
    }
    
    return 0;
}