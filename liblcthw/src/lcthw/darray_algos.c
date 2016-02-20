#include <lcthw/darray_algos.h>
#include <bsd/stdlib.h>

int DArray_qsort(DArray * array, DArray_compare cmp)
{
    qsort(array->contents, DArray_count(array), sizeof(void *), cmp);
    return 0;
}
