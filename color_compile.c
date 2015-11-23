/*
 * color_compile.c - handle compile command
 *
 * Copyright (c) 2014-2015 Alan Wang <alan@wrcode.com>
 *
 * This file is released under the Apache Licene 2.0.
 */

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

	// declude make menuconfig
	if (3 == argc && 0 == strcmp(argv[1], "make") && 
	    0 == strcmp(argv[2], "menuconfig") )
	{
		system("make menuconfig");
		return 0;
	}
	
	// copy cmd
	buf[0] = '\0';
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

