#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static const size_t BUFFER_SIZE = 1024 * 1024; // 1 MiB

int main()
{
    int src_fd = open ("input.dat", O_RDONLY),
        dst_fd = creat ("output.dat", 0666); // umask will apply here

    char* buffer = malloc (BUFFER_SIZE);
    ssize_t bytes, written;
    while ((bytes = read (src_fd, buffer, BUFFER_SIZE)) > 0) {
        written = write (dst_fd, buffer, bytes);
        if (written < 0) {
            perror ("write");
        } else if (written != bytes) {
            perror ("short write");
        }
    }
    if (bytes < 0) {
        perror ("read");
        return 1;
    }
    free (buffer);
}
