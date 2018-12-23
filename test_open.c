#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int
main(int argc, char *argv[])
{
	int opt, fd, nr, wret;
	char *filename, buf[1024];
	if (argc <= 1) {
		printf("We need a option!\n");
		exit(-1);
	}
	while ((opt = getopt(argc, argv, "f:")) != -1) {
		switch (opt) {
		case 'f':
			filename = optarg;
			break;
		default:
			printf("Unknow option!\n");
			exit(-1);
		}
	}
	printf("Filename:%s\n", filename);
	fd = open(filename, O_RDONLY);
	if (fd == -1) {
		printf("open failed with error [%s]\n", strerror(errno));
		exit(-1);
	}
	while ((nr = read(fd, buf, 1024)) > 0) {
		wret = write(STDOUT_FILENO, buf, nr);
		if (wret < 0) {
			printf("write error [%s]\n", strerror(errno));
			exit(-1);
		}
	}
	return 0;
}
