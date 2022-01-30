#include "math.h"

long long factorial(long long n) {
    long long result = 1;
    while (n > 1) {
        result *= n--;
    }
    return result;
}