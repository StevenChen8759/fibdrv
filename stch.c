#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <inttypes.h>

#include "bignum/bignum.h"

#define FIB_DEV "/dev/fibonacci"

int main()
{
    // unsigned long long sz;

    char buf[1];
    char write_buf[] = "testing writing";
    int offset = 100;

    int fd = open(FIB_DEV, O_RDWR);
    if (fd < 0) {
        perror("Failed to open character device");
        exit(1);
    }

    for (int i = 0; i <= offset; i++) {
        unsigned long long sz;

        lseek(fd, i, SEEK_SET);
        sz = read(fd, buf, 1);
        printf("F[%d] = %" PRIu64, i, sz);

        sz = write(fd, write_buf, strlen(write_buf));
        printf(", Time:  %" PRIu64 "\n", sz);
    }

    return 0;
}
