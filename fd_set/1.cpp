#include <sys/select.h>
#include <iostream>

using namespace std;

int main()
{
	fd_set rset;
	FD_ZERO(&rset);
	FD_SET(1, &rset);
	FD_SET(66666, &rset);
	return 0;
}
