#include "check.h"

int main(void)
{
    check("n*m*k+k*m+m+m*m+k*k*m+m+n*m", "m(n+1+kk+m+1+k+kn)");
}
