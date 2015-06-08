#include <sys/stat.h> 
#include <fcntl.h>
#include <unistd.h>

int main(void){

	char content[] = "hello";
	int fd;
	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	char *filename = "hello.txt";

	fd = creat(filename, mode);
	write(fd, content, sizeof(content));
  close(fd);

	return 0;


}
