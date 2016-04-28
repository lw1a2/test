#include <iostream>
#include <cstring>
#include <unistd.h>
using namespace std;

int main (int argc, char *argv[])
{
	//strcpy(argv[0], "123456");

	pid_t pid = fork();
	if (pid == 0)
	{
		execl("./test", "123", (char*)0);
	}
	pause();
	return(0);
}


