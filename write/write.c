#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

void Usage(void)
{
	printf("./write source dest\n");
}

int map_wholefile(char *src_name, char **sp)
{
	int fd;
	struct stat filestat;
	fd = open(src_name, O_RDONLY);
	if (fd < 0) {
		perror("Open source file failed");
		exit(-1);
	}

	if (fstat(fd, &filestat) != 0) {
		perror("stat source file failed");
		exit(-1);
	}
	*sp = mmap(NULL, filestat.st_size, PROT_READ, MAP_SHARED, fd, 0);
	if (*sp == MAP_FAILED) {
		perror("mmap failed");
		exit(-1);
	}
	return filestat.st_size;
}

int main(int argc, char *argv[])
{
	char **sp;
	int fsize, dfp, ret;
	char *asp;
	char *dst_name = argv[2];
	if (argc < 2) {
		Usage();
		exit(-1);
	}
	fsize = map_wholefile(argv[1], sp);
	dfp =  open(dst_name, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (dfp < 0) {
		perror("open destination file failed");
		exit(-1);
	}
	printf("Write the whole file out\n");
	ret = write(dfp, *sp, fsize);
	if (ret < 0) {
		perror("write to destination file failed");
		exit(-1);
	}
	return 0;
}
