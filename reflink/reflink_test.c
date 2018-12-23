#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <linux/fs.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	char *src_file = argv[1];
	char *dest_file = argv[2];
	int fd1, fd2, ret;
	
	if (argc < 3) {
		printf("Usage:./reflink src dest\n");
		exit(-1);
	}
	printf("%s\n", src_file);
	fd1 = open(src_file, O_RDWR);
	if (fd1 < 0) {
		perror("open failed:");
		printf("%s", src_file);
	}
	fd2 = open(dest_file, O_CREAT | O_WRONLY, 0644);
	if (fd2 < 0) {
		perror("open failed:");
		printf("%s", dest_file);
	}
	ret = ioctl (fd2, FICLONE, fd1);
	if (ret < 0) {
		perror("ioctl failed:");
	}
	return 0;
}
