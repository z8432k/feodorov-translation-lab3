#include "runner.h"

int main(void)
{
    char *result = NULL;

    runner("n*m+k*m+m+m*m+k*k+m+n", &result);

    if (result) {
        g_free(result);
    }
}
