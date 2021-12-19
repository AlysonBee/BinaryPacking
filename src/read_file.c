
#include "../inc/header.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

unsigned char	*read_file(char *filename, size_t *size)
{
	int 		fd;
	struct stat	info;	
	unsigned char	*buffer;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		fprintf(stderr, "Unable to open file\n");
		return (NULL);
	}
	fstat(fd, &info);
	*size = info.st_size;
	buffer = (unsigned char *)malloc(sizeof(unsigned char) * *size);
	if (!buffer)
	{
		fprintf(stderr, "No memory\n");
		return (NULL);
	}
	read(fd, buffer, *size);
	close(fd);
	return (buffer);
}
