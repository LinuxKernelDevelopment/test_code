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
#include <string.h>

void Usage(void)
{
	printf("./write source dest\n");
}

#define rangeup_page(size)	((size + getpagesize()) & ~(getpagesize() -1))

int main(int argc, char *argv[])
{
	void *buf;
	int fsize, dfp, ret, sfp;
	char *asp;
	char *src_name = argv[1];
	char *dst_name = argv[2];
	struct stat statbuf;
	if (argc < 2) {
		Usage();
		exit(-1);
	}
	sfp = open(src_name, O_RDONLY);
	if (sfp < 0) {
		perror("open source file failed");
		exit(-1);
	}
	ret = fstat(sfp, &statbuf);
	if (ret == -1) {
		perror("stat file failed");
		exit(-1);
	}
	ret = posix_memalign(&buf, getpagesize(), rangeup_page(statbuf.st_size));
	memset(buf, 0, rangeup_page(statbuf.st_size)); 
	if (ret != 0) {
		printf("%s", strerror(ret));
		exit(-1);
	}
	ret = read(sfp, buf, rangeup_page(statbuf.st_size));
	if (ret < 0) {
		perror("read failed");
		exit(-1);
	}
	dfp =  open(dst_name, O_WRONLY | O_CREAT | O_DIRECT, 0644);
	if (dfp < 0) {
		perror("open destination file failed");
		exit(-1);
	}
	printf("Write the whole file out\n");
	printf("%p, %ld\n", buf, statbuf.st_size);
	ret = write(dfp, buf, rangeup_page(statbuf.st_size));
	if (ret < 0) {
		perror("write to destination file failed");
		exit(-1);
	}
	return 0;
}
