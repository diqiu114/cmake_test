#include "lib_test.h"

int Get_sum(int num1, int num2)
{
    num1 += Get_multiply(num1, num2);
    return num1+num2;
}
