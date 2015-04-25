#include <stdio.h>
#include <string.h>

#define LINE_SIZE	2048

// printed color
#define BLACK	"\033[30m"
#define RED		"\033[31m"
#define GREEN	"\033[32m"
#define YELLOW	"\033[33m"
#define BLUE	"\033[34m"
#define PURPLE	"\033[35m"
#define CYAN	"\033[36m"
#define WHITE	"\033[37m"

#define BOLD		"\033[1m"
#define COLOR_END	"\033[0m"

#define WARNING_COLOR	YELLOW
#define ERROR_COLOR		RED
#define NOTE_COLOR		CYAN
#define ROW_COLOR		PURPLE
#define COL_COLOR		BLUE

#define MAKE	"make: ***"

#define WARNING	"warning:"
#define ERROR	"error:"
#define NOTE	"note:"
#define WARNING_CN	"警告："
#define ERROR_CN	"错误："
#define NOTE_CN	"附注："
#define MARK_NUM	6

#define TRUE	1
#define FALSE	0

struct mark_st
{
	const char *mark;
	const char *color;
	int b_cn;
};

static struct mark_st Mark[MARK_NUM] = 
{
	{WARNING, WARNING_COLOR, FALSE},
	{ERROR, ERROR_COLOR, FALSE},
	{NOTE, NOTE_COLOR, FALSE},
	{WARNING_CN, WARNING_COLOR, TRUE},
	{ERROR_CN, ERROR_COLOR, TRUE},
	{NOTE_CN, NOTE_COLOR, TRUE},
};

// function declare
static void color_print_line(const char *line, const char *color, int b_cn);
static void color_print_make_error(const char *line);
static int str_char_count(const char *str, char c);


int main(void)
{
	char line[LINE_SIZE];
	int i;
	size_t make_len = strlen(MAKE);

	while (1)
	{
		if (0 != feof(stdin) || NULL == fgets(line, LINE_SIZE, stdin) )
		{
			break;
		}

		// color_comile.c:35:6: warning: unused variable ‘t’ [-Wunused-variable]
		// xx.c:11:41: fatal error: include/xx.h: No such file or directory
		// test.c:24:2: 错误： ‘a’未声明(在此函数内第一次使用)
		if (str_char_count(line, ':') < 3)
		{
			if (0 == strncmp(line, MAKE, make_len)) // make error at end
			{
				color_print_make_error(line);
			}
			else
			{
				printf("%s", line);
			}
			continue;
		}

		for (i = 0; i < MARK_NUM; ++i)
		{
			if (NULL != strstr(line, Mark[i].mark))
			{
				color_print_line(line, Mark[i].color, Mark[i].b_cn);
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

static void color_print_line(const char *line, const char *color, int b_cn)
{
	// color_comile.c:35:6: warning: unused variable ‘t’ [-Wunused-variable]
	// arm-linux-gcc: error: xxx: No such file or directory
	// gcc: 错误： test.c：没有那个文件或目录
	// gcc: 致命错误： 没有输入文件
	char *filename;
	char *row;
	char *col;
	char *msg;
	char buf[LINE_SIZE];

	filename = index(line, ':');
	snprintf(buf, filename - line + 1, "%s", line);
	printf("%s%s%s%s:", color, BOLD, buf, COLOR_END);

	row = index(filename + 1, ':');
	if (row != NULL)
	{
		snprintf(buf, row - filename, "%s", filename + 1);
		printf("%s%s%s%s:", ROW_COLOR, BOLD, buf, COLOR_END);
	}
	else
	{
		printf("%s\n", filename + 1);
		return;
	}
	

	col = index(row + 1, ':');
	if (col != NULL)
	{
		snprintf(buf, col - row, "%s", row + 1);
		printf("%s%s%s:", COL_COLOR, buf, COLOR_END);
	}
	else
	{
		printf("%s\n", row + 1);
		return;
	}

	if (FALSE == b_cn)
	{
		msg = index(col + 1, ':');
		if (msg != NULL)
		{
			snprintf(buf, msg - col, "%s", col + 1);
			printf("%s%s%s:", color, buf, COLOR_END);

			printf("%s%s%s%s", color, BOLD, msg + 1, COLOR_END);
		}
		else
		{
			printf("%s\n", col + 1);
		}
	}
	else
	{
		msg = strstr(col + 1, "：");
		if (msg != NULL)
		{
			snprintf(buf, msg - col, "%s", col + 1);
			printf("%s%s%s：", color, buf, COLOR_END);

			printf("%s%s%s%s", color, BOLD, msg + strlen("："), COLOR_END);
		}
		else
		{
			printf("%s\n", col + 1);
		}
	}

	return;
}

static void color_print_make_error(const char *line)
{
	// make: *** [obj/main.o] Error 1
	char *left;
	char *right;
	char buf[LINE_SIZE];

	left = index(line, '[');
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

static int str_char_count(const char *str, char c)
{
	int count = 0;

	while ('\0' != *str)
	{
		if (c == *(str++) )
		{
			count++;
		}
	}

	return count;
}

