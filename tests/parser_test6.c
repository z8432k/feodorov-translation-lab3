#include "check.h"

int main(void)
{
    check("n*m*k+k*m+m+m*m+k*k*m+m+n*m", "m(nk+k+1+m+kk+1+n)");
}
