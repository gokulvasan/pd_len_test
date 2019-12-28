#include <sys/time.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <stdbool.h>
#include <math.h>
#include <sys/resource.h> // needed for getrusage 
#include <unistd.h>


#define PROC "/proc/"
#define PD_LEN "/pd_len"

#define PATH_LEN 256
int main(int argc, char** argv)
{
	FILE *fd;
	pid_t pid = getpid();
	char path[PATH_LEN] = {'\0'};
	char temp[40] = {0x00};
	unsigned long long val[2] = {150, 200};

	sprintf(path, "%s%d%s", PROC, pid, PD_LEN);
	printf("The Path is %s\n", path);
	
	fd = fopen(path, "rw");
	if(!fd) {
		perror("Something is Wrong in opening the file\n");
		exit(-1);
	}
	
	fgets(temp, 40, fd);
	printf("The old Value is: %s\n", temp);
	printf("Setting Val to: STMA %llu LTMA %llu\n", val[0], val[1]);

	if(fwrite(val, 1, sizeof(val), fd)) {
		perror("Write is not working :D");
		exit(-1);
	}
	fclose(fd);
	fd = fopen(path, "r");
	memset(temp, '0x00', sizeof(temp));
	fgets(temp, 40, fd);
	printf("Closed & Extracted New Value is: %s\n", temp);

	return 0;
}

