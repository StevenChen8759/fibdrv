#ifndef BIGNUM_H
#define BIGNUM_H

typedef struct BLT {
    unsigned long long value;
    struct BLT *prev;
    struct BLT *next;
} bnlist_t;

typedef struct {
    bnlist_t *msd;
    bnlist_t *lsd;
} bignum_t;

bignum_t *bn_create();  // Create a big number with initialize value zero

bignum_t **bn_make_fibonacci(
    size_t);  // Make fibonacci number array, store with big number structure

bignum_t *bn_add_with_malloc(
    bignum_t *,
    bignum_t *);  // add two big number with new memory space allocation

void bn_print();  // Print big number in Big-endian(MSD first)

void bn_free();  // Free created space after usage (Can be used in rmmod)

#endif
