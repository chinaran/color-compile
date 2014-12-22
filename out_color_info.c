#include <stdio.h>
#include <string.h>

#define LINE_SIZE	1024

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

#define WARNING	"warning:"
#define ERROR	"error:"
#define NOTE	"note:"

// function declare
static void color_print_line(const char *line, const char *color);
static int str_char_count(const char *str, char c);


int main(void)
{
	char line[LINE_SIZE];

	while (1)
	{
		if (0 != feof(stdin) || NULL == fgets(line, LINE_SIZE, stdin) )
		{
			break;
		}

		// color_comile.c:35:6: warning: unused variable ‘t’ [-Wunused-variable]
		if (4 != str_char_count(line, ':'))
		{
			printf("%s", line);
			continue;
		}

		if (NULL != strstr(line, WARNING))
		{
			color_print_line(line, WARNING_COLOR);
		}
		else if (NULL != strstr(line, ERROR))
		{
			color_print_line(line, ERROR_COLOR);
		}
		else if (NULL != strstr(line, NOTE))
		{
			color_print_line(line, NOTE_COLOR);
		}
		else
		{
			printf("%s", line);
		}
	}
	
	return 0;
}

static void color_print_line(const char *line, const char *color)
{
	// color_comile.c:35:6: warning: unused variable ‘t’ [-Wunused-variable]
	char *filename;
	char *row;
	char *col;
	char *msg;
	char buf[LINE_SIZE];

	filename = index(line, ':');
	snprintf(buf, filename - line + 1, "%s", line);
	printf("%s%s%s%s:", color, BOLD, buf, COLOR_END);

	row = index(filename + 1, ':');
	snprintf(buf, row - filename, "%s", filename + 1);
	printf("%s%s%s%s:", ROW_COLOR, BOLD, buf, COLOR_END);

	col = index(row + 1, ':');
	snprintf(buf, col - row, "%s", row + 1);
	printf("%s%s%s:", COL_COLOR, buf, COLOR_END);

	msg = index(col + 1, ':');
	snprintf(buf, msg - col, "%s", col + 1);
	printf("%s%s%s:", color, buf, COLOR_END);

	printf("%s%s%s%s", color, BOLD, msg + 1, COLOR_END);
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

