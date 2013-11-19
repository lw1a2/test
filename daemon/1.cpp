#include <unistd.h>
#include <stdio.h>
#include <time.h>

int main()
{
	FILE *fp;
	time_t t;
	daemon(1, 0);
	while (1)
	{
		sleep(3);
		if ((fp = fopen("./test.log", "a")) >=0)
		{
			t = time(0);
			fprintf(fp, "hello %s\n", asctime(localtime(&t)));
			fclose(fp);
		}
	}

	return 0;
}
