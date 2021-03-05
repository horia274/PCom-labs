#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "utils.h"

/* simulates "tac" bash command */

int main(int argc, char *argv[]) {
    int check_read, check_write, fd;
    int dim, count_bytes;
    char chr, *buff;

    DIE(argc != 2, "proper usage: ./tac [file_name]");

    fd = open(argv[1], O_RDONLY);
    DIE(fd < 0, "cannot open input file");

    dim = lseek(fd, -1, SEEK_END);
    count_bytes = 0;

    while (dim > 0) {
        check_read = read(fd, &chr, 1);
        DIE(check_read < 0, "cannot read single character from input file");
        dim--;

        if (chr != '\n') {
            count_bytes++;
            lseek(fd, -2, SEEK_CUR);
        } else {
            buff = malloc(count_bytes * sizeof(*buff));
            DIE(buff == NULL, "cannot allocate memory");

            check_read = read(fd, buff, count_bytes);
            DIE(check_read < 0, "cannot read in buffer from input file");

            check_write = write(1, buff, count_bytes);
            DIE(check_write < 0, "cannot write to stdout");

            check_write = write(1, &chr, 1);
            DIE(check_write < 0, "cannot write to stdout");
            
            free(buff);
            lseek(fd, -count_bytes - 2, SEEK_CUR);
            count_bytes = 0;
        }
    }

    /* print the first line */

    lseek(fd, 0, SEEK_SET);
    buff = malloc((++count_bytes) * sizeof(*buff));
    DIE(buff == NULL, "cannot allocate memory");

    check_read = read(fd, buff, count_bytes - 1);
    DIE(check_read < 0, "cannot read in buffer from input file");
    buff[count_bytes - 1] = '\n';

    check_write = write(1, buff, count_bytes);
    DIE(check_write < 0, "cannot write to stdout");

    free(buff);
    close(fd);
    
    return 0;
}
