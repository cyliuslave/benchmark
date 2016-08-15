#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>

#define PHYSICAL_ADDRESS 0xF1000000
int main(int argc, char *argv[])
{
	int fd;
	unsigned int *ptr;
	int i;
	long long value;


	if(argc<2){
		printf("usage : ./vpmu_switch {0|1}\n");
		return -1;
	}

	value=atoi(argv[1]);


	fd = open("/dev/mem", O_RDWR | O_SYNC);
	if (fd < 0) {
		printf("Open Failed\n");
		return 0;
	}
	ptr = (unsigned int *)mmap(NULL, 8, PROT_READ | PROT_WRITE, MAP_SHARED, fd, PHYSICAL_ADDRESS);
	if (ptr == MAP_FAILED) {
		printf("Map Failed\n");
		return 0;
	}

	for(i=0;i<8;i++){
		ptr[0] = 0;
	}
	ptr[0] = value; 

	printf("mmap done.\n");
	close(fd);
	return 0;
}


