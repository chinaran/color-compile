#include <stdio.h>

#define LINE_SIZE	1024

int main(void)
{
	char buf[LINE_SIZE];
	char p; // this is a warning
	int i = 0;

	while (1)
	{
		if (0 != feof(stdin))
		{
			break;
		}

		if (NULL != fgets(buf, LINE_SIZE, stdin) )
		{
			printf("[%d] %s", ++i, buf);
		}
	}
	
	a; // this is an error

	return 0;
}

