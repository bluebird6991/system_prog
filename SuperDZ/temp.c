#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define PORT 8080
#define BUFLEN 256

int main(int argc, char const *argv[]){
	int fd;
	char buffer[BUFLEN];
	if ((fd = open("/dev/DHT11_Device", O_RDWR)) < 0){
		perror("Device açılamadı.\n");
		exit(1);
	}
	read(fd, buffer, BUFLEN);
	printf("%s", buffer);
	close(fd);
	return 0;
}