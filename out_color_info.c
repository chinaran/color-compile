/*
 * out_color_info.c - show diffrent color when get warnning, note, error ...
 *
 * Copyright (c) 2014-2015 Alan Wang <alan@wrcode.com>
 *
 * This file is released under the Apache Licene 2.0.
 */

#include <stdio.h>
#include <string.h>

#define LINE_SIZE	2048

// printed color
#define BLACK	"\033[30m"
#define RED	"\033[31m"
#define GREEN	"\033[32m"
#define YELLOW	"\033[33m"
#define BLUE	"\033[34m"
#define PURPLE	"\033[35m"
#define CYAN	"\033[36m"
#define WHITE	"\033[37m"

#define BOLD		"\033[1m"
#define COLOR_END	"\033[0m"

#define WARNING_COLOR	YELLOW
#define ERROR_COLOR	RED
#define NOTE_COLOR	CYAN
#define ROW_COLOR	PURPLE
#define COL_COLOR	BLUE

#define MAKE		"make"
#define MAKE_SIGN	"***"

#define WARNING	"warning:"
#define ERROR	"error:"
#define NOTE	"note:"
#define WARNING_CN	"警告："
#define ERROR_CN	"错误："
#define NOTE_CN		"附注："
#define MARK_NUM	6

#define TRUE	1
#define FALSE	0

struct mark_st
{
	const char *mark;
	const char *color;
	const char *print_self;
};

static struct mark_st Mark[MARK_NUM] = 
{
	{WARNING,    WARNING_COLOR, WARNING_COLOR "warning" COLOR_END ":"},
	{ERROR,      ERROR_COLOR,   ERROR_COLOR "error" COLOR_END ":"},
	{NOTE,       NOTE_COLOR,    NOTE_COLOR "note" COLOR_END ":"},
	{WARNING_CN, WARNING_COLOR, WARNING_COLOR "警告" COLOR_END "："},
	{ERROR_CN,   ERROR_COLOR,   ERROR_COLOR "错误" COLOR_END "："},
	{NOTE_CN,    NOTE_COLOR,    NOTE_COLOR "附注" COLOR_END "："},
};


static int str_char_count(const char *str, char c, int len)
{
	int count = 0;

	while (len-- > 0)
	{
		if (c == *(str++) )
		{
			++count;
		}
	}

	return count;
}

static void color_print_line(const char *line, const char *mark_p, int m_i)
{
	char *filename;
	char *row;
	char *col;
	char buf[LINE_SIZE];
	char *p;
	int colon_num;

	colon_num = str_char_count(line, ':', mark_p - line);
	if (1 == colon_num)
	{
		// gcc: 错误： test.c：没有那个文件或目录
		// gcc: 致命错误： 没有输入文件
		// gcc: fatal error: no input files
		// collect2: error: ld returned 1 exit status
		p = index(line, ':');
		snprintf(buf, p - line + 1, "%s", line);
		printf("%s%s%s%s:", PURPLE, BOLD, buf, COLOR_END);

		snprintf(buf, mark_p - p, "%s", p + 1);
		printf("%s%s%s", Mark[m_i].color, buf, COLOR_END);

		printf("%s", Mark[m_i].print_self);

		printf("%s%s%s%s", Mark[m_i].color, BOLD, mark_p + strlen(Mark[m_i].mark), COLOR_END);
	}
	else if (2 == colon_num)
	{
		// test.c:24: 错误：‘a’未声明(在此函数内第一次使用) // centos, gcc4.2
		filename = index(line, ':');
		snprintf(buf, filename - line + 1, "%s", line);
		printf("%s%s%s%s:", Mark[m_i].color, BOLD, buf, COLOR_END);

		row = index(filename + 1, ':');
		snprintf(buf, row - filename, "%s", filename + 1);
		printf("%s%s%s%s:", ROW_COLOR, BOLD, buf, COLOR_END);

		snprintf(buf, mark_p - row, "%s", row + 1);
		printf("%s%s%s", Mark[m_i].color, buf, COLOR_END);

		printf("%s", Mark[m_i].print_self);

		printf("%s%s%s%s", Mark[m_i].color, BOLD, mark_p + strlen(Mark[m_i].mark), COLOR_END);
	}
	else if (3 == colon_num)
	{
		// color_comile.c:35:6: warning: unused variable ‘t’ [-Wunused-variable]
		// xx.c:11:41: fatal error: include/xx.h: No such file or directory
		filename = index(line, ':');
		snprintf(buf, filename - line + 1, "%s", line);
		printf("%s%s%s%s:", Mark[m_i].color, BOLD, buf, COLOR_END);

		row = index(filename + 1, ':');
		snprintf(buf, row - filename, "%s", filename + 1);
		printf("%s%s%s%s:", ROW_COLOR, BOLD, buf, COLOR_END);

		col = index(row + 1, ':');
		snprintf(buf, col - row, "%s", row + 1);
		printf("%s%s%s:", COL_COLOR, buf, COLOR_END);

		snprintf(buf, mark_p - col, "%s", col + 1);
		printf("%s%s%s", Mark[m_i].color, buf, COLOR_END);

		printf("%s", Mark[m_i].print_self);

		printf("%s%s%s%s", Mark[m_i].color, BOLD, mark_p + strlen(Mark[m_i].mark), COLOR_END);
	}
	else
	{
		printf("%s", line);
	}
}

static void color_print_line_mark(const char *line, int len)
{
	//  char p; // this is a warning
	//       ^
	char buf[LINE_SIZE];
	snprintf(buf, len - 1, "%s", line);
	printf("%s", buf);

	printf("%s%s%c%s", GREEN, BOLD, '^', COLOR_END);

	printf("%s", line + len - 1);
}

static void color_print_make_error(const char *line, const char *p_sign)
{
	// make: *** [obj/main.o] Error 1
	// make[5]: *** [libmpc.la] Error 1
	char *left;
	char *right;
	char buf[LINE_SIZE];

	left = index(p_sign, '[');
	if (left != NULL)
	{
		snprintf(buf, left - line + 1, "%s", line);
		printf("%s%s%s%s", RED, BOLD, buf, COLOR_END);
		
		right = index(left + 1, ']');
		snprintf(buf, right - left + 2, "%s", left);
		printf("%s%s%s", YELLOW, buf, COLOR_END);

		printf("%s%s%s%s", RED, BOLD, right + 1, COLOR_END);
	}
	else
	{
		printf("%s%s%s%s", RED, BOLD, line, COLOR_END);
	}
}

/*------------------ main func ------------------*/
int main(void)
{
	char line[LINE_SIZE];
	int i;
	int len;
	char *p;

	while (1)
	{
		if (0 != feof(stdin) || NULL == fgets(line, LINE_SIZE, stdin) )
		{
			break;
		}

		len = strlen(line);

		// case 1: ^
		if (len >= 2 && '^' == line[len - 2])
		{
			color_print_line_mark(line, len);
			continue;
		}

		// ":" number must >= 1
		if (0 == str_char_count(line, ':', len) )
		{
			printf("%s", line);
			continue;
		}

		// case 2: make
		if (0 == strncmp(line, MAKE, strlen(MAKE)) )
		{
			if (NULL != (p = strstr(line, MAKE_SIGN)) )
			{
				color_print_make_error(line, p);
				continue;
			}
		}

		// case 3: error, warning, note ...
		for (i = 0; i < MARK_NUM; ++i)
		{
			if (NULL != (p = strstr(line, Mark[i].mark)) )
			{
				color_print_line(line, p, i);
				break;
			}
		}

		if (MARK_NUM == i)
		{
			printf("%s", line);
		}
	}
	
	return 0;
}

