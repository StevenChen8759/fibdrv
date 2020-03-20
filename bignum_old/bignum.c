#include <stdio.h>
#include <stdlib.h>

#include "bignum.h"

bignum_t *bn_create()
{
    /* Local variable declaration */
    bignum_t *bn_new;

    /* Allocate big number`s memory space */
    bn_new = calloc(1, sizeof(bignum_t));

    /* Check if allocated space is null */
    if (bn_new == NULL)
        return bn_new;

    /* Allocate space for first number (as list) */
    bn_new->lsd = calloc(1, sizeof(bnlist_t));

    /* Allocate node fail, free allocated space and return NULL */
    if (bn_new->lsd == NULL) {
        free(bn_new);
        return NULL;
    }

    /* Pointer operation for big number */
    bn_new->msd = bn_new->lsd;

    /* Assign initial value for allocated number(Not necessary for calloc()) */
    /*bn_new->lsd->value = 0;
    bn_new->lsd->prev = NULL;
    bn_new->lsd->next = NULL;*/

    /* Result return */
    return bn_new;
}

bignum_t **bn_make_fibonacci(size_t n)
{
    /* Declare dynamic array for big number */
    bignum_t **bn_fib;
    // bnlist_t *ptr_bnl;
    size_t i;
    // unsigned long long temp;

    /* Return NULL while input is not non-negative value */
    if (n == 0)
        return NULL;

    /* Allocate n bignum_t* pointer spaces for fibonacci number storage */
    bn_fib = calloc(n, sizeof(bignum_t *));  // Allocate pointer spaces...

    /* Return NULL while failed allocation */
    if (bn_fib == NULL)
        return NULL;

    /* Allocate bignum_t spaces for initial value F[0] and F[1] */
    *(bn_fib) = bn_create();      // Allocate F[0]
    *(bn_fib + 1) = bn_create();  // Allocate F[1]

    /* Return NULL while failed allocation*/
    if (*(bn_fib) == NULL || *(bn_fib + 1) == NULL) {
        bn_free(bn_fib);
        return NULL;
    }

    /* Fibonacci number initial value assignment */
    bn_fib[0]->lsd->value = 0;  // F[0] = 0
    bn_fib[1]->lsd->value = 1;  // F[1] = 1

    printf("F[0] = ");
    bn_print(bn_fib[0]);
    printf("\n");
    printf("F[1] = ");
    bn_print(bn_fib[1]);
    printf("\n");

    /* Calculate Fibonacci Number (Start from 2)  */
    for (i = 2; i < n; i++) {
        bn_fib[i] = bn_add_with_malloc(bn_fib[i - 1], bn_fib[i - 2]);
        printf("F[%zu] = ", i);
        bn_print(bn_fib[i]);
        printf("\n");
    }

    return bn_fib;
}

bignum_t *bn_add_with_malloc(bignum_t *src_1, bignum_t *src_2)
{
    /* TODO: Make memory managing mechanism complete! */

    /* Allocate new space for number*/
    bignum_t *res = bn_create();
    bnlist_t *ptr_res, *ptr_src1, *ptr_src2;
    unsigned long long val_carry = 0;

    /* Point to LSD */
    ptr_res = res->lsd;
    ptr_src1 = src_1->lsd;
    ptr_src2 = src_2->lsd;

    /* Add by digits */
    while (1) {
        /* Add value */
        ptr_res->value = ptr_src1->value + ptr_src2->value + val_carry;

        /* Calculate carry value */
        val_carry = (ptr_res->value & 0xFFFFFFFF00000000) >> 32;
    }

    return res;
}

/*unsigned long long bn_check_carry(bnlist_t *digit){

    return ((digit->value) & 0xFFFFFFFF00000000) >> 32;
}*/

void bn_print(bignum_t *bnum)
{
    /* Local Variable Declaration */
    bnlist_t *ptr;

    /* Return while bnum is NULL */
    if (bnum == NULL)
        return;

    /* Pointer Assignment, print by big-endian(MSD first)*/
    ptr = bnum->msd;

    /* Traverse each node and print */
    while (ptr != NULL) {
        printf("%llu", ptr->value);

        ptr = ptr->next;
    }
}


void bn_free(bignum_t *bnum)
{
    /* Local variable declaration */
    bnlist_t *ptr;

    /* Return while bnum is NULL */
    if (bnum == NULL)
        return;

    /* Pointer assignment*/
    ptr = bnum->msd;

    /* free the list */
    while (ptr != NULL) {
        bnum->msd = bnum->msd->next;
        free(ptr);
        ptr = bnum->msd;
    }

    /* free the number structure */
    free(bnum);
}

int main(int argc, char *argv[])
{
    bn_make_fibonacci(100);

    return 0;
}
