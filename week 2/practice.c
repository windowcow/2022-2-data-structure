#include <stdio.h>
#define type(x) _Generic((x),                                                     \
        _Bool: "_Bool",                  unsigned char: "unsigned char",          \
         char: "char",                     signed char: "signed char",            \
    short int: "short int",         unsigned short int: "unsigned short int",     \
          int: "int",                     unsigned int: "unsigned int",           \
     long int: "long int",           unsigned long int: "unsigned long int",      \
long long int: "long long int", unsigned long long int: "unsigned long long int", \
        float: "float",                         double: "double",                 \
  long double: "long double",                   char *: "char *",                 \
       void *: "void *",                         int *: "int *",                  \
      default: "unknown")


int main(void) {

    int arr[5][6];
    int **ptr1;
    int ***ptr2;
    
    printf("%s\n", type(arr));
    printf("%s\n", type(arr[1]));
    printf("%s\n", type(arr[1][1]));
    printf("%s\n", type(arr[5]));


    printf("%s\n", type(ptr1));
    printf("%s\n", type(ptr2));

    printf("%lu\n", sizeof(ptr1));
    printf("%lu\n", sizeof(ptr2));

    printf("%d\n", arr[5]);



    return 1;
}