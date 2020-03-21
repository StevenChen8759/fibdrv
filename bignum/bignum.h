#ifndef BIGNUM_H
#define BIGNUM_H

typedef struct BLT {
    char value;
    struct BLT *prev;
    struct BLT *next;
} bnlist_t;

typedef struct {
    int cnt_d;
    bnlist_t *msd;
    bnlist_t *lsd;
} bignum_t;

/* Create a big number with initialize value zero */
bignum_t *bn_create();

/* Return fibonacci number, store with big number structure */
bignum_t *bn_fibonacci(size_t);

/* Allocate digit nodes to specific input number */
void bn_set_digit(bignum_t *, int);

/* Add two big number with new memory space allocation */
bignum_t *bn_add_with_malloc(bignum_t *, bignum_t *);

/* Print big number in Big-endian(MSD first) */
void bn_print();

/* Free created space after usage */
void bn_free();

#endif
