#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "utils.h"

/* simulates "cat" bash command */

int main(int argc, char *argv[]) {
    DIE(argc != 2, "proper usage: ./cat [file_name]");

    int fd = open(argv[1], O_RDONLY);
    DIE(fd < 0, "cannot open input file");

    int dim = lseek(fd, 0, SEEK_END);
    char *buff = malloc(dim * sizeof(*buff));
    DIE(buff == NULL, "cannot allocate memory");

    lseek(fd, 0, SEEK_SET);
    int check_read = read(fd, buff, dim);
    DIE(check_read < 0, "cannot read from input file");

    int check_write = write(1, buff, dim);
    DIE(check_write < 0, "cannot write to stdout");

    free(buff);
    close(fd);
    
    return 0;
}
