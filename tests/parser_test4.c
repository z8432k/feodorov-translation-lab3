#include "runner.h"

int main(void)
{
    char *result = NULL;

    runner("n*m+n*k", &result);

    if (result) {
        g_free(result);
    }
}
