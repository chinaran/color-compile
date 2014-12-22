#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE	2048
#define CAT_SIZE	1024


int main(int argc, char const *argv[])
{
	int i;
	char buf[BUF_SIZE];

	if (argc < 2 || 0 != strcmp(argv[0], "color_compile") )
	{
		fprintf(stderr, "[color_compile] bad argument...\n");
		return 1;
	}
	
	// copy cmd
	for (i = 1; i < argc; ++i)
	{
		strncat(buf, argv[i], CAT_SIZE);
		strncat(buf, " ", CAT_SIZE);
	}
	// add out_color_info
	strncat(buf, "2>&1 | out_color_info", CAT_SIZE);

	// true exec
	system(buf);

	return 0;
}

