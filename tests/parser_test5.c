#include "check.h"

int main(void)
{
    check("n*m+k*m+m*m*m+k*m", "m(k+mm+k+n)");
}

