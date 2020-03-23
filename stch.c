#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <inttypes.h>
#include <stdint.h>

#include "bignum/bignum.h"

#define FIB_DEV "/dev/fibonacci"

int main()
{
    // unsigned long long sz;

    char buf[1];
    char wr_dp[] = "d", wr_fd[] = "f";
    int offset = 93;

    int fd = open(FIB_DEV, O_RDWR);
    if (fd < 0) {
        perror("Failed to open character device");
        exit(1);
    }

    for (int i = 0; i <= offset; i++) {
        unsigned long long sz;

        lseek(fd, i, SEEK_SET);
        sz = read(fd, buf, 1);
        printf("%d, %llu", i, sz);

        sz = write(fd, wr_dp, strlen(wr_dp));
        printf(", %llu", sz);

        sz = write(fd, wr_fd, strlen(wr_fd));
        printf(", %llu\n", sz);
    }

    return 0;
}
