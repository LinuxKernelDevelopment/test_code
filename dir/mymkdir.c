#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	char dirname[100] = { 0, 0, 0};
	int i;
	printf("argc:%d\n", argc);
	if (argc != 2) {
		printf("Usage: ./mymkdir number\n");
		exit(-1);
	}
	for (i = 0; i < atoi(argv[1]); i++)
	{
		sprintf(dirname, "dir%d", i);
		mkdir(dirname, 0777);
	}
	return 0;
}
