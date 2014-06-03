
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <unistd.h>  
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>

int main(int argc, char **argv)
{
	int fd = 0;
	int ledn = 0;
	
	/* 输入检查 */
	ledn = strtoul(argv[1], 0, 0);
	if((3 != argc) || (3 < ledn))
	{
		printf("input param error!\r\n");
		exit(1);
	}
	fd = open("/dev/leds", 2);
	if(0 > fd)
	{
		perror("open /dev/leds");
		exit(1);
	}
	
	if(0 == strcmp(argv[2], "on"))
	{
		printf("led%d = on\r\n", ledn);
		printf("ioctl ret = %d\r\n", ioctl(fd, 1, ledn));
	}
	else if(0 == strcmp(argv[2], "off"))
	{
		printf("led%d = off\r\n", ledn);
		printf("ioctl ret = %d\r\n", ioctl(fd, 0, ledn));
	}
	else
	{
		close(fd);
		printf("input argv[2] error!\r\n");
		exit(1);
	}
	
	close(fd);
	return 0;
}
