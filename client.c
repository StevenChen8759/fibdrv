#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include "bignum/bignum.h"

#define FIB_DEV "/dev/fibonacci"

void fib_ull_test()
{
    unsigned long long sz;

    char buf[1];
    char write_buf[] = "testing writing";
    int offset = 100;

    int fd = open(FIB_DEV, O_RDWR);
    if (fd < 0) {
        perror("Failed to open character device");
        exit(1);
    }

    for (int i = 0; i <= offset; i++) {
        sz = write(fd, write_buf, strlen(write_buf));
        printf("Writing to " FIB_DEV ", returned the sequence %llu\n", sz);
    }

    for (int i = 0; i <= offset; i++) {
        lseek(fd, i, SEEK_SET);
        sz = read(fd, buf, 1);
        printf("Reading from " FIB_DEV
               " at offset %d, returned the sequence "
               "%llu.\n",
               i, sz);
    }

    for (int i = offset; i >= 0; i--) {
        lseek(fd, i, SEEK_SET);
        sz = read(fd, buf, 1);
        printf("Reading from " FIB_DEV
               " at offset %d, returned the sequence "
               "%llu.\n",
               i, sz);
    }

    close(fd);
}

/* void fib_bignum_test(void)
{
    unsigned long long sz;

    bignum_t *fibn;

    // char buf[1];
    char write_buf[] = "testing writing";
    int offset = 100;

    int fd = open(FIB_DEV, O_RDWR);
    if (fd < 0) {
        perror("Failed to open character device");
        exit(1);
    }

    for (int i = 0; i <= offset; i++) {
        sz = write(fd, write_buf, strlen(write_buf));
        printf("Writing to " FIB_DEV ", returned the sequence %llu\n", sz);
    }

    for (int i = 0; i <= offset; i++) {
        lseek(fd, i, SEEK_SET);
        sz = read(fd, fibn, 1);
        printf("Reading from " FIB_DEV " at offset %d, returned the sequence ",
               i);
        bn_print(fibn);
        printf(".\n");
    }

    for (int i = offset; i >= 0; i--) {
        lseek(fd, i, SEEK_SET);
        // sz = read(fd, fibn, 1);
        read(fd, fibn, 1);

        printf("Position:");

        printf("Reading from " FIB_DEV " at offset %d, returned the sequence ",
               i);
        bn_print(fibn);
        printf(".\n");
    }

    close(fd);
} */

int main()
{
    /* Call different function for specific implementaion */

    fib_ull_test();  // In type unsigned long long
    // fib_bignum_test(); // In type bignum_t

    /* Using fast doubling implementation */
    // fib_ull_fd_test();    // In type unsigned long long
    // fib_bignum_fd_test(); // In type bignum_t

    return 0;
}
