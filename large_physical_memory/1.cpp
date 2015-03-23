#include <unistd.h>
#include <strings.h>
#include <iostream>

using namespace std;

char *c;

int main() 
{
    long size = 1024L * 1024 * 1024 * 10;
    while (1) {
        try {
            c = new char[size];
            bzero(c, size);
        } catch (bad_alloc &e) {
            size /= 2;
            if (size > 1024 * 1024 * 100) {
                cout << "std::bad_alloc, change size to "
                    << size << endl;
            } else {
                cout << "sleep" << endl;
                sleep(99999);
            }
        }
    }
    
    return 0;
}
