#include "runner.h"

int main(void)
{
    char *result = NULL;

    runner("n*m+k*m+m*m*m+k", &result);

    if (result) {
        g_free(result);
    }
}
